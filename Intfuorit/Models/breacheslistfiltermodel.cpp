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

#include "breacheslistfiltermodel_p.h"

using namespace Intfuorit;

BreachesListFilterModel::BreachesListFilterModel(QObject *parent) :
    BaseFilterModel(*new BreachesListFilterModelPrivate, parent)
{
    setSourceModel(new BreachesListModel(this));
    setSortRole(BreachesListModel::PwnCount);
    setFilterRole(BreachesListModel::Title);
    setSortLocaleAware(true);
    setDynamicSortFilter(true);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    sort(0, Qt::DescendingOrder);
}


BreachesListFilterModel::~BreachesListFilterModel()
{

}


void BreachesListFilterModel::getAllBreaches(bool reload)
{
    Q_D(BreachesListFilterModel);
    INTF_MODEL(BreachesListModel);
    model->getAllBreaches(reload);
}


void BreachesListFilterModel::getAllBreaches(const QString &domain, bool reload)
{
    Q_D(BreachesListFilterModel);
    INTF_MODEL(BreachesListModel);
    model->getAllBreaches(domain, reload);
}


bool BreachesListFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (search().isEmpty()) {
        return true;
    } else {
        Q_D(const BreachesListFilterModel);
        return ((d->search.indexIn(sourceModel()->data(sourceModel()->index(source_row, 0, source_parent), BreachesListModel::Title).toString()) > -1) || (d->search.indexIn(sourceModel()->data(sourceModel()->index(source_row, 0, source_parent), BreachesListModel::Domain).toString()) > -1));
    }
}

void BreachesListFilterModel::clear()
{
    Q_D(BreachesListFilterModel);
    INTF_MODEL(BreachesListModel);
    model->clear();
}

#include "moc_breacheslistfiltermodel.cpp"
