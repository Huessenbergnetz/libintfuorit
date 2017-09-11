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

#include "basemodel_p.h"

using namespace Intfuorit;


BaseModelPrivate::BaseModelPrivate(BaseModel *parent) : q_ptr(parent)
{

}


BaseModelPrivate::~BaseModelPrivate()
{

}


void BaseModelPrivate::setInOperation(bool nInOperation)
{
    if (inOperation != nInOperation) {
        inOperation = nInOperation;
        qDebug("inOperation changed to %s.", inOperation ? "true" : "false");
        Q_Q(BaseModel);
        Q_EMIT q->inOperationChanged(inOperation);
    }
}


void BaseModelPrivate::setError(Error *nError)
{
    Q_Q(BaseModel);
    Error *old = nullptr;
    if (error && nError) {
        if (*error != *nError) {
            old = error;
            if (nError->parent() == q_ptr) {
                error = nError;
            } else if ((nError->parent() == nullptr) && (nError->thread() == q_ptr->thread())) {
                error = nError;
                error->setParent(q_ptr);
            } else {
                error = Error::clone(nError, q_ptr);
                if (nError->parent() == nullptr) {
                    delete nError;
                }
            }
            Q_EMIT q->errorChanged(error);
        } else {
            if ((nError->parent() == q_ptr) || (nError->parent() == nullptr)) {
                delete nError;
            }
        }
    } else if (error && !nError) {
        old = error;
        error = nError;
        Q_EMIT q->errorChanged(nError);
    } else if (!error && nError) {
        if (nError->parent() == q_ptr) {
            error = nError;
        } else {
            error = Error::clone(nError, q_ptr);
        }
        Q_EMIT q->errorChanged(error);
    }

    if (old && ((old->parent() == q_ptr) || (old->parent() == nullptr))) {
        delete old;
    }
}


BaseModel::BaseModel(QObject *parent) : QAbstractItemModel(parent), d_ptr(new BaseModelPrivate(this))
{

}


BaseModel::BaseModel(BaseModelPrivate &dd, QObject *parent) : QAbstractItemModel(parent), d_ptr(&dd)
{

}


BaseModel::~BaseModel()
{

}


bool BaseModel::inOperation() const
{
    Q_D(const BaseModel);
    return d->inOperation;
}


Error* BaseModel::error() const
{
    Q_D(const BaseModel);
    return d->error;
}


quint32 BaseModel::cachePeriod() const { Q_D(const BaseModel); return d->cachePeriod; }

void BaseModel::setCachePeriod(quint32 nCachePeriod)
{
    Q_D(BaseModel);
    if (d->cachePeriod != nCachePeriod) {
        d->cachePeriod = nCachePeriod;
        qDebug("Cache period changed to %u seconds.", nCachePeriod);
        Q_EMIT cachePeriodChanged(nCachePeriod);
    }
}

QString BaseModel::userAgent() const { Q_D(const BaseModel); return d->userAgent; }

void BaseModel::setUserAgent(const QString &nUserAgent)
{
    Q_D(BaseModel);
    if (d->userAgent != nUserAgent) {
        d->userAgent = nUserAgent;
        qDebug("User agent changed to \"%s\".", qUtf8Printable(nUserAgent));
        Q_EMIT userAgentChanged(nUserAgent);
    }
}

#include "moc_basemodel.cpp"
