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

#ifndef LIBINTFUORITGETALLBREACHES_H
#define LIBINTFUORITGETALLBREACHES_H

#include "component.h"

namespace Intfuorit {

class Breach;
class GetAllBreachesPrivate;

/*!
 * \ingroup api
 * Implements a request to get all breached sites from the HIBP API. Can optionally filter the result
 * by \link GetAllBreaches::domain domain \endlink name.
 *
 * \par HIBP API docs
 * <a href="https://haveibeenpwned.com/API/v2#AllBreaches" rel="external noopener">Getting all breached sites in the system</a>
 *
 * \headerfile "" <Intfuorit/API/GetAllBreaches>
 * \sa Breach, BreachesListModel, BreachesListFilterModel, GetBreachedSite, GetBreachesForAccount
 */
class INTFUORITSHARED_EXPORT GetAllBreaches : public Component
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GetAllBreaches)
    Q_DISABLE_COPY(GetAllBreaches)
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
public:
    /*!
     * Constructs a new %GetAllBreaches object with the given \a parent.
     */
    explicit GetAllBreaches(QObject *parent = nullptr);

    /*!
     * Deconstructs the %GetAllBreaches object.
     */
    ~GetAllBreaches();

    /*!
     * Starts the API request. Set \a reload to \c true to circumvent the cache file and to load directly from the API.
     * If something failed, the Component::failed() signal will be emitted, on success, the gotAllBreaches() signal will
     * be emitted containing the JSON array of breached sites data.
     *
     * \note This function can be invoked via the meta-object system and from QML. See Q_INVOKABLE.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Sets the filter \link GetAllBreaches::domain domain \endlink and starts the API request. Set \a reload to \c true
     * to circumvent the local cache file and to load directly from the API.
     *
     * \note This function can be invoked via the meta-object system and from QML. See Q_INVOKABLE.
     */
    Q_INVOKABLE void execute(const QString &domain, bool reload = false);

    /*!
     * Getter function for the \link GetAllBreaches::domain domain \endlink property.
     * \sa setDomain() domainChanged()
     */
    QString domain() const;
    /*!
     * Setter function for the \link GetAllBreaches::domain domain \endlink property.
     * \sa domain() domainChanged()
     */
    void setDomain(const QString &nDomain);

    /*!
     * Gets the list of all breaches from the HIBP API, optionally filtered by \a domain.
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
    static QVector<Breach> get(const QString &domain = QString(), const QString &userAgent = QString(), bool reload = false, bool *ok = nullptr);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link GetAllBreaches::domain domain \endlink property.
     * \sa domain() setDomain()
     */
    void domainChanged(const QString &domain);
    /*!
     * This signal will be emitted when the list of breached sites has been successfully requested from the API.
     */
    void gotAllBreaches(const QVector<Intfuorit::Breach> &breaches);

protected:
    /*!
     * Sets the Component::inOperation property to \c false and emits the gotAllBreaches() signal.
     */
    void successCallback(const QJsonDocument &json) override;
};

}

#endif // LIBINTFUORITGETALLBREACHES_H
