/* libintfuorit - Qt library to access the API of haveibeenpwned.com
 * Copyright (C) 2017 Hüssenbergnetz / Matthias Fehring
 * https://github.com/Huessenbergnetz/libintfuorit
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */


#include "component_p.h"
#include "../error.h"
#include "../networkaccessmanagerfactory.h"
#include <QUrl>
#include <QStringBuilder>

using namespace Intfuorit;

NetworkAccessManagerFactory *Component::m_namFactory = nullptr;

/*!
 * \internal
 * \brief Constructs a new ComponentPrivate with the given \a parent.
 *
 * The \a parent object will be set to the protected \a q_ptr variable to have
 * access to the public class.
 *
 * This constructor will also build the default user agent that will be compiled from
 * QCoreApplication::applicationName() and QCoreApplication::applicationVersion().
 */
ComponentPrivate::ComponentPrivate(Component *parent) :
    q_ptr(parent)
{
    const QString app = QCoreApplication::applicationName();
    const QString ver = QCoreApplication::applicationVersion();
    if (!app.isEmpty() && !ver.isEmpty()) {
        userAgent = QStringLiteral("%1/%2").arg(app, ver);
    } else if (!app.isEmpty() && ver.isEmpty()) {
        userAgent = app;
    }
}

ComponentPrivate::~ComponentPrivate()
{

}

/*!
 * \internal
 * \brief Creates a new request for the HIBP API.
 *
 * You can use Component::buildUrl() to construct a valid API \a url. \a contentLength should
 * be used if it is a POST request. If \a contentLength is greater than \c 0, it will automatically
 * add Content-Type (application/x-www-form-urlencoded) and Content-Length headers to the request.
 */
QNetworkRequest ComponentPrivate::buildRequest(const QUrl &url, int contentLength) const
{
    QNetworkRequest req;

    req.setUrl(url);

    req.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    req.setRawHeader(QByteArrayLiteral("Accept"), QByteArrayLiteral("application/vnd.haveibeenpwned.v2+json"));

    if (contentLength > 0) {
        req.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));
        req.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);
    }

    return req;
}

/*!
 * \internal
 * \brief Processes the finished network reply.
 *
 * This will be called by the QNetworkReply::finished() signal. It will stop the timeout
 * timer, close the cache file and will process the received data.
 *
 * If the reply was successfull (QNetworkReply::error() == QNetworkReply::NoError), it will
 * check the response output with ComponentPrivate::checkOutput() and will than eather call
 * Component::successCallback() or Component::extractError().
 */
void ComponentPrivate::requestFinished()
{
    Q_Q(Component);

    qDebug("API request has been finished.");

    if (Q_LIKELY(timeoutTimer && timeoutTimer->isActive())) {
        timeoutTimer->stop();
    }

    if (cacheFile.isOpen()) {
        cacheFile.close();
    }

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray result;
        if (useCache) {
            if (Q_UNLIKELY(!openCacheFile(QIODevice::ReadOnly|QIODevice::Text))) {
                Q_EMIT q->failed(error);
            } else {
                result = cacheFile.readAll();
                cacheFile.close();
            }
        } else {
            result = reply->readAll();
        }
        bool check = true;
        const QJsonDocument json = checkOutput(result, &check);
        if (check) {
            qDebug("Processing response data");
            q->successCallback(json);
        } else {
            q->setInOperation(false);
        }
    } else {
        q->extractError(reply);
        q->setInOperation(false);
    }

    reply->deleteLater();
    reply = nullptr;
}

/*!
 * \internal
 * \brief Writes the received data to the cache file.
 *
 * QNetworkReply::readyRead() signal will beconnected to this function.
 */
void ComponentPrivate::requestReadyRead()
{
    if (Q_LIKELY(cacheFile.isOpen())) {
        if (Q_UNLIKELY(cacheFile.write(reply->readAll()) == -1)) {
            qWarning("Failed to write data to cache file \"%s\" because of the following error: %s", qUtf8Printable(cacheFile.fileName()), qUtf8Printable(cacheFile.errorString()));
        }
    } else {
        qWarning("Cache file not open! Can not write data to \"%s\".", qUtf8Printable(cacheFile.fileName()));
    }
}

/*!
 * \internal
 * \brief Cancels the API request after the timeout.
 *
 * This will be connected to the QTimer::timeout() signal and will delete
 * the reply after the time has been running out. It will also emit the Component::failed() signal.
 */
