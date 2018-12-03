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

#ifndef LIBINTFUORITCOMPONENT_H
#define LIBINTFUORITCOMPONENT_H

#include <QObject>
#include <QUrl>
#include "../error.h"
#include "../intfuorit_global.h"

class QNetworkReply;
class QJsonDocument;

namespace Intfuorit {

class Error;
class ComponentPrivate;
class NetworkAccessManagerFactory;

/*!
 * The Component class is the base class of all Intfuorit objects that request data from the HIBP API.
 * When creating a subclass of Component, you have to reimplement execute() and successCallback() -
 * optionally you can reimplement extractError(). In the implementation of execute() set
 * \link Component::inOperation inOperation \endlink to \c true and in the end call startRequest() to
 * request the data from the API. In successCallback() you should process the API JSON reply and set
 * \link Component::inOperation inOperation \endlink to \c false when finished. When reimplementing
 * extractError(), you should emit the failed() signal after extracting the error and set
 * \link Component::inOperation inOperation \endlink to \c false.
 *
 * Normally you do not have to create new derived classes, because libintfuorit already provides classes
 * and methods for each HIBP API route.
 *
 * Component and its subclasses in libintfuorit use a
 * <a href="https://techbase.kde.org/Policies/Library_Code_Policy/Shared_D-Pointer_Example">shared D-pointer</a>.
 *
 * \headerfile "" <Intfuorit/API/component.h>
 * \since libintfuorit 1.0.0
 */
class INTFUORITSHARED_EXPORT Component : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Component)
    Q_DECLARE_PRIVATE(Component)
    /*!
     * This property holds the descriptive <A HREF="https://en.wikipedia.org/wiki/User_agent#Use_in_HTTP">HTTP User Agent</A>
     * that will be added to the API request. The HIBP API requires to send a user agent header with
     * every API request. So you should set this to some valid value. If not set explicitly, the user
     * agent will be composed from the values of QCoreApplication::applicationName() and
     * QCoreApplication::applicationVersion().
     *
     * \par HIBP API Docs
     * <A HREF="https://haveibeenpwned.com/API/v2#UserAgent">Specifying the user agent</A>
     *
     * \par Access functions
     * \li QString userAgent() const
     * \li void setUserAgent(const QString &nUserAgent)
     *
     * \par Notifier signal
     * \li void userAgentChanged(const QString &userAgent)
     */
    Q_PROPERTY(QString userAgent READ userAgent WRITE setUserAgent NOTIFY userAgentChanged)
    /*!
     * This property holds wether the API request is running or not. It can be used to show/check the operational status
     * of the request. While it is \c true, no new request will be sent from the current instance (sendRequest() will
     * return directly). Derived classes can use setInOperation() to change it.
     *
     * \par Access functions
     * \li bool inOperation() const
     *
     * \par Notifier signal
     * \li void inOperationChanged(bool inOperation)
     */
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    /*!
     * This property holds the cache time in seconds. If the cache file is not older than the seconds defined in this property
     * and if execute() is called with \a reload = \c false, the data will be loaded from cache instead of the API. Set this
     * property to \c 0 to disable the cache completely. The default value of this property is \c 172800 seconds (2 days).
     *
     * \par Access functions
     * \li quint32 cachePeriod() const
     * \li void setCachePeriod(quint32 nCachePeriod)
     *
     * \par Notifier signal
     * \li void cachePeriodChanged(quint32 cachePeriod)
     */
    Q_PROPERTY(quint32 cachePeriod READ cachePeriod WRITE setCachePeriod NOTIFY cachePeriodChanged)
    /*!
     * This property holds a pointer to the last occured Error. If no error has occured, it holds a \c nullptr. Derived classes
     * can use setError() to set error objects.
     *
     * \note Setting a new Error object will not automatically emit the failed() signal.
     *
     * \par Access functions
     * \li Error *error() const;
     *
     * \par Notifier signal
     * \li void errorChanged(Error *error)
     */
    Q_PROPERTY(Intfuorit::Error error READ error NOTIFY errorChanged)
