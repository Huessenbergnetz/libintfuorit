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
#include <QTextStream>

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

    const QByteArray hash = QCryptographicHash::hash(d->password.toUtf8(), QCryptographicHash::Sha1).toHex().toUpper();
    d->pwPrefix = QString::fromLatin1(hash.left(5));
    d->pwSuffix = QString::fromLatin1(hash.mid(5));

    setCacheFileName(d->pwPrefix % QStringLiteral(".txt"));

    QUrl url;
    url.setScheme(QStringLiteral("https"));
    url.setHost(QStringLiteral("api.pwnedpasswords.com"));
    url.setPath(QStringLiteral("/range/") % d->pwPrefix);

    sendRequest(url, reload);
}


void CheckPwnedPassword::execute(const QString &password, bool reload)
{
    setPassword(password);
    setOriginalPasswordIsHash(originalPasswordIsHash);
    execute(reload);
}


void CheckPwnedPassword::successCallback(const QJsonDocument &json)
{
    Q_UNUSED(json)
    Q_ASSERT_X(false, "CheckPwnedPassword::successCallback", "there should be no JSON in the respone");
}


void CheckPwnedPassword::successCallback(const QByteArray &data)
{
    Q_D(CheckPwnedPassword);
    QTextStream s(data, QIODevice::ReadOnly|QIODevice::Text);
    s.setCodec("ASCII");
    int count = 0;
    QString line;
    line.reserve(45);
    while (s.readLineInto(&line)) {
        const QString suffix = line.left(35);
        if (d->pwSuffix.compare(suffix, Qt::CaseInsensitive) == 0) {
            count = line.mid(36).toInt();
            break;
        }
    }
    qDebug("The password \"%s\" has been found %i times.", qUtf8Printable(d->password), count);
    Q_EMIT passwordChecked(count);
    setInOperation(false);
}


void CheckPwnedPassword::extractError(QNetworkReply *reply)
{
    Q_ASSERT_X(reply, "extract error", "invalid QNetworkReply object");
    Component::extractError(reply);
    setInOperation(false);
}


QString CheckPwnedPassword::password() const { Q_D(const CheckPwnedPassword); return d->password; }

void CheckPwnedPassword::setPassword(const QString &nPassword)
{
    Q_D(CheckPwnedPassword);
    if (inOperation()) {
        qWarning("%s", "Can not change the password to check while operation is running.");
        return;
    }
    if (d->password != nPassword) {
        d->password = nPassword;
        qDebug("Changed password to \"%s\".", qUtf8Printable(nPassword));
        Q_EMIT passwordChanged(nPassword);
    }
}

#include "moc_checkpwnedpassword.cpp"