void ComponentPrivate::requestTimedOut()
{
    Q_Q(Component);

    //% "The connection to the server timed out after %n second(s)."
    q->setError(new Error(Error::RequestError, Error::Critical, qtTrId("libintfuorit-err-conn-timeout", requestTimeout), q_ptr));

    QNetworkReply *nr = reply;
    reply = nullptr;
    delete nr;

    Q_EMIT q->failed(error);
}

/*!
 * \internal
 * \brief Checks the API response body data.
 *
 * \a result has to be eather the result directly received from the HIBP API or to be the data
 * loaded from a cache file. \a checkResult is mandatory and will be \c true if the check was
 * successfull. If the check failed, \a checkResult will be \c false and the returned QJsonDocument
 * will be empty.
 *
 * This checks will use the expected JSON type that can be set to the expectedJSONType member variable.
 */
QJsonDocument ComponentPrivate::checkOutput(const QByteArray &result, bool *checkResult)
{
    QJsonDocument json;

    qDebug("Checking API response.");

    Q_ASSERT_X(checkResult, "check output", "invalid check result pointer");
    Q_Q(Component);

    if (expectedJSONType != Empty) {
        QJsonParseError jsonError;
        json = QJsonDocument::fromJson(result, &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            q->setError(new Error(jsonError, q_ptr));
            Q_EMIT q->failed(error);
            *checkResult = false;
            return json;
        }
    }

    if (Q_UNLIKELY((expectedJSONType != Empty) && (json.isNull() || json.isEmpty()))) {
        //% "The request replied an empty answer, but there was content expected."
        q->setError(new Error(Error::OutputError, Error::Critical, qtTrId("libintfuorit-err-empty-answer"), q_ptr));
        Q_EMIT q->failed(error);
        *checkResult = false;
        return json;
    }

    if (Q_UNLIKELY((expectedJSONType == Array) && !json.isArray())) {
        //% "It was expected that the request returns a JSON array, but it returned something else."
        q->setError(new Error(Error::OutputError, Error::Critical, qtTrId("libintfuorit-err-no-json-array"), q_ptr));
        Q_EMIT q->failed(error);
        *checkResult = false;
        return json;
    }

    if (Q_UNLIKELY((expectedJSONType == Object) && !json.isObject())) {
        //% "It was expected that the request returns a JSON object, but it returned something else."
        q->setError(new Error(Error::OutputError, Error::Critical, qtTrId("err-no-json-object"), q_ptr));
        Q_EMIT q->failed(error);
        *checkResult = false;
        return json;
    }

    *checkResult = true;
    return json;
}

/*!
 * \internal Returns \c true if the requested data is available in local cache file.
 *
 * This will check if the cache file exists, is not older than the cache period and if
 * the file is not empty.
 */
bool ComponentPrivate::isInCache() const
{
    bool ret = false;

    qDebug("Checking if data is cached.");
    if ((cachePeriod > 0) && !cacheFile.fileName().isEmpty()) {
        if (cacheFile.exists()) {
            QFileInfo fi(cacheFile);
            if (fi.size() > 0) {
                if (fi.lastModified().secsTo(QDateTime::currentDateTime()) < cachePeriod) {
                    ret = true;
                }
            }
        }
    }

    return ret;
}

/*!
 * \brief Opens the cache file with the given \a mode and returns \c true on success.
 */
bool ComponentPrivate::openCacheFile(QIODevice::OpenMode mode)
{
    bool ret = false;

    qDebug("Opening cache file \"%s\".", qUtf8Printable(cacheFile.fileName()));

    if (cacheFile.isOpen()) {
        if (cacheFile.openMode() == mode) {
            ret = true;
        } else {
            qCritical("Cache file \"%s\" is already opened, but with a different mode.", qUtf8Printable(cacheFile.fileName()));
        }
    } else {
        ret = cacheFile.open(mode);
        if (!ret) {
            qCritical("Failed to open cache file \"%s\".", qUtf8Printable(cacheFile.fileName()));
        }
    }

    return ret;
}

/*!
 * \brief Removes the cache file and returns \c true on success.
 *
 * If removing the cache file fails, this will abort the API request and will
 * also emit the Component::failed() signal. It will also set Component::inOperation property
 * to false.
 */