public:
    /*!
     * Constructs a new Component object with the given \a parent.
     */
    explicit Component(QObject *parent = nullptr);

    /*!
     * Deconstructs the Component object.
     */
    ~Component();

    /*!
     * Executes the API request. Reimplement this in a derived class and setup the request parameters like the API URL and
     * set the \link Component::inOperation inOperation \endlink property to \c true. Here you should also check if
     * inOperation() returns \c true and refuse processing if it is.
     *
     * The \a reload parameter, that controls if the local cache should be circumvented, should be forwarded to the sendRequest() method.
     *
     * After setting up the request parameters like cache file name and URL, you have to call sendRequest()
     * to start the request.
     *
     * \par Implementation example
     *
     * \code{.cpp}
     * void GetAllBreaches::execute(bool reload)
     * {
     *     if (inOperation()) {
     *         qWarning("Getting all breaches still in progress. Aborting.");
     *         return;
     *     }
     *     setInOpeartion(true);
     *     setError(nullptr);
     *
     *     QUrl url = buildUrl(QStringLiteral("breaches"), QString());
     *     if (!d->domain.isEmpty()) {
     *         setCacheFileName(QLatin1String("allbreaches-") % d->domain % QLatin1String(".json"));
     *         QUrlQuery uq;
     *         uq.addQueryItem(QStringLiteral("domain"), d->domain);
     *         url.setQuery(uq);
     *     } else {
     *         setCacheFileName(QStringLiteral("allbreaches.json"));
     *     }
     *
     *     sendRequest(url, reload);
     * }
     * \endcode
     */
    Q_INVOKABLE virtual void execute(bool reload = false) = 0;


    /*!
     * Getter function for the \link Component::error error \endlink property.
     * \sa setError() errorChanged()
     */
    Error error() const;

    /*!
     * Getter function for the \link Component::inOperation inOperation \endlink property.
     * \sa setInOperation() inOperationChanged()
     */
    bool inOperation() const;

    /*!
     * Getter function for the \link Component::cachePeriod cachePeriod \endlink property.
     * \sa setCachePeriod() cachePeriodChanged()
     */
    quint32 cachePeriod() const;

    /*!
     * Getter function for the \link Component::userAgent userAgent \endlink property.
     * \sa setUserAgent() userAgentChanged()
     */
    QString userAgent() const;

    /*!
     * Setter function for the \link Component::cachePeriod cachePeriod \endlink property.
     * \sa cachePeriod() cachePeriodChanged()
     */
    void setCachePeriod(quint32 nCachePeriod);

    /*!
     * Setter function for the \link Component::userAgent userAgent \endlink property.
     * \sa userAgent() userAgentChanged()
     */
    void setUserAgent(const QString &nUserAgent);

    /*!
     * Sets the directory to store the cache files. The default cache directory it that one
     * returned by QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
     */
    void setCacheDirPath(const QString &path);

    /*!
     * Sets the network access manager \a factory to create new QNetworkAccessManager objects
     * to performing the API requests. If no factory is available, a default QNetworkAccessManager
     * object will be created.
     */
    static void setNetworkAccessManagerFactory(NetworkAccessManagerFactory *factory);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link Component::error error \endlink property.
     * \sa setError() error()
     */
    void errorChanged(const Error &error);
    /*!
     * Notifier signal for the \link Component::inOperation inOperation \endlink property.
     * \sa setInOperation() inOperation()
     */
    void inOperationChanged(bool inOperation);
    /*!
     * This signal is emitted when the API request failed. It will contain a pointer to the Error object
     * that will contain more information about the reason the request failed.
     *
     * \sa Component::error
     */
    void failed(const Error &error);
    /*!
     * Notifier signal for the \link Component::cachePeriod cachePeriod \endlink property.
     * \sa setCachePeriod() cachePeriod()
     */
    void cachePeriodChanged(quint32 cachePeriod);
    /*!
     * Notifier signal for the \link Component::userAgent userAgent \endlink property.
     * \sa setUserAgent() userAgent()
     */
    void userAgentChanged(const QString &userAgent);

