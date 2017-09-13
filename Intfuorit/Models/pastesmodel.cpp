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

#include "pastesmodel_p.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

using namespace Intfuorit;


PastesModelPrivate::PastesModelPrivate(PastesModel *parent) : BaseModelPrivate(parent)
{

}

PastesModelPrivate::~PastesModelPrivate()
{

}


void PastesModelPrivate::clearModel()
{
    Q_Q(PastesModel);
    if (!list.empty()) {
        qDebug("Clearing model data.");
        q->beginRemoveRows(QModelIndex(), 0, list.size() - 1);
        qDeleteAll(list.begin(), list.end());
        list.clear();
        q->endRemoveRows();
    }
}


void PastesModelPrivate::gotPastes(const QJsonArray &a)
{
    if (!a.isEmpty()) {
        qDebug("Populating model.");
        Q_Q(PastesModel);
        q->beginInsertRows(QModelIndex(), list.size(), (list.size() + a.size() - 1));
        list.reserve(list.size() + a.size());
        for (const QJsonValue &o : a) {
            list.push_back(Paste::fromJson(o.toObject(), q_ptr));
        }
        q->endInsertRows();
    }
    setInOperation(false);
}


PastesModel::PastesModel(QObject *parent) : BaseModel(* new PastesModelPrivate(this), parent)
{

}


PastesModel::PastesModel(PastesModelPrivate &dd, QObject *parent) : BaseModel(dd, parent)
{

}

PastesModel::~PastesModel()
{

}


void PastesModel::getPastesForAccount(const QString &account, bool reload)
{
    Q_D(PastesModel);
    if (d->inOperation) {
        qWarning("Model is still working. Will not reload.");
        return;
    }

    d->setInOperation(true);

    d->clearModel();

    if (!d->gpfa) {
        d->gpfa = new GetPastesForAccount(this);
        connect(d->gpfa, &GetPastesForAccount::gotPastesForAccount, [d](const QString &account, const QJsonArray &json){
            Q_UNUSED(account);
            d->gotPastes(json);
        });
        connect(d->gpfa, &GetPastesForAccount::gotPastesForAccount, [d](){
            d->gpfa->deleteLater();
            d->gpfa = nullptr;
        });
        connect(d->gpfa, &GetPastesForAccount::errorChanged, [d](Error *e){d->setError(e);});
        connect(d->gpfa, &GetPastesForAccount::failed, [this, d](){
            d->setInOperation(false);
            d->gpfa->deleteLater();
            d->gpfa = nullptr;
            Q_EMIT failed(d->error);
        });
        connect(d->gpfa, &GetPastesForAccount::gotNoPastesForAccount, [this, d](const QString &account){
            d->setInOperation(false);
            d->gpfa->deleteLater();
            d->gpfa = nullptr;
            Q_EMIT gotNoPastesForAccount(account);
        });
    }

    d->gpfa->setCachePeriod(d->cachePeriod);
    d->gpfa->setUserAgent(d->userAgent);
    d->gpfa->execute(account, reload);
}

void PastesModel::clear()
{
    Q_D(PastesModel);
    d->clearModel();
}

#include "moc_pastesmodel.cpp"
