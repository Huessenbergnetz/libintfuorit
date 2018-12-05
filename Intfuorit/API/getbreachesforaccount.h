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

#ifndef LIBINTFUORITGETBREACHESFORACCOUNT_H
#define LIBINTFUORITGETBREACHESFORACCOUNT_H

#include "component.h"

namespace Intfuorit {

class Breach;
class GetBreachesForAccountPrivate;

/*!
 * \ingroup api
 * Implements a request to get all breached sites for a specific \link GetBreachesForAccount::account account \endlink
 * from the HIBP API. Can optionally filter the result by \link GetBreachesForAccount::domain domain \endlink name.
 * By default, unverified breaches are not included - use the \link GetBreachesForAccount::includeUnverified includeUnverified \endlink
 * property to include those as well. In order to successfully process the request, it is mandatory to set an
 * \link GetBreachesForAccount::account account \endlink.
 *
 * If there are breaches on HIBP the \link GetBreachesForAccount::account account \endlink is part of, gotBreachesForAccount() will
 * be emitted. If there are no breaches, gotNoBreachesForAccount() will be emitted.
 *
 * \par HIBP API docs
 * <a href="https://haveibeenpwned.com/API/v2#BreachesForAccount" rel="external noopener">Getting all breaches for an account</a>
 *
 * \headerfile "" <Intfuorit/API/GetBreachesForAccount>
 * \sa Breach, BreachesListModel, BreachesListFilterModel, GetAllBreaches, GetBreachedSite
 */
class INTFUORITSHARED_EXPORT GetBreachesForAccount : public Component
{
    Q_OBJECT
    Q_DISABLE_COPY(GetBreachesForAccount)
    Q_DECLARE_PRIVATE(GetBreachesForAccount)
    /*!
     * This property holds the \a domain name filter. If not empty, the request URL will have the \a domain
     * filter parameter added and the API will only return breaches for that \a domain.
     *
     * \par Access functions
     * \li QString domain() const
     * \li void setDomain(const QString &nDomain)
     *
     * \par Notifier signal
     * \li void domainChanged(const QString &domain)
     */
    Q_PROPERTY(QString domain READ domain WRITE setDomain NOTIFY domainChanged)
    /*!
     * This property holds wether the replied list of breaches should be truncated. If \c true, only the name of the breach
     * will be returned. The default is \c false.
     *
     * \par Access functions
     * \li bool truncateResponse() const
     * \li void setTruncateResponse(bool nTruncateResponse)
     *
     * \par Notifier signal
     * \li void truncateResponseChanged(bool truncateRepsonse)
     */
    Q_PROPERTY(bool truncateResponse READ truncateResponse WRITE setTruncateResponse NOTIFY truncateResponseChanged)
    /*!
     * This property holds wether unverified breaches should be included in the search. By default this is \c false and
     * only verified breaches will be searched and returned. Set this to \c true to also return breaches that are not
     * verified.
     *
     * \par Access functions
     * \li bool includeUnverified() const
     * \li void setIncludeUnverified(bool nIncludeUnverified)
     *
     * \par Notifier signal
     * \li void includeUnverifiedChanged(bool includeUnverified)
     */
    Q_PROPERTY(bool includeUnverified READ includeUnverified WRITE setIncludeUnverified NOTIFY includeUnverifiedChanged)
    /*!
     * This property holds the account name / email address that should be checked. Checking for breached sites
     * an account is part of works with account user names and with email addresses.
     *
     * \par Access functions
     * \li QString account() const
     * \li void setAccount(const QString &nAccount)
     *
     * \par Notifier signal
     * \li void accountChanged(const QString &account)
     */
    Q_PROPERTY(QString account READ account WRITE setAccount NOTIFY accountChanged)
public:
    /*!
     * Constructs a new %GetBreachesForAccount with the given \a parent.
     */
    explicit GetBreachesForAccount(QObject *parent = nullptr);

    /*!
     * Deconstructs the %GetBreachesForAccount object.
     */
    ~GetBreachesForAccount();

    /*!
     * Start the API request. An \link GetBreachesForAccount::account account \endlink has to be set.
     * Set \a reload to \c true to circumvent the cache file and to load directly from the API.
     *
     * \note This function can be invoked via the meta-object system and from QML. See Q_INVOKABLE.
     */
    Q_INVOKABLE void execute(bool reload = false) override;
    /*!
     * Start the API request with the given propertis. Set \a reload to \c true to circumvent the cache file and to load directly from the API.
     *
     * \note This function can be invoked via the meta-object system and from QML. See Q_INVOKABLE.
     */
    Q_INVOKABLE void execute(const QString &account, const QString &domain = QString(), bool truncateResponse = false, bool includeUnverified = false, bool reload = false);

