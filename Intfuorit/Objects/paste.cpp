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

#include "paste_p.h"
#include <QJsonObject>
#include <QJsonValue>

using namespace Intfuorit;

Paste::Paste(QObject *parent) : QObject(parent), d_ptr(new PastePrivate)
{

}


Paste::Paste(const QString &source, const QString &sourceId, const QString &title, const QDateTime &date, quint32 emailCount, QObject *parent) :
    QObject(parent), d_ptr(new PastePrivate(source, sourceId, title, date, emailCount))
{

}


Paste::~Paste()
{

}


QString Paste::source() const { Q_D(const Paste); return d->source; }

QString Paste::sourceId() const { Q_D(const Paste); return d->sourceId; }

QString Paste::title() const { Q_D(const Paste); return d->title; }

QDateTime Paste::date() const { Q_D(const Paste); return d->date; }

quint32 Paste::emailCount() const { Q_D(const Paste); return d->emailCount; }

QUrl Paste::url() const { Q_D(const Paste); return d->url; }


Paste* Paste::fromJson(const QJsonObject &o, QObject *parent)
{
    if (o.isEmpty()) {
        return new Paste(parent);
    }

    QString title = o.value(QStringLiteral("Title")).toString();
    if (title.isEmpty()) {
        //% "No title"
        title = qtTrId("libintfuorit-no-title");
    }

    return new Paste(o.value(QStringLiteral("Source")).toString(),
                     o.value(QStringLiteral("Id")).toString(),
                     title,
                     QDateTime::fromString(o.value(QStringLiteral("Date")).toString(), Qt::ISODate),
                     o.value(QStringLiteral("EmailCount")).toInt(),
                     parent);
}


Paste* Paste::clone(Paste *other, QObject *parent)
{
    Q_ASSERT_X(other, "clone paste", "invalid source object");

    return new Paste(other->source(),
                     other->sourceId(),
                     other->title(),
                     other->date(),
                     other->emailCount(),
                     parent);
}

#include "moc_paste.cpp"
