/* libintfuorit - Qt library to access the API of haveibeenpwned.com
 * Copyright (C) 2017-2019 Hüssenbergnetz / Matthias Fehring
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

#include "getallbreaches_p.h"
#include "../Objects/breach.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QVector>
#include <QUrlQuery>
#include <QStringBuilder>

using namespace Intfuorit;

GetAllBreaches::GetAllBreaches(QObject *parent) : Component(* new GetAllBreachesPrivate(this), parent)
{

}


GetAllBreaches::~GetAllBreaches()
{

}


void GetAllBreaches::execute(bool reload)
{
    Q_D(GetAllBreaches);
    if (inOperation()) {
        qWarning("Getting all breaches still in progress. Aborting.");
        return;
    }
    setInOperation(true);
    setError(Error());

    QUrl url = buildUrl(QStringLiteral("breaches"), QString());
    if (!d->domain.isEmpty()) {
        setCacheFileName(QLatin1String("allbreaches-") % d->domain % QLatin1String(".json"));
        QUrlQuery uq;
        uq.addQueryItem(QStringLiteral("domain"), d->domain);
        url.setQuery(uq);
    } else {
        setCacheFileName(QStringLiteral("allbreaches.json"));
    }
    sendRequest(url, reload);
}


void GetAllBreaches::execute(const QString &domain, bool reload)
{
    setDomain(domain);
    execute(reload);
}


void GetAllBreaches::successCallback(const QJsonDocument &json)
{
    qDebug("%s", "Got all breaches.");
    const QJsonArray a = json.array();
    QVector<Breach> breaches;
    breaches.reserve(a.size());
    for (const QJsonValue &v : a) {
        breaches.push_back(Breach::fromJson(v.toObject()));
    }
    Q_EMIT gotAllBreaches(breaches);
    setInOperation(false);
}


QString GetAllBreaches::domain() const { Q_D(const GetAllBreaches); return d->domain; }

void GetAllBreaches::setDomain(const QString &nDomain)
{
    Q_D(GetAllBreaches);
    if (nDomain != d->domain) {
        d->domain = nDomain;
        qDebug("Filter domain changed to %s.", qUtf8Printable(nDomain));
        Q_EMIT domainChanged(nDomain);
    }
}

QVector<Breach> GetAllBreaches::get(const QString &domain, const QString &userAgent, bool reload, bool *ok)
{
    QVector<Breach> breaches;
    GetAllBreaches api;
    const QString ua = userAgent.trimmed();
    if (!ua.isEmpty()) {
        api.setUserAgent(ua);
    }
    QEventLoop loop;
    QObject::connect(&api, &GetAllBreaches::failed, &loop, &QEventLoop::quit);
    QObject::connect(&api, &GetAllBreaches::gotAllBreaches, &loop, &QEventLoop::quit);
    if (ok) {
        QObject::connect(&api, &GetAllBreaches::failed, &api, [ok](){*ok = false;});
    }
    QObject::connect(&api, &GetAllBreaches::gotAllBreaches, &api, [&breaches,ok](const QVector<Breach> &_breaches){
        breaches = _breaches;
        if (ok) {
            *ok = true;
        }
    });
    api.execute(domain, reload);
    if (api.inOperation()) {
        loop.exec();
    }
    return breaches;
}

#include "moc_getallbreaches.cpp"
