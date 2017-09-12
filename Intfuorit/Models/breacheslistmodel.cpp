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

#include "breacheslistmodel_p.h"
#include "../Objects/breach.h"

using namespace Intfuorit;

BreachesListModel::BreachesListModel(QObject *parent) : BreachesModel(* new BreachesListModelPrivate(this), parent)
{

}

BreachesListModel::BreachesListModel(BreachesListModelPrivate &dd, QObject *parent) : BreachesModel(dd, parent)
{

}

BreachesListModel::~BreachesListModel()
{

}

QHash<int, QByteArray> BreachesListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    roles.insert(Title, QByteArrayLiteral("title"));
    roles.insert(Name, QByteArrayLiteral("name"));
    roles.insert(Domain, QByteArrayLiteral("domain"));
    roles.insert(BreachDate, QByteArrayLiteral("breachDate"));
    roles.insert(AddedDate, QByteArrayLiteral("addedDate"));
    roles.insert(ModifiedDate, QByteArrayLiteral("modifiedDate"));
    roles.insert(PwnCount, QByteArrayLiteral("pwnCount"));
    roles.insert(Description, QByteArrayLiteral("description"));
    roles.insert(DataClasses, QByteArrayLiteral("dataClasses"));
    roles.insert(IsVerified, QByteArrayLiteral("isVerified"));
    roles.insert(IsFabricated, QByteArrayLiteral("isFabricated"));
    roles.insert(IsSensitive, QByteArrayLiteral("isSensitive"));
    roles.insert(IsActive, QByteArrayLiteral("isActive"));
    roles.insert(IsRetired, QByteArrayLiteral("isRetired"));
    roles.insert(IsSpamList, QByteArrayLiteral("isSpamList"));
    roles.insert(LogoType, QByteArrayLiteral("logoType"));
    return roles;
}

int BreachesListModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const BreachesListModel);
    Q_UNUSED(parent);
    return d->list.size();
}

QModelIndex BreachesListModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex idx;

    if (hasIndex(row, column, parent)) {
        idx = createIndex(row, column);
    }

    return idx;
}

QVariant BreachesListModel::data(const QModelIndex &index, int role) const
{
    QVariant var;

    Q_D(const BreachesListModel);

    if (index.isValid() && (static_cast<std::size_t>(index.row()) < d->list.size())) {
        Breach *b = d->list.at(index.row());
        switch (role) {
        case Item:          var.setValue<Breach*>(b);           break;
        case Title:         var.setValue(b->title());           break;
        case Name:          var.setValue(b->name());            break;
        case Domain:        var.setValue(b->domain());          break;
        case BreachDate:    var.setValue(b->breachDate());      break;
        case AddedDate:     var.setValue(b->addedDate());       break;
        case ModifiedDate:  var.setValue(b->modifiedDate());    break;
        case PwnCount:      var.setValue(b->pwnCount());        break;
        case Description:   var.setValue(b->description());     break;
        case DataClasses:   var.setValue(b->dataClasses());     break;
        case IsVerified:    var.setValue(b->isVerified());      break;
        case IsFabricated:  var.setValue(b->isFabricated());    break;
        case IsSensitive:   var.setValue(b->isSensitive());     break;
        case IsActive:      var.setValue(b->isActive());        break;
        case IsRetired:     var.setValue(b->isRetired());       break;
        case IsSpamList:    var.setValue(b->isSpamList());      break;
        case LogoType:      var.setValue(b->logoType());        break;
        default: break;
        }
    }

    return var;
}

QModelIndex BreachesListModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int BreachesListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

#include "moc_breacheslistmodel.cpp"
