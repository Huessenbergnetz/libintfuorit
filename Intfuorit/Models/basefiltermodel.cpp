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

#include "basefiltermodel_p.h"

using namespace Intfuorit;

BaseFilterModel::BaseFilterModel(QObject *parent) : QSortFilterProxyModel(parent), d_ptr(new BaseFilterModelPrivate)
{
    Q_D(BaseFilterModel);
    connect(this, &QAbstractProxyModel::sourceModelChanged, [this, d]() {
        if (d->bsm) {
            disconnect(d->bsm, &BaseModel::inOperationChanged, this, &BaseFilterModel::inOperationChanged);
            disconnect(d->bsm, &BaseModel::errorChanged, this, &BaseFilterModel::errorChanged);
            disconnect(d->bsm, &BaseModel::cachePeriodChanged, this, &BaseFilterModel::cachePeriodChanged);
            disconnect(d->bsm, &BaseModel::userAgentChanged, this, &BaseFilterModel::userAgentChanged);
        }
        d->bsm = qobject_cast<BaseModel *>(sourceModel());
        if (d->bsm) {
            connect(d->bsm, &BaseModel::inOperationChanged, this, &BaseFilterModel::inOperationChanged);
            connect(d->bsm, &BaseModel::errorChanged, this, &BaseFilterModel::errorChanged);
            connect(d->bsm, &BaseModel::cachePeriodChanged, this, &BaseFilterModel::cachePeriodChanged);
            connect(d->bsm, &BaseModel::userAgentChanged, this, &BaseFilterModel::userAgentChanged);
        }
    });
}


BaseFilterModel::BaseFilterModel(BaseFilterModelPrivate &dd, QObject *parent) : QSortFilterProxyModel(parent), d_ptr(&dd)
{
    Q_D(BaseFilterModel);
    connect(this, &QAbstractProxyModel::sourceModelChanged, [this, d]() {
        if (d->bsm) {
            disconnect(d->bsm, &BaseModel::inOperationChanged, this, &BaseFilterModel::inOperationChanged);
            disconnect(d->bsm, &BaseModel::errorChanged, this, &BaseFilterModel::errorChanged);
            disconnect(d->bsm, &BaseModel::cachePeriodChanged, this, &BaseFilterModel::cachePeriodChanged);
            disconnect(d->bsm, &BaseModel::userAgentChanged, this, &BaseFilterModel::userAgentChanged);
        }
        d->bsm = qobject_cast<BaseModel *>(sourceModel());
        if (d->bsm) {
            connect(d->bsm, &BaseModel::inOperationChanged, this, &BaseFilterModel::inOperationChanged);
            connect(d->bsm, &BaseModel::errorChanged, this, &BaseFilterModel::errorChanged);
            connect(d->bsm, &BaseModel::cachePeriodChanged, this, &BaseFilterModel::cachePeriodChanged);
            connect(d->bsm, &BaseModel::userAgentChanged, this, &BaseFilterModel::userAgentChanged);
        }
    });
}


BaseFilterModel::~BaseFilterModel()
{

}


bool BaseFilterModel::inOperation() const { Q_D(const BaseFilterModel); return d->bsm ? d->bsm->inOperation() : false; }

Error BaseFilterModel::error() const { Q_D(const BaseFilterModel); return d->bsm ? d->bsm->error() : Error(); }

QString BaseFilterModel::userAgent() const { Q_D(const BaseFilterModel); return d->bsm ? d->bsm->userAgent() : QString(); }

void BaseFilterModel::setUserAgent(const QString &nUserAgent)
{
    Q_D(BaseFilterModel);
    if (d->bsm) {
        d->bsm->setUserAgent(nUserAgent);
    }
}

quint32 BaseFilterModel::cachePeriod() const { Q_D(const BaseFilterModel); return d->bsm ? d->bsm->cachePeriod() : 0; }

void BaseFilterModel::setCachePeriod(quint32 nCachePeriod)
{
    Q_D(BaseFilterModel);
    if (d->bsm) {
        d->bsm->setCachePeriod(nCachePeriod);
    }
}

QString BaseFilterModel::search() const { Q_D(const BaseFilterModel); return d->search.pattern(); }

void BaseFilterModel::setSearch(const QString &nSearch)
{
    Q_D(BaseFilterModel);
    const QString trimmed = nSearch.trimmed();
    if (d->search.pattern() != trimmed) {
        d->search.setPattern(trimmed);
        qDebug("Changed search string to \"%s\".", qUtf8Printable(trimmed));
        Q_EMIT searchChanged(trimmed);
        invalidateFilter();
    }
}

void BaseFilterModel::setSortOrder(Qt::SortOrder nSortOrder)
{
    if (sortOrder() != nSortOrder) {
        sort(0, nSortOrder);
        qDebug("Sort order changed to %i.", nSortOrder);
        Q_EMIT sortOrderChanged(nSortOrder);
    }
}

#include "moc_basefiltermodel.cpp"
