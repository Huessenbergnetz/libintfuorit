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

#include <QObject>
#include <QVariant>
#include "intfuorit_global.h"

class QNetworkReply;
struct QJsonParseError;

namespace Intfuorit {

class ErrorPrivate;

/*!
 * \brief Provides information about occurred errors.
 *
 * \headerfile "" <Intfuorit/Error>
 */
class INTFUORITSHARED_EXPORT Error : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Error)
    Q_DECLARE_PRIVATE(Error)
    /*!
     * \brief Text describing the error in a human readable way.
     *
     * \par Access functions:
     * \li QString text() const
     * \par Notifier signal:
     * \li void textChanged(const QString &text)
     */
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    /*!
     * \brief Type of the error.
     *
     * \par Access functions:
     * \li Error::Type type() const
     * \par Notifier signal:
     * \li void typeChanged(Error::Type type)
     */
    Q_PROPERTY(Intfuorit::Error::Type type READ type NOTIFY typeChanged)
    /*!
     * \brief Additional error data.
     *
     * \par Access functions:
     * \li QVariant() data() const
     * \par Notifier signal:
     * \li void dataChanged(const QVariant &data)
     */
    Q_PROPERTY(QVariant data READ data NOTIFY dataChanged)
    /*!
     * \brief The severity of the error.
     *
     * \par Access functions:
     * \li Error::Severity severity() const
     * \par Notifier signal:
     * \li void severityChanged(Error::Severity severity)
     */
    Q_PROPERTY(Intfuorit::Error::Severity severity READ severity NOTIFY severityChanged)
public:
    /*!
     * \brief Defines the error type.
     */
    enum Type {
        NoError             = 0,    /**< No error has occurred. */
        RequestError        = 1,    /**< The request was not setup correctly. */
        JSONParsingError    = 2,    /**< Failed to parse JSON data. */
        InputError          = 3,    /**< An error occurred while providing data to the library methods. */
        OutputError         = 4,    /**< An error occurred while processing the returned data from the API. */
        ServerError         = 5,    /**< An error occurred on the server. */
        ApplicationError    = 6,    /**< An error occurred in the local application. */
    };
    Q_ENUM(Type)

    /*!
     * \brief Defines the severity of the error.
     */
    enum Severity {
        Nothing     = 0,    /**< No error has occurred */
        Warning     = 1,    /**< Only a warning, but operation was perfmormed */
        Critical    = 2,    /**< A critical error has occurred, the operation has been canceled */
        Fatal       = 3     /**< A fatal error has occurred, the application will be exited */
    };
    Q_ENUM(Severity)

    /*!
     * \brief Constructs a new empty Error object with the given \a parent.
     */
    explicit Error(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Error object with the given parameters.
     * \param type      The Type of the error.
     * \param severity  The Severity of the error.
     * \param text      The human readable text to describe the error.
     * \param data      Optinal additional error data.
     * \param parent    Parent object.
     */
    Error(Type type, Severity severity, const QString &text, const QVariant &data = QVariant(), QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Error object from a QNetworkReply.
     * \param reply     The network reply to construct the error from.
     * \param parent    The parent object.
     */
    explicit Error(QNetworkReply *reply, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Error object from a QJsonParseError.
     * \param jsonError The JSON parse error data.
     * \param parent    The parent object.
     */
    explicit Error(QJsonParseError jsonError, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Error object.
     */
    ~Error();

    /*!
     * \brief Getter function for the \link Error::type type \endlink property.
     * \sa Error::setType() Error::typeChanged()
     */
    Type type() const;

    /*!
     * \brief Getter function for the \link Error::severity severity \endlink property.
     * \sa Error::setSeverity() Error::severityChanged()
     */
    Severity severity() const;

    /*!
     * \brief Getter function for the \link Error::text text \endlink property.
     * \sa Error::setText() Error::textChanged()
     */
    QString text() const;

    /*!
     * \brief Getter function for the \link Error::data data \endlink property.
     * \sa Error::setData() Error::dataChanged()
     */
    QVariant data() const;


    /*!
     * \brief Sets the Type of this error.
     * \sa Error::type() Error::typeChanged()
     */
    void setType(Type nType);

    /*!
     * \brief Sets the Severity of this error.
     * \sa Error::severity() Error::severityChanged()
     */
    void setSeverity(Severity nSeverity);

    /*!
     * \brief Sets the humand readable error string of this error
     * \sa Error::text() Error::textChanged()
     */
    void setText(const QString &nText);

    /*!
     * \brief Sets the optional additional data for this error.
     * \sa Error::data() Error::dataChanged()
     */
    void setData(const QVariant &nData);

Q_SIGNALS:
    /*!
     * \brief Notifier function for the \link Error::type type \endlink property.
     * \sa Error::setType() Error::type()
     */
    void typeChanged(Type type);

    /*!
     * \brief Notifier function for the \link Error::severity severity \endlink property.
     * \sa Error::setSeverity() Error::severity()
     */
    void severityChanged(Severity severity);

    /*!
     * \brief Notifier function for the \link Error::text text \endlink property.
     * \sa Error::setText() Error::text()
     */
    void textChanged(const QString &text);

    /*!
     * \brief Notifier function for the \link Error::data data \endlink property.
     * \sa Error::setData() Error::data()
     */
    void dataChanged(const QVariant &data);

protected:
    const QScopedPointer<ErrorPrivate> d_ptr;
};

}

#endif // INTFUORITERROR_H
