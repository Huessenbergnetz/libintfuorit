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

#include "getbreachesforaccount_p.h"
#include "../error.h"
#include <QCryptographicHash>
#include <QUrlQuery>

using namespace Intfuorit;

GetBreachesForAccount::GetBreachesForAccount(QObject *parent) : Component(* new GetBreachesForAccountPrivate(this), parent)
{

}


GetBreachesForAccount::~GetBreachesForAccount()
{

}


void GetBreachesForAccount::execute(bool reload)
{
    if (inOperation()) {
        qWarning("Geting breaches for acocunt stin in progress. Aborting.");
        return;
    }

    setInOperation(true);
    setError(nullptr);

    Q_D(GetBreachesForAccount);

    if (d->account.isEmpty()) {
        //% "Can not request list of breaches for empty account user name/email address."
        setError(new Error(Error::InputError, Error::Critical, qtTrId("libintfuorit-err-empty-account"), this));
        setInOperation(false);
        Q_EMIT failed(error());
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(d->account.toUtf8());

    QUrlQuery uq;

    if (!d->domain.isEmpty()) {
        hash.addData(d->domain.toUtf8());
        uq.addQueryItem(QStringLiteral("domain"), d->domain);
    }

    if (d->truncateResponse) {
        hash.addData(QByteArrayLiteral("truncateResponse"));
        uq.addQueryItem(QStringLiteral("truncateResponse"), QStringLiteral("true"));
    }

    if (d->includeUnverified) {
        hash.addData(QByteArrayLiteral("includeUnverified"));
        uq.addQueryItem(QStringLiteral("includeUnverified"), QStringLiteral("true"));
    }

    QUrl url = buildUrl(QStringLiteral("breachedaccount"), d->account);

    if (!uq.isEmpty()) {
        url.setQuery(uq);
    }

    setCacheFileName(QString::fromLatin1(hash.result().toHex()));

    sendRequest(url, reload);
}


void GetBreachesForAccount::execute(const QString &account, const QString &domain, bool truncateResponse, bool includeUnverified, bool reload)
{
    if (inOperation()) {
        qWarning("Geting breaches for acocunt stin in progress. Aborting.");
        return;
    }

    setAccount(account);
    setDomain(domain);
    setTruncateResponse(truncateResponse);
    setIncludeUnverified(includeUnverified);

    execute(reload);
}


QString GetBreachesForAccount::domain() const { Q_D(const GetBreachesForAccount); return d->domain; }

void GetBreachesForAccount::setDomain(const QString &nDomain)
{
    const QString trimmed = nDomain.trimmed();
    Q_D(GetBreachesForAccount);
    if (d->domain != trimmed) {
        d->domain = trimmed;
        qDebug("Changed domain to \"%s\".", qUtf8Printable(d->domain));
        Q_EMIT domainChanged(d->domain);
    }
}


QString GetBreachesForAccount::account() const { Q_D(const GetBreachesForAccount); return d->account; }

void GetBreachesForAccount::setAccount(const QString &nAccount)
{
    Q_D(GetBreachesForAccount);
    if (d->account != nAccount) {
        d->account = nAccount;
        qDebug("Changed account to \"%s\".", qUtf8Printable(d->account));
        Q_EMIT accountChanged(d->account);
    }
}


bool GetBreachesForAccount::truncateResponse() const { Q_D(const GetBreachesForAccount); return d->truncateResponse; }

void GetBreachesForAccount::setTruncateResponse(bool nTruncateResponse)
{
    Q_D(GetBreachesForAccount);
    if (d->truncateResponse != nTruncateResponse) {
        d->truncateResponse = nTruncateResponse;
        qDebug("Changed truncateResponse to %s.", d->truncateResponse ? "true" : "false");
        Q_EMIT truncateResponseChanged(d->truncateResponse);
    }
}


bool GetBreachesForAccount::includeUnverified() const { Q_D(const GetBreachesForAccount); return d->includeUnverified; }

void GetBreachesForAccount::setIncludeUnverified(bool nIncludeUnverified)
{
    Q_D(GetBreachesForAccount);
    if (d->includeUnverified != nIncludeUnverified) {
        d->includeUnverified = nIncludeUnverified;
        qDebug("Changed includeUnverified to %s.", d->includeUnverified ? "true" : "false");
        Q_EMIT includeUnverifiedChanged(d->includeUnverified);
    }
}


void GetBreachesForAccount::successCallback(const QJsonDocument &json)
{
    Q_EMIT gotBreachesForAccount(account(), json);
    qDebug("Account %s is part of breaches.", qUtf8Printable(account()));
    setInOperation(false);
}


void GetBreachesForAccount::extractError(QNetworkReply *reply)
{
    Q_ASSERT_X(reply, "extract error", "invalid QNetworkReply object");

    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 404) {
        qDebug("Account/email %s is not in the HIBP database.", qUtf8Printable(account()));
        Q_EMIT gotNoBreachesForAccount(account());
    } else {
        Component::extractError(reply);
    }
    setInOperation(false);
}

#include "moc_getbreachesforaccount.cpp"