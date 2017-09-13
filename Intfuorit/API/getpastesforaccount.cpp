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

#include "getpastesforaccount_p.h"
#include "../error.h"
#include <QCryptographicHash>
#include <QStringBuilder>
#include <QJsonArray>

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
    setError(nullptr);

    Q_D(GetPastesForAccount);

    if (d->account.isEmpty()) {
        //% "Can not request list of pastes for empty account email address."
        setError(new Error(Error::InputError, Error::Critical, qtTrId("libintfuorit-err-get-pastes-empty-account"), this));
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
    Q_EMIT gotPastesForAccount(account(), array);
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

#include "moc_getpastesforaccount.cpp"
