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

#include "breach_p.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

using namespace Intfuorit;

Breach::Breach(QObject *parent) :
    QObject(parent), d_ptr(new BreachPrivate)
{

}


Breach::Breach(const QString &title, const QString &name, const QString &domain, QDate breachDate, const QDateTime &addedDate, const QDateTime &modifiedDate, quint32 pwnCount, const QString &description, const QStringList &dataClasses, bool isVerified, bool isFabricated, bool isSensitive, bool isActive, bool isRetired, bool isSpamList, const QString &logoType, QObject *parent) :
    QObject(parent), d_ptr(new BreachPrivate(title, name, domain, breachDate, addedDate, modifiedDate, pwnCount, description, dataClasses, isVerified, isFabricated, isSensitive, isActive, isRetired, isSpamList, logoType))
{
    setObjectName(name);
}


Breach::~Breach()
{

}


QString Breach::title() const { Q_D(const Breach); return d->title; }

QString Breach::name() const { Q_D(const Breach); return d->name; }

QString Breach::domain() const { Q_D(const Breach); return d->domain; }

QDate Breach::breachDate() const { Q_D(const Breach); return d->breachDate; }

QDateTime Breach::addedDate() const { Q_D(const Breach); return d->addedDate; }

QDateTime Breach::modifiedDate() const { Q_D(const Breach); return d->modifiedDate; }

quint32 Breach::pwnCount() const { Q_D(const Breach); return d->pwnCount; }

QString Breach::description() const { Q_D(const Breach); return d->description; }

QStringList Breach::dataClasses() const { Q_D(const Breach); return d->dataClasses; }

bool Breach::isVerified() const { Q_D(const Breach); return d->isVerified; }

bool Breach::isFabricated() const { Q_D(const Breach); return d->isFabricated; }

bool Breach::isSensitive() const { Q_D(const Breach); return d->isSensitive; }

bool Breach::isActive() const { Q_D(const Breach); return d->isActive; }

bool Breach::isRetired() const { Q_D(const Breach); return d->isRetired; }

bool Breach::isSpamList() const { Q_D(const Breach); return d->isSpamList; }

QString Breach::logoType() const { Q_D(const Breach); return d->logoType; }


Breach* Breach::fromJson(const QJsonObject &o, QObject *parent)
{
    if (o.isEmpty()) {
        return new Breach(parent);
    }

    const QJsonArray dataClassesArray = o.value(QStringLiteral("DataClasses")).toArray();
    QStringList dataClasses;
    dataClasses.reserve(dataClassesArray.size());
    for (const QJsonValue &dc : dataClassesArray) {
        dataClasses << dc.toString();
    }

    return new Breach(o.value(QStringLiteral("Title")).toString(),
                      o.value(QStringLiteral("Name")).toString(),
                      o.value(QStringLiteral("Domain")).toString(),
                      QDate::fromString(o.value(QStringLiteral("BreachDate")).toString(), QStringLiteral("yyyy-MM-dd")),
                      QDateTime::fromString(o.value(QStringLiteral("AddedDate")).toString(), Qt::ISODate),
                      QDateTime::fromString(o.value(QStringLiteral("ModifiedDate")).toString(), Qt::ISODate),
                      o.value(QStringLiteral("PwnCount")).toInt(),
                      o.value(QStringLiteral("Description")).toString(),
                      dataClasses,
                      o.value(QStringLiteral("IsVerified")).toBool(),
                      o.value(QStringLiteral("IsFabricated")).toBool(),
                      o.value(QStringLiteral("IsSensitive")).toBool(),
                      o.value(QStringLiteral("IsActive")).toBool(),
                      o.value(QStringLiteral("IsRetired")).toBool(),
                      o.value(QStringLiteral("IsSpamList")).toBool(),
                      o.value(QStringLiteral("LogoType")).toString(),
                      parent);
}


Breach* Breach::clone(Breach *other, QObject *parent)
{
    Q_ASSERT_X(other, "clone breach", "invalid source object");

    return new Breach(other->title(),
                      other->name(),
                      other->domain(),
                      other->breachDate(),
                      other->addedDate(),
                      other->modifiedDate(),
                      other->pwnCount(),
                      other->description(),
                      other->dataClasses(),
                      other->isVerified(),
                      other->isFabricated(),
                      other->isSensitive(),
                      other->isActive(),
                      other->isRetired(),
                      other->isSpamList(),
                      other->logoType(),
                      parent);
}

#include "moc_breach.cpp"
