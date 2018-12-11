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
#include <QDebug>

using namespace Intfuorit;

Paste::Paste() : d(new PasteData)
{

}

Paste::Paste(const QString &source, const QString &sourceId, const QString &title, const QDateTime &date, quint32 emailCount) :
    d(new PasteData(source, sourceId, title, date, emailCount))
{

}

Paste::Paste(const Paste &other) :
    d(other.d)
{

}

Paste& Paste::operator=(const Paste &other)
{
    d = other.d;
    return *this;
}

Paste& Paste::operator=(Paste &&other) noexcept
{
    swap(other);
    return *this;
}

Paste::~Paste()
{

}

void Paste::swap(Paste &other) noexcept
{
    std::swap(d, other.d);
}

QString Paste::source() const { return d->source; }

QString Paste::sourceId() const { return d->sourceId; }

QString Paste::title() const { return d->title; }

QDateTime Paste::date() const { return d->date; }

quint32 Paste::emailCount() const { return d->emailCount; }

QUrl Paste::url() const { return d->url; }

bool Paste::operator==(const Paste &other) const
{
    return (d->source == other.source() && d->sourceId == other.sourceId());
}

bool Paste::operator!=(const Paste &other) const
{
    return (d->source != other.source() || d->sourceId != other.sourceId());
}

Paste Paste::fromJson(const QJsonObject &o)
{
    if (o.isEmpty()) {
        return Paste();
    }

    QString title = o.value(QStringLiteral("Title")).toString();
    if (title.isEmpty()) {
        //% "No title"
        title = qtTrId("libintfuorit-no-title");
    }

    return {
        o.value(QStringLiteral("Source")).toString(),
        o.value(QStringLiteral("Id")).toString(),
        title,
        QDateTime::fromString(o.value(QStringLiteral("Date")).toString(), Qt::ISODate),
        static_cast<quint32>(o.value(QStringLiteral("EmailCount")).toDouble())
    };
}

QDebug operator<<(QDebug dbg, const Intfuorit::Paste &paste)
{
    QDebugStateSaver saver(dbg);
    Q_UNUSED(saver);
    dbg.nospace() << "Intfuorit::Paste(";
    dbg << "Source: " << paste.source();
    dbg << ", SourceID: " << paste.sourceId();
    dbg << ", Title: " << paste.title();
    dbg << ", Date: " << paste.date();
    dbg << ", EmailCount: " << paste.emailCount();
    dbg << ", URL: " << paste.url();
    dbg << ')';
    return dbg.maybeSpace();
}

#include "moc_paste.cpp"
