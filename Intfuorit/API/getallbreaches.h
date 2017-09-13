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

#ifndef LIBINTFUORITGETALLBREACHES_H
#define LIBINTFUORITGETALLBREACHES_H

#include <QObject>
#include "../intfuorit_global.h"
#include "../error.h"
#include "component.h"

namespace Intfuorit {

class GetAllBreachesPrivate;

/*!
 * Implements a request to get all breached sites from the HIBP API. Can optionally filter the result
 * by \link GetAllBreaches::domain domain \endlink name.
 *
 * \par HIBP API Docs
 * <A HREF="https://haveibeenpwned.com/API/v2#AllBreaches">Getting all breached sites in the system</A>
 *
 * \headerfile "" <Intfuorit/API/GetAllBreaches>
 * \since libintfuorit 1.0.0
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
     * Constructs a new GetAllBreaches object with the given \a parent.
     */
    explicit GetAllBreaches(QObject *parent = nullptr);

    /*!
     * Deconstructs the GetAllBreaches object.
     */
    ~GetAllBreaches();

    /*!
     * Starts the API request. Set \a reload to \c true to circumvent the cache file and to load directly from the API.
     * If something failed, the Component::failed() signal will be emitted, on success, the gotAllBreaches() signal will
     * be emitted containing the JSON array of breached sites data.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Sets the filter \link GetAllBreaches::domain domain \endlink and starts the API request. Set \a reload to \c true
     * to circumvent the local cache file and to load directly from the API.
     *
     * \overload
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

Q_SIGNALS:
    /*!
     * Notifier signal for the \link GetAllBreaches::domain domain \endlink property.
     * \sa domain() setDomain()
     */
    void domainChanged(const QString &domain);
    /*!
     * This signal will be emitted when the list of breached sites has been successfully requested from the API.
     * The \a breaches JSON will contain an array of objects that contain the information about the
     * breached sites. See the <A HREF="https://haveibeenpwned.com/API/v2#BreachModel">HIBP API docs</A> for a
     * description of the JSON breach object values.
     */
    void gotAllBreaches(const QJsonDocument &breaches);

protected:
    /*!
     * Sets the Component::inOperation property to \c false and emits the gotAllBreaches() signal.
     */
    void successCallback(const QJsonDocument &json) override;
};

}

#endif // LIBINTFUORITGETALLBREACHES_H
