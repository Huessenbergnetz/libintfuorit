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

#include "getallbreaches_p.h"
#include <QJsonDocument>
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
    setError(nullptr);

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
    Q_EMIT gotAllBreaches(json);
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


#include "moc_getallbreaches.cpp"