bool ComponentPrivate::removeCacheFile()
{
    bool ret = true;
    qDebug("Removing cache file \"%s\".", qUtf8Printable(cacheFile.fileName()));
    if (cacheFile.exists()) {
        if (!cacheFile.remove()) {
            Q_Q(Component);
            //% "Failed to remove cache file \"%s\"."
            q->setError(new Error(Error::FileError, Error::Critical, qtTrId("libintfuorit-err-remove-cache-file").arg(cacheFile.fileName()), q_ptr));
            Q_EMIT q->failed(error);
            q->setInOperation(false);
            ret = false;
        }
    }
    return ret;
}


Component::Component(QObject *parent) :
    QObject(parent), d_ptr(new ComponentPrivate(this))
{

}


Component::Component(ComponentPrivate &dd, QObject *parent) :
    QObject(parent), d_ptr(&dd)
{

}


Component::~Component()
{

}


QUrl Component::buildUrl(const QString &service, const QString &parameter) const
{
    QUrl url;

    url.setScheme(QStringLiteral("https"));
    url.setHost(QStringLiteral("haveibeenpwned.com"));

    if (!parameter.isEmpty()) {
        url.setPath(QLatin1String("/api/") % service % QLatin1Char('/') % parameter);
    } else {
        url.setPath(QLatin1String("/api/") % service);
    }

    return url;
}


Error* Component::error() const { Q_D(const Component); return d->error; }

void Component::setError(Error *nError)
{
    Q_D(Component);
    if (d->error) {
        if (*nError != *d->error) {
            Error *oldError = d->error;
            d->error = nError;
            delete oldError;
            qDebug("Changed error to %p.", nError);
            Q_EMIT errorChanged(nError);
        } else if (nError != d->error) {
            delete nError;
        }
    } else {
        if (nError) {
            d->error = nError;
            qDebug("Changed error to %p.", nError);
            Q_EMIT errorChanged(nError);
        }
    }
}


bool Component::inOperation() const { Q_D(const Component); return d->inOperation; }

void Component::setInOperation(bool nInOperation)
{
    Q_D(Component);
    if (d->inOperation != nInOperation) {
        d->inOperation = nInOperation;
        qDebug("Changed inOperation to %s.", nInOperation ? "true" : "false");
        Q_EMIT inOperationChanged(nInOperation);
    }
}

void Component::setCacheDirPath(const QString &path)
{
    Q_D(Component);
    if (d->cacheDirPath != path) {
        d->cacheDirPath = path;
        qDebug("Changed cache dir path to \"%s\".", qUtf8Printable(path));
    }
}

void Component::extractError(QNetworkReply *reply)
{
    Q_ASSERT_X(reply, "extract error", "invalid QNetworkReply object");

    switch(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) {
    case 403:
        //% "No user agent has been specified in the request. HIBP API requires a user agent header."
        setError(new Error(Error::RequestError, Error::Critical, qtTrId("libintfuorit-err-forbidden-req"), this));
        break;
    case 429:
        //% "Too many requests, the rate limit has been exceeded."
        setError(new Error(Error::RequestError, Error::Critical, qtTrId("libintfuorit-err-too-many-reqs"), this));
        break;
    default:
        setError(new Error(reply, this));
        break;
    }
    Q_EMIT failed(error());
}


