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

#ifndef LIBINTFUORITCHECKPWNEDPASSWORD_H
#define LIBINTFUORITCHECKPWNEDPASSWORD_H

#include <QObject>
#include "component.h"
#include "../intfuorit_global.h"

class QJsonObject;
class QJsonDocument;

namespace Intfuorit {

class CheckPwnedPasswordPrivate;

/*!
 * The %CheckPwnedPassword class implements a request to the HIBP API to check if a password
 * has been pwned and is part of the HIBP database. The password itself will not be send
 * to the HIBP API. Only the first 5 characters of a SHA1 hash of the password will be send
 * to the API.
 *
 * \par HIBP API Docs
 * <A HREF="https://haveibeenpwned.com/API/v2#PwnedPasswords">Pwned Passwords</A>
 *
 * \headerfile "" <Intfuorit/API/CheckPwnedPassword>
 * \since libintfuorit 1.0.0
 */
class INTFUORITSHARED_EXPORT CheckPwnedPassword : public Component
{
    Q_OBJECT
    Q_DISABLE_COPY(CheckPwnedPassword)
    Q_DECLARE_PRIVATE(CheckPwnedPassword)
    /*!
     * This property holds the password that should be checked against the HIBP API.
     *
     * \par Access functions
     * \li QString password() const
     * \li void setPassword(const QString &nPassword)
     *
     * \par Notifier function
     * \li void passwordChanged(const QString &password)
     */
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
public:
    /*!
     * Constructs a new CheckPwnedPassword object with the given \a parent.
     */
    explicit CheckPwnedPassword(QObject *parent = nullptr);

    /*!
     * Deconstructs the CheckPwnedPassword object.
     */
    ~CheckPwnedPassword();

    /*!
     * Starts the API request. A \link CheckPwnedPassword::password password \endlink to check has to be
     * set before calling this function.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Sets the A \link CheckPwnedPassword::password password \endlink to check starts the API request.
     */
    Q_INVOKABLE void execute(const QString &password, bool reload = false);

    /*!
     * Getter function for the \link CheckPwnedPassword::password password \endlink property.
     * \sa setPassword() passwordChanged()
     */
    QString password() const;

    /*!
     * Setter function for the \link CheckPwnedPassword::password password \endlink property.
     * \sa password() passwordChanged()
     */
    void setPassword(const QString &nPassword);

    /*!
     * Checks if the \a password has been pwned and returns the number of times the \a password has been found.
     * If \a reload is set to \c false, cached results will be returned where the default cache time (2 days)
     * will be used.
     *
     * If \a userAgent is empty, a default user agent will be created, using QCoreApplication::applicationName()
     * and QCoreApplication::applicationVersion(). Note that the HIBP API does not allow sending an empty user
     * agent string.
     *
     * If an error occures, \c -1 will be returned.
     *
     * This function performs a synchronous request and will block the event loop until the request has finished
     * or failed.
     *
     * \since libintfuorit 2.0.0
     */
    static int check(const QString &password, const QString &userAgent = QString(), bool reload = false);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link CheckPwnedPassword::password password \endlink property.
     * \sa setPassword() password()
     */
    void passwordChanged(const QString &password);

    /*!
     * This signal will be emitted if the password has been checked successfully.
     * \a count will contain the number of times the password has been seen before.
     * \since libintfuorit 2.0.0
     */
    void passwordChecked(int count);

protected:
    /*!
     * This does nothing.
     */
    void successCallback(const QJsonDocument &json) override;

    /*!
     * Will check the returned list of hashes for occurence of the password to check and
     * emits the passwordChecked() signal.
     */
    void successCallback(const QByteArray &data) override;

    /*!
     * Checks the HTTP status code of the API reply. If the status code is \c 404, the passwordNotPwned()
     * signal will be emitted, otherwise it calls Component::extractError(). At the end it sets
     * Component::inOperation to \c false.
     */
    void extractError(QNetworkReply *reply) override;
};

}

#endif // LIBINTFUORITCHECKPWNEDPASSWORD_H
