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

#ifndef LIBINTFUORITPASTESMODEL_H
#define LIBINTFUORITPASTESMODEL_H

#include <QObject>
#include "basemodel.h"
#include "../intfuorit_global.h"

namespace Intfuorit {

class PastesModelPrivate;

/*!
 * The PastesModel class is the base class for all Intfuorit Paste data model.
 * It contains a std::vector of pointers to Paste objects taht are children of
 * the PastesModel. Destroying the PastesModel will also destroy the Paste objects
 * in it. Internally this model uses GetPastesForAccount to request a list of pastes
 * a specific account is part of from the HIBP API and to populate the model.
 *
 * Call getPastesForAccount() to start the API request and to populate the model. See
 * also BaseModel for more information about required settings.
 *
 * Do not use this class directly, use one of the derived classes, as this class does
 * not implement all functions from QAbstractItemModel that are needed.
 *
 * \headerfile "" <Intfuorit/Models/pastesmode.h>
 * \since libintfuorit 1.0.0
 */
class INTFUORITSHARED_EXPORT PastesModel : public BaseModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(PastesModel)
    Q_DISABLE_COPY(PastesModel)
public:
    /*!
     * Constructs a new empty PastesModel with the given \a parent. Call getPastesForAccount()
     * to start an API request and populate the model.
     */
    explicit PastesModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the PastesModel and destroys all Paste objects in the model.
     */
    ~PastesModel();

    /*!
     * Requests all pastes from the HIBP API the given \a account is part of. If \a reload is
     * set to \c true, the local cache will be circumvented and the data will be requested from
     * the API directly. Use BaseModel::cachePeriod to set the valid period for cached data.
     * Internally this uses GetPastesForAccount to request the list of pastes.
     *
     * Befor sending a new request, the current model data will be cleared and all Paste objects
     * currently available in the model will be destroyed.
     *
     * If pastes were found for the given \a account, the model will be populated with the result,
     * if no pastes were found, the gotNoPastesForAccount() signal will be emitted. If something
     * failed, the BaseModel::failed() signal will be emitted.
     *
     * \sa GetPastesForAccount::execute()
     */
    Q_INVOKABLE void getPastesForAccount(const QString &account, bool reload = false);

Q_SIGNALS:
    /*!
     * This signal will be emitted when the request to the HIBP API was successful and no pastes
     * could be found for the given \a account.
     */
    void gotNoPastesForAccount(const QString &account);

protected:
    PastesModel(PastesModelPrivate &dd, QObject *parent);
};


}

#endif // LIBINTFUORITPASTESMODEL_H
