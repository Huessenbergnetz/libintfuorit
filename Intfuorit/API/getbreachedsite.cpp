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

#include "getbreachedsite_p.h"
#include "../error.h"
#include "../Objects/breach.h"
#include <QStringBuilder>
#include <QJsonObject>
#include <QEventLoop>

using namespace Intfuorit;

GetBreachedSite::GetBreachedSite(QObject *parent) :
    Component(* new GetBreachedSitePrivate(this), parent)
{

}

GetBreachedSite::~GetBreachedSite()
{

}

void GetBreachedSite::execute(bool reload)
{
    Q_D(GetBreachedSite);
    if (inOperation()) {
        qWarning("Getting breached site still in progress. Aborting.");
        return;
    }

    setInOperation(true);
    setError(Error());

    if (d->name.isEmpty()) {
        //% "You can not request data for a single breached site without specifying a name for it."
        setError(Error(Error::InputError, Error::Critical, qtTrId("libintfuorit-err-missing-breach-name")));
        setInOperation(false);
        Q_EMIT failed(error());
        return;
    }

    const QUrl url = buildUrl(QStringLiteral("breach"), d->name);

    setCacheFileName(QLatin1String("breach-") % d->name % QLatin1String(".json"));

    sendRequest(url, reload);
}

void GetBreachedSite::execute(const QString &name, bool reload)
{
    setName(name);
    execute(reload);
}

QString GetBreachedSite::name() const { Q_D(const GetBreachedSite); return d->name; }

void GetBreachedSite::setName(const QString &nName)
{
    Q_D(GetBreachedSite);
    const QString trimmed = nName.trimmed();
    if (d->name != trimmed) {
        d->name = trimmed;
        qDebug("Changed name to \"%s\".", qUtf8Printable(trimmed));
        Q_EMIT nameChanged(trimmed);
    }
}

void GetBreachedSite::successCallback(const QJsonDocument &json)
{
    qDebug("Got breached site data for %s.", qUtf8Printable(name()));
    Q_EMIT gotBreach(Breach::fromJson(json.object()));
    setInOperation(false);
}

Breach GetBreachedSite::get(const QString &name, const QString &userAgent, bool reload, bool *ok)
{
    Breach breach;
    GetBreachedSite api;
    const QString ua = userAgent.trimmed();
    if (!ua.isEmpty()) {
        api.setUserAgent(ua);
    }
    QEventLoop loop;
    QObject::connect(&api, &GetBreachedSite::failed, &loop, &QEventLoop::quit);
    QObject::connect(&api, &GetBreachedSite::gotBreach, &loop, &QEventLoop::quit);
    if (ok) {
        QObject::connect(&api, &GetBreachedSite::failed, &api, [ok](){*ok = false;});
    }
    QObject::connect(&api, &GetBreachedSite::gotBreach, &api, [&breach,ok](const Breach &_breach){
        breach = _breach;
        if (ok) {
            *ok = true;
        }
    });
    api.execute(name, reload);
    if (api.inOperation()) {
        loop.exec();
    }
    return breach;
}

#include "moc_getbreachedsite.cpp"
