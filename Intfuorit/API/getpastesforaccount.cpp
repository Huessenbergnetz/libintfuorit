/* libintfuorit - Qt library to access the API of haveibeenpwned.com
 * Copyright (C) 2017-2018 Hüssenbergnetz / Matthias Fehring
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

#include "getpastesforaccount_p.h"
#include "../error.h"
#include "../Objects/paste.h"
#include <QCryptographicHash>
#include <QStringBuilder>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

using namespace Intfuorit;

GetPastesForAccount::GetPastesForAccount(QObject *parent) :
    Component(* new GetPastesForAccountPrivate(this), parent)
{

}

GetPastesForAccount::~GetPastesForAccount()
{

}

void GetPastesForAccount::execute(bool reload)
{
    if (inOperation()) {
        qWarning("Geting pastes for account still in progress. Aborting.");
        return;
    }

    setInOperation(true);
    setError(Error());

    Q_D(GetPastesForAccount);

    if (d->account.isEmpty()) {
        //% "Can not request list of pastes for empty account email address."
        setError(Error(Error::InputError, Error::Critical, qtTrId("libintfuorit-err-get-pastes-empty-account")));
        setInOperation(false);
        Q_EMIT failed(error());
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(QByteArrayLiteral("getpastesforaccount"));
    hash.addData(d->account.toUtf8());

    const QUrl url = buildUrl(QStringLiteral("pasteaccount"), d->account);

    setCacheFileName(QString::fromLatin1(hash.result().toHex()) % QLatin1String(".json"));

    sendRequest(url, reload);
}


void GetPastesForAccount::execute(const QString &account, bool reload)
{
    if (inOperation()) {
        qWarning("Geting pastes for account still in progress. Aborting.");
        return;
    }

    setAccount(account);

    execute(reload);
}


QString GetPastesForAccount::account() const { Q_D(const GetPastesForAccount); return d->account; }

void GetPastesForAccount::setAccount(const QString &nAccount)
{
    Q_D(GetPastesForAccount);
    const QString trimmed = nAccount.trimmed();
    if (d->account != trimmed) {
        d->account = trimmed;
        qDebug("Changed account to \"%s\".", qUtf8Printable(trimmed));
        Q_EMIT accountChanged(trimmed);
    }
}


void GetPastesForAccount::successCallback(const QJsonDocument &json)
{
    const QJsonArray array = json.array();
    QVector<Paste> pastes;
    pastes.reserve(array.size());
    for (const QJsonValue &v : array) {
        pastes.push_back(Paste::fromJson(v.toObject()));
    }
    Q_EMIT gotPastesForAccount(account(), pastes);
    qDebug("Account %s is part of pastes.", qUtf8Printable(account()));
    setInOperation(false);
}


void GetPastesForAccount::extractError(QNetworkReply *reply)
{
    Q_ASSERT_X(reply, "extract error", "invalid QNetworkReply object");

    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 404) {
        qDebug("Account/email \"%s\" is not in the HIBP database.", qUtf8Printable(account()));
        Q_EMIT gotNoPastesForAccount(account());
    } else {
        Component::extractError(reply);
    }
    setInOperation(false);
}

QVector<Paste> GetPastesForAccount::get(const QString &account, const QString &userAgent, bool reload, bool *ok)
{
    QVector<Paste> pastes;
    GetPastesForAccount api;
    const QString ua = userAgent.trimmed();
    if (ua.isEmpty()) {
        api.setUserAgent(ua);
    }
    QEventLoop loop;
    QObject::connect(&api, &GetPastesForAccount::failed, &loop, &QEventLoop::quit);
    QObject::connect(&api, &GetPastesForAccount::gotNoPastesForAccount, &loop, &QEventLoop::quit);
    QObject::connect(&api, &GetPastesForAccount::gotPastesForAccount, &loop, &QEventLoop::quit);
    if (ok) {
        QObject::connect(&api, &GetPastesForAccount::failed, &api, [ok](){*ok = false;});
        QObject::connect(&api, &GetPastesForAccount::gotNoPastesForAccount, &api, [ok](){*ok = true;});
    }
    QObject::connect(&api, &GetPastesForAccount::gotPastesForAccount, &api, [&pastes,ok](const QString &account, const QVector<Paste> &_pastes){
        Q_UNUSED(account);
        pastes = _pastes;
        if (ok) {
            *ok = true;
        }
    });
    api.execute(account, reload);
    if (api.inOperation()) {
        loop.exec();
    }
    return pastes;
}

#include "moc_getpastesforaccount.cpp"