protected:
    const QScopedPointer<ComponentPrivate> d_ptr;
    Component(ComponentPrivate &dd, QObject *parent = nullptr);

    /*!
     * Extracts error data from a failed API request. You can reimplement this in a derived class.
     * The default implementation simply uses the \a reply to construct a new Error object, sets
     * it with setError() and emits the failed() signal.
     */
    virtual void extractError(QNetworkReply *reply);

    /*!
     * Called after a successfull API request to further process the reponse \a json data.
     * This has to be reimplemented when creating a new derived class that requests JSON data.
     * This is also the place to set \link Component::inOperation inOperation \endlink to
     * \c false after processing the result.
     *
     * The default implementation only sets \link Component::inOperation inOperation \endlink
     * to \c false.
     *
     * \par Implementation example
     *
     * \code{.cpp}
     * void GetAllBreaches::successCallback(const QJsonDocument &json)
     * {
     *     Q_EMIT gotAllBreaches(json);
     *     setInOperation(false);
     * }
     * \endcode
     */
    virtual void successCallback(const QJsonDocument &json);

    /*!
     * Called after a successfull API request to further process the response \a data.
     * This has to be reimplemented when creating a new derived class that requests data
     * other than JSON. This is also the place to set \link Component::inOperation inOperation \endlink
     * to \c false after processing the result.
     *
     * The default implementation only sets \link Component::inOperation inOperation \endlink
     * to \c false.
     *
     * \par Implementation example
     *
     * \code{.cpp}
     * void CheckPwnedPassword::successCallback(const QByteArray &data)
     * {
     *     QTextStream s(data, QIODevice::ReadOnly|QIODevice::Text);
     *     s.setCodec("ASCII");
     *     // further processing ...
     * }
     * \endcode
     *
     * \since libintfuorit 2.0.0
     */
    virtual void successCallback(const QByteArray &data);

    /*!
     * Sends the request to the HIBP API. Use this in the reimplementation of execute() to finally
     * send the request to the API. You can use buildUrl() to create the API URL, set \a reload
     * to \c true to not use cached data. If you want to use a POST request, use the \a payload
     * parameter to specify the request body.
     *
     * \internal
     * Calling this function will reset the last error by setting a \c nullptr to the \link Component::error error \endlink property.
     * If \a reload is \c false or if \link Component::cachePeriod cachePeriod \endlink is set to \c 0, the cache will be ommited.
     *
     * When no \link Component::networkManager networkManager \endlink has been set, this will also create a new QNetworkManager object
     * to perform the API request. If a timeout has been set greater than \c 0, the timeout timer will be started.
     *
     * In the end, the QNetworkReply::finished() signal will be connected to the ComponentPrivate::requestFinished() function and the
     * QNetworkReply::readyRead() signal will be connected to the ComponentPrivate::requestReadyRead() function if a cachefile should be
     * used.
     * \endinternal
     */
    void sendRequest(const QUrl &url, bool reload = false, const QByteArray &payload = QByteArray());

    /*!
     * Builds an API URL for the given \a service and \a parameter.
     */
    QUrl buildUrl(const QString &service, const QString &parameter) const;

    /*!
     * Sets a new pointer to an Error object for the \link Component::error error \endlink property.     *
     * This will be used internally and should also be used by derived classes to set a pointer to the last Error object.
     * To reset the error, simply set a \c nullptr.
     */
    void setError(const Error &error);

    /*!
     * Sets the value of the \link Component::inOperation inOperation \endlink property.
     * Use this to lock the request for the current operation. It is also used to notify connected receivers
     * about the operational state of the request. So simply set it to \c true in you implementation of execute()
     * and set it to false in your implementations of successCallback() and extractError().
     */
    void setInOperation(bool nInOperation);

    /*!
     * Sets the name of the cache file that will be used for this request.
     * The absolute file path will be composed from the setting of setCacheDirPath(), so be sure to call that
     * function at first. Best place to call setCacheFileName() is your implementation of execute().
     */
    void setCacheFileName(const QString &name);

private:
    static NetworkAccessManagerFactory *m_namFactory;
};

}

#endif // LIBINTFUORITCOMPONENT_H
