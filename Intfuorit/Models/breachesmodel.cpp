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

#include "breachesmodel_p.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

using namespace Intfuorit;

BreachesModelPrivate::BreachesModelPrivate(BreachesModel *parent) : BaseModelPrivate(parent)
{

}


BreachesModelPrivate::~BreachesModelPrivate()
{

}


void BreachesModelPrivate::clearModel()
{
    Q_Q(BreachesModel);
    if (!list.empty()) {
        qDebug("Clearing model data.");
        q->beginRemoveRows(QModelIndex(), 0, list.size() - 1);
        list.clear();
        q->endRemoveRows();
    }
}


void BreachesModelPrivate::gotBreaches(const QJsonArray &a)
{
    if (!a.isEmpty()) {
        qDebug("Populating model.");
        Q_Q(BreachesModel);
        q->beginInsertRows(QModelIndex(), list.size(), (list.size() + a.size() - 1));
        list.reserve(list.size() + a.size());
        for (const QJsonValue &o : a) {
            list.push_back(Breach::fromJson(o.toObject()));
        }
        q->endInsertRows();
    }
    setInOperation(false);
}


BreachesModel::BreachesModel(QObject *parent) : BaseModel(* new BreachesModelPrivate(this), parent)
{

}


BreachesModel::BreachesModel(BreachesModelPrivate &dd, QObject *parent) : BaseModel(dd, parent)
{

}


BreachesModel::~BreachesModel()
{

}


void BreachesModel::getAllBreaches(bool reload)
{
    getAllBreaches(QString(), reload);
}


void BreachesModel::getAllBreaches(const QString &domain, bool reload)
{
    Q_D(BreachesModel);
    if (d->inOperation) {
        qWarning("Model is still working. Will not reload.");
        return;
    }

    d->setInOperation(true);

    d->clearModel();

    if (!d->gab) {
        d->gab = new GetAllBreaches(this);
        connect(d->gab, &GetAllBreaches::gotAllBreaches, this, [d](const QJsonArray &json){d->gotBreaches(json);});
        connect(d->gab, &GetAllBreaches::gotAllBreaches, this, [d](){
            d->gab->deleteLater();
            d->gab = nullptr;
        });
        connect(d->gab, &GetAllBreaches::errorChanged, this, [d](const Error &e){d->setError((e));});
        connect(d->gab, &GetAllBreaches::failed, this, [this, d](){
            d->setInOperation(false);
            d->gab->deleteLater();
            d->gab = nullptr;
            Q_EMIT failed(d->error);
        });
    }

    d->gab->setCachePeriod(d->cachePeriod);
    d->gab->setUserAgent(d->userAgent);
    d->gab->execute(domain, reload);
}


void BreachesModel::getBreachesForAccount(const QString &account, const QString &domain, bool includeUnverified, bool reload)
{
    Q_D(BreachesModel);
    if (d->inOperation) {
        qWarning("Model is still working. Will not reload.");
        return;
    }

    d->setInOperation(true);

    d->clearModel();

    if (!d->gbfa) {
        d->gbfa = new GetBreachesForAccount(this);
        connect(d->gbfa, &GetBreachesForAccount::gotBreachesForAccount, this, [d](const QString &account, const QJsonArray &json){Q_UNUSED(account); d->gotBreaches(json);});
        connect(d->gbfa, &GetBreachesForAccount::gotBreachesForAccount, this, [d](){
            d->gbfa->deleteLater();
            d->gbfa = nullptr;
        });
        connect(d->gbfa, &GetBreachesForAccount::errorChanged, this, [d](const Error &e){d->setError((e));});
        connect(d->gbfa, &GetBreachesForAccount::failed, this, [this, d](){
            d->setInOperation(false);
            d->gbfa->deleteLater();
            d->gbfa = nullptr;
            Q_EMIT failed(d->error);
        });
        connect(d->gbfa, &GetBreachesForAccount::gotNoBreachesForAccount, this, [this, d](const QString &account){
            d->setInOperation(false);
            d->gbfa->deleteLater();
            d->gbfa = nullptr;
            Q_EMIT gotNoBreachesForAccount(account);
        });
    }

    d->gbfa->setCachePeriod(d->cachePeriod);
    d->gbfa->setUserAgent(d->userAgent);
    d->gbfa->execute(account, domain, false, includeUnverified, reload);
}

void BreachesModel::clear()
{
    Q_D(BreachesModel);
    d->clearModel();
}

#include "moc_breachesmodel.cpp"
