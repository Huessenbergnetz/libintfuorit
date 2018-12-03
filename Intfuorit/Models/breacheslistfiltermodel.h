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

#ifndef LIBINTFUORITBREACHESLISTFILTERMODEL_H
#define LIBINTFUORITBREACHESLISTFILTERMODEL_H

#include <QObject>
#include "basefiltermodel.h"

namespace Intfuorit {

class BreachesListFilterModelPrivate;

/*!
 * \ingroup models
 * The %BreachesListFilterModel class provides a dynamically sorted list model of Breach data objects. Internally it
 * uses BreachesListModel to get and store the data.
 *
 * \headerfile "" <Intfuorit/Models/BreachesListFilterModel>
 * \sa Breach, BreachesListModel, GetAllBreaches, GetBreachesForAccount
 */
class BreachesListFilterModel : public BaseFilterModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BreachesListFilterModel)
    Q_DISABLE_COPY(BreachesListFilterModel)
public:
    /*!
     * Constructs a new %BreachesListFilterModel with the given \a parent.
     */
    explicit BreachesListFilterModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the BreachesListFilterModel object.
     */
    ~BreachesListFilterModel();

    /*!
     * Requests all breaches from the HIBP API. If \a reload is set to \c true, the local
     * cache will be circumvented and the data will be requested from the API directly.
     * Internally this will call BreachesListModel::getAllBreaches() from the source model.
     */
    Q_INVOKABLE void getAllBreaches(bool reload = false);

    /*!
     * Requests all breaches from the HIBP API, filtered by \a a domain. If \a reload is
     * set to \c true, the local cache will be circumvented and the data will be requested
     * from the API directly. Internally this will call BreachesListModel::getAllBreaches()
     * from the source model.
     *
     * \overload
     */
    Q_INVOKABLE void getAllBreaches(const QString &domain, bool reload = false);

    /*!
     * Clears all data in the source BreachesListModel and destroys the Breach objects in
     * the source model.
     */
    Q_INVOKABLE void clear();

protected:
    /*!
     * Returns \c true if the iten in the row indicated by the given \a source_row and
     * \a source_parent contains the term set to BaseFilterModel::search in the Breach::title
     * or Breach::domain property.
     */
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

}

#endif // LIBINTFUORITBREACHESLISTFILTERMODEL_H
