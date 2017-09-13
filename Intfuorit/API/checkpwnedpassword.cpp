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

#include "checkpwnedpassword_p.h"
#include "../error.h"
#include <QStringBuilder>
#include <QUrlQuery>
#include <QCryptographicHash>

using namespace Intfuorit;

CheckPwnedPassword::CheckPwnedPassword(QObject *parent) :
    Component(* new CheckPwnedPasswordPrivate(this), parent)
{

}


CheckPwnedPassword::~CheckPwnedPassword()
{

}


void CheckPwnedPassword::execute(bool reload)
{
    Q_UNUSED(reload)
    Q_D(CheckPwnedPassword);
    if (inOperation()) {
        qWarning("Checking pwned password still in progress. Aborting.");
        return;
    }

    setInOperation(true);
    setError(nullptr);

    if (d->password.isEmpty()) {
        //% "You can not check for a pwned password without specifying a password."
        setError(new Error(Error::InputError, Error::Critical, qtTrId("libintfuorit-err-empty-password"), this));
        setInOperation(false);
        Q_EMIT failed(error());
        return;
    }

    QUrl url;
    url.setScheme(QStringLiteral("https"));
    url.setHost(QStringLiteral("haveibeenpwned.com"));
    url.setPath(QStringLiteral("/api/v2/pwnedpassword"));

    if (d->originalPasswordIsHash) {
        QUrlQuery uq;
        uq.addQueryItem(QStringLiteral("originalPasswordIsHash"), QStringLiteral("true"));
        url.setQuery(uq);
    }

    const QString hashedPw = d->originalPasswordIsHash ? d->password : QString::fromLatin1(QCryptographicHash::hash(d->password.toUtf8(), QCryptographicHash::Sha1).toHex());

    QUrlQuery data;
    data.addQueryItem(QStringLiteral("Password"), hashedPw);

    sendRequest(url, true, data.toString(QUrl::FullyEncoded).toUtf8());
}


void CheckPwnedPassword::execute(const QString &password, bool originalPasswordIsHash, bool reload)
{
    setPassword(password);
    setOriginalPasswordIsHash(originalPasswordIsHash);
    execute(reload);
}


void CheckPwnedPassword::successCallback(const QJsonDocument &json)
{
    Q_UNUSED(json)
    qDebug("Password \"%s\" has been pwned.", qUtf8Printable(password()));
    Q_EMIT passwordPwned(password());
    setInOperation(false);
}


void CheckPwnedPassword::extractError(QNetworkReply *reply)
{
    Q_ASSERT_X(reply, "extract error", "invalid QNetworkReply object");

    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 404) {
        qDebug("Password \"%s\" has not been pwned.", qUtf8Printable(password()));
        Q_EMIT passwordNotPwned(password());
    } else {
        Component::extractError(reply);
    }
    setInOperation(false);
}


QString CheckPwnedPassword::password() const { Q_D(const CheckPwnedPassword); return d->password; }

void CheckPwnedPassword::setPassword(const QString &nPassword)
{
    Q_D(CheckPwnedPassword);
    if (d->password != nPassword) {
        d->password = nPassword;
        qDebug("Changed password to \"%s\".", qUtf8Printable(nPassword));
        Q_EMIT passwordChanged(nPassword);
    }
}


bool CheckPwnedPassword::originalPasswordIsHash() const { Q_D(const CheckPwnedPassword); return d->originalPasswordIsHash; }

void CheckPwnedPassword::setOriginalPasswordIsHash(bool nOriginalPasswordIsHash)
{
    Q_D(CheckPwnedPassword);
    if (d->originalPasswordIsHash != nOriginalPasswordIsHash) {
        d->originalPasswordIsHash = nOriginalPasswordIsHash;
        qDebug("Changed originalPasswordIsHash to %s.", nOriginalPasswordIsHash ? "true" : "false");
        Q_EMIT originalPasswordIsHashChanged(nOriginalPasswordIsHash);
    }
}
