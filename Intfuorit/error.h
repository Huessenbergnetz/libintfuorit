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

#ifndef INTFUORITERROR_H
#define INTFUORITERROR_H

#include "intfuorit_global.h"
#include <QObject>
#include <QVariant>
#include <QSharedDataPointer>

class QNetworkReply;
struct QJsonParseError;

namespace Intfuorit {

class ErrorData;

/*!
 * Provides information about occurred errors.
 *
 * \headerfile "" <Intfuorit/Error>
 */
class INTFUORITSHARED_EXPORT Error
{
    Q_GADGET
    /*!
     * This property holds the human readable error description.
     *
     * \par Access functions:
     * \li QString text() const
     */
    Q_PROPERTY(QString text READ text CONSTANT)
    /*!
     * This property holds the error type.
     *
     * \par Access functions:
     * \li Error::Type type() const
     */
    Q_PROPERTY(Intfuorit::Error::Type type READ type CONSTANT)
    /*!
     * This property hold the error severity.
     *
     * \par Access functions:
     * \li Error::Severity severity() const
     */
    Q_PROPERTY(Intfuorit::Error::Severity severity READ severity CONSTANT)
public:
    /*!
     * Defines the error type.
     */
    enum Type : quint8 {
        NoError             = 0,    /**< No error has occurred. */
        RequestError        = 1,    /**< The request was not setup correctly. */
        JSONParsingError    = 2,    /**< Failed to parse JSON data. */
        InputError          = 3,    /**< An error occurred while providing data to the library methods. */
        OutputError         = 4,    /**< An error occurred while processing the returned data from the API. */
        ServerError         = 5,    /**< An error occurred on the server. */
        ApplicationError    = 6,    /**< An error occurred in the local application. */
        FileError           = 7     /**< Failed to open, read or write a file. */
    };
    Q_ENUM(Type)

    /*!
     * Defines the severity of the error.
     */
    enum Severity : quint8 {
        Nothing     = 0,    /**< No error has occurred */
        Warning     = 1,    /**< Only a warning, but operation was perfmormed */
        Critical    = 2,    /**< A critical error has occurred, the operation has been canceled */
        Fatal       = 3     /**< A fatal error has occurred, the application will be exited */
    };
    Q_ENUM(Severity)

    /*!
     * Constructs a new empty %Error object of Type NoError.
     */
    explicit Error();

    /*!
     * \brief Constructs a new Error object with the given parameters and \a parent.
     * Use appropriate values for \a type and \a severity and set a descriptive humand readable
     * error \a text.
     */
    Error(Type type, Severity severity, const QString &text);

    /*!
     * Constructs a new Error object from QNetworkReply \a reply with the given \a parent.
     */
    explicit Error(QNetworkReply *reply);

    /*!
     * Constructs a new Error object from QJsonError \a jsonError with the given \a parent.
     */
    explicit Error(const QJsonParseError jsonError);

    /*!
     * Constructs a copy of \a other.
     */
    Error(const Error &other);

//    /*!
//     * Move-constructs an %Error instance, making it point at the same object \a other is pointing to.
//     */
//    Error(Error &&error) noexcept;

    /*!
     * Assings \a other to this %Error and returns a reference to this error.
     */
    Error &operator=(const Error &other);

    /*!
     * Move-assigns \a other to this %Error instance.
     */
    Error &operator=(Error &&other) noexcept;

    /*!
     * Deconstructs the %Error object.
     */
    ~Error();

    /*!
     * Swaps this %Error instance with \a other.
     */
    void swap(Error &other) noexcept;

    /*!
     * Getter function for the \link Error::type type \endlink property.
     */
    Type type() const;

    /*!
     * Getter function for the \link Error::severity severity \endlink property.
     */
    Severity severity() const;

    /*!
     * Getter function for the \link Error::text text \endlink property.
     */
    QString text() const;

    /*!
     * Compare the \a other error's values to this error and returns \c true if it is equal.
     */
    bool operator==(const Error &other) const;

    /*!
     * Compare the \a other error's values to this error and returns \c true if it is not equal.
     */
    bool operator!=(const Error &other) const;

protected:
    QSharedDataPointer<ErrorData> d;
};

}

Q_DECLARE_TYPEINFO(Intfuorit::Error, Q_MOVABLE_TYPE);

#endif // INTFUORITERROR_H