void Component::sendRequest(const QUrl &url, bool reload, const QByteArray &payload)
{
    Q_ASSERT_X(url.isValid(), "send request", "invalid API URL");
    Q_D(Component);

    setError(nullptr);

    if (!reload && d->isInCache()) {
        qDebug("Loading data from cache file \"%s\".", qUtf8Printable(d->cacheFile.fileName()));
        if (d->openCacheFile(QIODevice::ReadOnly|QIODevice::Text)) {
            const QByteArray cachedData = d->cacheFile.readAll();
            if (!cachedData.isEmpty()) {
                d->cacheFile.close();
                bool checkResult = false;
                const QJsonDocument json = d->checkOutput(cachedData, &checkResult);
                if (checkResult) {
                    qDebug("Processing cached data.");
                    successCallback(json);
                    return;
                } else {
                    qWarning("Failed to read data from cache file with. Will try to reload from API.");
                    d->removeCacheFile();
                }
            } else {
                qWarning("Failed to read data from cache file. Will try to reload from API.");
                d->removeCacheFile();
            }
        } else {
            qWarning("Failed to open cache file. Will try to reload from API.");
            d->removeCacheFile();
        }
    }

    qDebug("Sending new request to API.");

    QNetworkRequest req = d->buildRequest(url, payload.length());

    if (!d->nam) {
        if (Component::m_namFactory) {
            d->nam = Component::m_namFactory->create(this);
        } else {
            d->nam = new QNetworkAccessManager(this);
        }
    }

    qDebug("API URL: %s", qUtf8Printable(url.toString()));
#ifndef QT_NO_DEBUG_OUTPUT
    if (!req.rawHeaderList().empty()) {
        const QList<QByteArray> hl = req.rawHeaderList();
        for (const QByteArray &h : hl) {
            qDebug("%s: %s", h.constData(), req.rawHeader(h).constData());
        }
    }

    if (!payload.isEmpty()) {
        qDebug("Payload: %s", payload.constData());
    }
#endif

    if (Q_LIKELY(d->requestTimeout > 0)) {
        if (!d->timeoutTimer) {
            d->timeoutTimer = new QTimer(this);
            d->timeoutTimer->setSingleShot(true);
            d->timeoutTimer->setTimerType(Qt::VeryCoarseTimer);
            connect(d->timeoutTimer, &QTimer::timeout, [d](){d->requestTimedOut();});
        }
        d->timeoutTimer->start(d->requestTimeout * 1000);
    }

    d->useCache = ((d->cachePeriod > 0) && !d->cacheFile.fileName().isEmpty());


    if (d->useCache) {
        d->useCache = d->openCacheFile(QIODevice::WriteOnly);
        if (!d->useCache) {
            //% "Failed to open cache file \"%s\" for writing."
            setError(new Error(Error::FileError, Error::Warning, qtTrId("libintfuorit-err-open-cache-file").arg(d->cacheFile.fileName()), this));
        }
    }

    switch(d->namOperation) {
    case QNetworkAccessManager::GetOperation:
        d->reply = d->nam->get(req);
        break;
    case QNetworkAccessManager::PostOperation:
        d->reply = d->nam->post(req, payload);
        break;
    default:
        d->timeoutTimer->stop();
        //% "Invalid network operation. Only GET and POST are supported."
        setError(new Error(Error::ApplicationError, Error::Critical, qtTrId("libintfuorit-err-invalid-net-op"), this));
        break;
    }

    if (d->useCache) {
        connect(d->reply, &QNetworkReply::readyRead, [d](){d->requestReadyRead();});
    }
    connect(d->reply, &QNetworkReply::finished, [d](){d->requestFinished();});
}

void Component::setCacheFileName(const QString &name)
{
    Q_D(Component);
    const QString fn = d->cacheDirPath % QLatin1Char('/') % name;
    if (d->cacheFile.fileName() != fn) {
        if (!d->cacheFile.isOpen()) {
            d->cacheFile.setFileName(fn);
        } else {
            qWarning("Can not set new cache file name while cache file \"%s\" is open.", qUtf8Printable(fn));
        }
    }
}

quint32 Component::cachePeriod() const { Q_D(const Component); return d->cachePeriod; }

void Component::setCachePeriod(quint32 nCachePeriod)
{
    Q_D(Component);
    if (d->cachePeriod != nCachePeriod) {
        d->cachePeriod = nCachePeriod;
        qDebug("Cache period changed to %u seconds.", nCachePeriod);
        Q_EMIT cachePeriodChanged(nCachePeriod);
    }
}

QString Component::userAgent() const { Q_D(const Component); return d->userAgent; }

void Component::setUserAgent(const QString &nUserAgent)
{
    Q_D(Component);
    const QString uaTrimmed = nUserAgent;
    if (!uaTrimmed.isEmpty()) {
        if (d->userAgent != uaTrimmed) {
            d->userAgent = uaTrimmed;
            qDebug("User agent changed to \"%s\".", qUtf8Printable(uaTrimmed));
            Q_EMIT userAgentChanged(uaTrimmed);
        }
    } else {
        qWarning("You can not set an empty user agent because HIBP API requires an user agent.");
    }

}

void Component::setNetworkAccessManagerFactory(NetworkAccessManagerFactory *factory)
{
    Component::m_namFactory = factory;
}

#include "moc_component.cpp"
