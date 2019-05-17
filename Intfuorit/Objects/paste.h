/* libintfuorit - Qt library to access the API of haveibeenpwned.com
 * Copyright (C) 2017-2019 Hüssenbergnetz / Matthias Fehring
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


#ifndef LIBINTFUORITPASTE_H
#define LIBINTFUORITPASTE_H

#include "../intfuorit_global.h"
#include <QObject>
#include <QDateTime>
#include <QString>
#include <QUrl>
#include <QSharedDataPointer>

class QJsonObject;

namespace Intfuorit {

class PasteData;

/*!
 * \brief The Paste class contains information about a single paste.
 *
 * \par HIBP API Docs
 * <A HREF="https://haveibeenpwned.com/API/v2#PasteModel"></A>
 *
 * \headerfile "" <Intfuorit/Objects/Paste>
 * \sa PastesListModel, PastesListFilterModel, GetPastesForAccount
 */
class INTFUORITSHARED_EXPORT Paste
{
    Q_GADGET
    /*!
     * This property holds the paste service the record was retrieved from.
     * Current values are: Pastebin, Pastie, Slexy, Ghostbin, QuickLeak, JustPaste, AdHocUrl, OptOut
     *
     * \par Access functions
     * \li QString source() const
     */
    Q_PROPERTY(QString source READ source CONSTANT)
    /*!
     * This property holds the ID of the paste as it was given at the source service.
     * Combined with the \link Paste::source source \endlink property, this this will be used to resolve
     * the \link Paste::url url \endlink of the paste.
     *
     * \par Access functions
     * \li QString sourceId() const
     */
    Q_PROPERTY(QString sourceId READ sourceId CONSTANT)
    /*!
     * This property holds the title of the paste as observed on the source site.
     * This may be null.
     *
     * \par Access functions
     * \li QString title() const
     */
    Q_PROPERTY(QString title READ title CONSTANT)
    /*!
     * This property holds the date and time (precision to the second) that the paste was posted.
     * This is taken directly from the paste site when this information is available but may be
     * null if no date is published.
     *
     * \par Access functions
     * \li QDateTime date() const
     */
    Q_PROPERTY(QDateTime date READ date CONSTANT)
    /*!
     * This property holds the number of emails that were found when processing the paste.
     * Emails are extracted by using a regular expression.
     *
     * \par Access functions
     * \li quint32 emailCount() const
     */
    Q_PROPERTY(quint32 emailCount READ emailCount CONSTANT)
    /*!
     * This property holds the URL to the paste. This will be resolved from the \link Paste::source source \endlink service
     * and the \link Paste::sourceId sourceId \endlink of the paste. Might be null if the URL could not
     * be resolved.
     *
     * \par Access functions
     * \li QUrl url() const
     */
    Q_PROPERTY(QUrl url READ url CONSTANT)
public:
    /*!
     * Constructs a new empty %Paste object.
     */
    Paste();

    /*!
     * Constructs a new %Paste with the given parameters.
     */
    Paste(const QString &source, const QString &sourceId, const QString &title, const QDateTime &date, quint32 emailCount);

    /*!
     * Constructs a copy of \a other.
     */
    Paste(const Paste &other);

    /*!
     * Assigns \a other to this %Paste and returns a reference to this %Paste.
     */
    Paste &operator=(const Paste &other);

    /*!
     * Move-assigns \a other this this %Paste.
     */
    Paste &operator=(Paste &&other) noexcept;

    /*!
     * Deconstructs the Paste object.
     */
    ~Paste();

    /*!
     * Swaps this %Paste with \a other.
     */
    void swap(Paste &other) noexcept;

    /*!
     * Getter function for the \link Paste::source source \endlink property.
     */
    QString source() const;
    /*!
     * Getter function for the \link Paste::sourceId sourceId \endlink property.
     */
    QString sourceId() const;
    /*!
     * Getter function for the \link Paste::title title \endlink property.
     */
    QString title() const;
    /*!
     * Getter function for the \link Paste::date date \endlink property.
     */
    QDateTime date() const;
    /*!
     * Getter function for the \link Paste::emailCount emailCount \endlink property.
     */
    quint32 emailCount() const;
    /*!
     * Getter function for the \link Paste::url url \endlink property.
     */
    QUrl url() const;

    /*!
     * Compares the \a other %Paste's values to this %Paste and returns \c true if it is equal.
     */
    bool operator==(const Paste &other) const;

    /*!
     * Compares the \a other %Paste's values to this %Paste and returns \c true if it is equal.
     */
    bool operator!=(const Paste &other) const;

    /*!
     * Creates a new Paste object from JSON object \a o.
     */
    static Paste fromJson(const QJsonObject &o);

protected:
    QSharedDataPointer<PasteData> d;
};

}

Q_DECLARE_TYPEINFO(Intfuorit::Paste, Q_MOVABLE_TYPE);

/*!
 * \relates Intfuorit::Paste
 * \brief Writes the \a paste to the \a dbg stream and returns the stream.
 */
QDebug operator<<(QDebug dbg, const Intfuorit::Paste &pate);

#endif // LIBINTFUORITPASTE_H
