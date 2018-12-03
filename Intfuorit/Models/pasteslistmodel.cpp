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

#include "pasteslistmodel_p.h"
#include "../Objects/paste.h"

using namespace Intfuorit;

PastesListModel::PastesListModel(QObject *parent) : PastesModel(* new PastesListModelPrivate(this), parent)
{

}


PastesListModel::PastesListModel(PastesListModelPrivate &dd, QObject *parent) : PastesModel(dd, parent)
{

}


PastesListModel::~PastesListModel()
{

}


QHash<int, QByteArray> PastesListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    roles.insert(Source, QByteArrayLiteral("source"));
    roles.insert(SourceId, QByteArrayLiteral("sourceId"));
    roles.insert(Title, QByteArrayLiteral("title"));
    roles.insert(EmailCount, QByteArrayLiteral("emailCount"));
    roles.insert(Date, QByteArrayLiteral("date"));
    roles.insert(Url, QByteArrayLiteral("url"));
    return roles;
}


int PastesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const PastesListModel);
    return d->list.size();
}


QModelIndex PastesListModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex idx;

    if (hasIndex(row, column, parent)) {
        idx = createIndex(row, column);
    }

    return idx;
}


QVariant PastesListModel::data(const QModelIndex &index, int role) const
{
    QVariant var;

    Q_D(const PastesListModel);

    if (index.isValid() && (static_cast<std::size_t>(index.row()) < d->list.size())) {
        Paste *p = d->list.at(index.row());
        switch(role) {
        case Item:          var.setValue<Paste*>(p);        break;
        case Source:        var.setValue(p->source());      break;
        case SourceId:      var.setValue(p->sourceId());    break;
        case Title:         var.setValue(p->title());       break;
        case EmailCount:    var.setValue(p->emailCount());  break;
        case Date:          var.setValue(p->date());        break;
        case Url:           var.setValue(p->url());         break;
        default: break;
        }
    }

    return var;
}


QModelIndex PastesListModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}


int PastesListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

#include "moc_pasteslistmodel.cpp"
