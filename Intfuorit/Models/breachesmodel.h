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

#ifndef LIBINTFUORITBREACHESMODEL_H
#define LIBINTFUORITBREACHESMODEL_H

#include <QObject>
#include "basemodel.h"
#include "../intfuorit_global.h"

namespace Intfuorit {

class BreachesModelPrivate;

/*!
 * The BreachesModel class is the base class for all Intfuorit Breach data models.
 * It contains a std::vector of pointers to Breach objects that are children of the
 * BreachesModel. Destroying the BreachesModel will also destroy all Breach objects
 * in it. Internally this model uses GetAllBreaches to request a list of breached
 * sites from the HIBP API.
 *
 * Do not use this class directly, use one of the derived classes.
 *
 * \headerfile "" <Intfuorit/Models/breachesmodel.h>
 * \since libintfuorit 1.0.0
 */
class INTFUORITSHARED_EXPORT BreachesModel : public BaseModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BreachesModel)
    Q_DISABLE_COPY(BreachesModel)
public:
    /*!
     * Constructs a new BreachesModel with the given \a parent.
     */
    explicit BreachesModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the BreachesModel and destroys the Breach objects in the model.
     */
    ~BreachesModel();

    /*!
     * Requests all breaches from the HIBP API. If \a reload is set to \c true, the local
     * cache will be circumvented and the data will be requested from the API directly.
     * Internally this uses GetAllBreaches to request the list of breached sites.
     */
    Q_INVOKABLE void getAllBreaches(bool reload = false);

    /*!
     * Requests all breaches from the HIBP API, filtered by \a a domain. If \a reload is
     * set to \c true, the local cache will be circumvented and the data will be requested
     * from the API directly. Internally this uses GetAllBreaches to request the list of
     * breached sites.
     */
    Q_INVOKABLE void getAllBreaches(const QString &domain, bool reload = false);

    /*!
     * Requests the breaches the given \a account was part in from the HIBP API and populates
     * the model, optionally filtered by \a domain. By default, no unverified breaches are
     * included in the response, set \a includeUnverified to \c true to include thos ones as
     * well. Internally this uses GetBreachesForAccount to request the list of breaches.
     * If \a reload is \c false, cached data will be loaded if inside the \link BaseModel::cachePeriod cachePeriod \endlink.
     */
    Q_INVOKABLE void getBreachesForAccount(const QString &account, const QString &domain = QString(), bool includeUnverified = false, bool reload = false);

Q_SIGNALS:
    /*!
     * This signal is emitted when the request started by getBreachesForAccount() did not find
     * the specified \a account in the breached sites data.
     */
    void gotNoBreachesForAccount(const QString &account);

protected:
    BreachesModel(BreachesModelPrivate &dd, QObject *parent);
};

}

#endif // LIBINTFUORITBREACHESMODEL_H