    /*!
     * Getter function for the \link GetBreachesForAccount::domain domain \endlink property.
     * \sa setDomain() domainChanged()
     */
    QString domain() const;
    /*!
     * Getter function for the \link GetBreachesForAccount::account account \endlink property.
     * \sa setAccount() accountChanged()
     */
    QString account() const;
    /*!
     * Getter function for the \link GetBreachesForAccount::truncateResponse truncateResponse \endlink property.
     * \sa setTruncateResponse() truncateResponseChanged()
     */
    bool truncateResponse() const;
    /*!
     * Getter function for the \link GetBreachesForAccount::includeUnverified includeUnverified \endlink property.
     * \sa setIncludeUnverified() includeUnverifiedChanged()
     */
    bool includeUnverified() const;

    /*!
     * Setter function for the \link GetBreachesForAccount::domain domain \endlink property.
     * \sa domain() domainChanged()
     */
    void setDomain(const QString &nDomain);
    /*!
     * Setter function for the \link GetBreachesForAccount::account account \endlink property.
     * \sa account() accountChanged()
     */
    void setAccount(const QString &nAccount);
    /*!
     * Setter function for the \link GetBreachesForAccount::truncateResponse truncateResponse \endlink property.
     * \sa truncateResposne() truncateResponseChanged()
     */
    void setTruncateResponse(bool nTruncateResponse);
    /*!
     * Setter function for the \link GetBreachesForAccount::includeUnverified includeUnverified \endlink property.
     * \sa inlcludeUnverified() includeUnverifiedChanged()
     */
    void setIncludeUnverified(bool nIncludeUnverified);

    /*!
     * Gets a list of breaches from the HIBP API the \a account is part of. If \a domain is
     * not empty, the API will only check for breaches in this \a domain. If \a includeUnverified
     * is set to \c true, the response will also contain breaches that have not been verified.
     * If \a reload is set to \c false, cached results will be returned where the default
     * cache time (2 days) will be used.
     *
     * If \a userAgent is empty, a default user agent will be created, using QCoreApplication::applicationName()
     * and QCoreApplication::applicationVersion(). Note that the HIBP API does not allow sending an empty user
     * agent string.
     *
     * If \a ok ist not \c nullptr, failure is reported by setting \a *ok to \c false, and success
     * by setting \a *ok to \c true.
     *
     * This function performs a synchronous request and will block the event loop until the request has finished
     * or failed.
     */
    static QVector<Breach> get(const QString &account, const QString &domain = QString(), bool includeUnverified = true, const QString &userAgent = QString(), bool reload = false, bool *ok = nullptr);

Q_SIGNALS:
    /*!
     * Notifier singal for the \link GetBreachesForAccount::domain domain \endlink property.
     * \sa setDomain() domain()
     */
    void domainChanged(const QString &domain);
    /*!
     * Notifier singal for the \link GetBreachesForAccount::account account \endlink property.
     * \sa setAccount() account()
     */
    void accountChanged(const QString &account);
    /*!
     * Notifier singal for the \link GetBreachesForAccount::truncateResponse truncateResponse \endlink property.
     * \sa setTruncateResponse() truncateResponse()
     */
    void truncateResponseChanged(bool truncateResponse);
    /*!
     * Notifier singal for the \link GetBreachesForAccount::includeUnverified includeUnverified \endlink property.
     * \sa setIncludeUnverified() includeUnverified()
     */
    void includeUnverifiedChanged(bool includeUnverified);
    /*!
     * This signal will be emitted when the request has been finished and the \link GetBreachesForAccount::account account \endlink
     * has been found in one ore more breaches.
     * \sa gotNoBreachesForAccount()
     */
    void gotBreachesForAccount(const QString &account, const QVector<Intfuorit::Breach> &breaches);
    /*!
     * This signal will be emitted when the request has been finished and the \link GetBreachesForAccount::account account \endlink
     * has not been found in the breaches data of HIBP. It will contain the queried \a account name.
     * \sa gotBreachesForAccount()
     */
    void gotNoBreachesForAccount(const QString &account);

protected:
    /*!
     * Extracts the breaches \a json array data from the reply, sets Component::inOperation to \c false and
     * emits the gotBreachesForAccount() signal.
     */
    void successCallback(const QJsonDocument &json) override;
    /*!
     * Checks the HTTP status code of the API reply. If the status code is \c 404, the
     * gotNoBreachesForAccount() signal will be emitted, otherwise it calls Component::extractError().
     * At the end it sets Component::inOperation to \c false.
     */
    void extractError(QNetworkReply *reply) override;
};

}

#endif // LIBINTFUORITGETBREACHESFORACCOUNT_H
