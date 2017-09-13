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
 * The CheckPwnedPassword class implements a request to the HIBP API to check if a password
 * has been pwned and is part of the HIBP database. As written in the HIBP API docs, it is
 * <B>NOT RECOMMENDED</B> to send any passwords you actively use to third-party services - even
 * haveibeenpwned.com!
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
    /*!
     * This property holds wether the \link CheckPwnedPassword::password password \endlink to check is itself
     * a SHA1 when originally used. If true, the API searches for a password which was originally a SHA1 hash,
     * causing it to be hashed again before being compared to the Pwned Password repository.
     *
     * \par Access functions
     * \li bool originalPasswordIsHash() const
     * \li void setOriginalPasswordIsHash(bool nOriginalPasswordIsHash)
     *
     * \par Notifier signal
     * \li void originalPasswordIsHashChanged(bool originalPasswordIsHash)
     */
    Q_PROPERTY(bool originalPasswordIsHash READ originalPasswordIsHash WRITE setOriginalPasswordIsHash NOTIFY originalPasswordIsHashChanged)
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
     * set before calling this function. The \a reload parameter is ignored for this API call.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Sets the A \link CheckPwnedPassword::password password \endlink to check and if it is an
     * \link CheckPwnedPassword::originalPasswordIsHash original password hash \endlink before sending
     * the request. The \a reload parameter is ignored for this API call.
     */
    Q_INVOKABLE void execute(const QString &password, bool originalPasswordIsHash = false, bool reload = false);

    /*!
     * Getter function for the \link CheckPwnedPassword::password password \endlink property.
     * \sa setPassword() passwordChanged()
     */
    QString password() const;

    /*!
     * Getter function for the \link CheckPwnedPassword::originalPasswordIsHash originalPasswordIsHash \endlink property.
     * \sa setOriginalPasswordIsHash() originalPasswordIsHashChanged()
     */
    bool originalPasswordIsHash() const;

    /*!
     * Setter function for the \link CheckPwnedPassword::password password \endlink property.
     * \sa password() passwordChanged()
     */
    void setPassword(const QString &nPassword);

    /*!
     * Setter function for the \link CheckPwnedPassword::originalPasswordIsHash originalPasswordIsHash \endlink property.
     * \sa setOriginalPasswordIsHash() originalPasswordIsHashChanged()
     */
    void setOriginalPasswordIsHash(bool nOriginalPasswordIsHash);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link CheckPwnedPassword::password password \endlink property.
     * \sa setPassword() password()
     */
    void passwordChanged(const QString &password);

    /*!
     * Notifier signal for the \link CheckPwnedPassword::originalPasswordIsHash originalPasswordIsHash \endlink property.
     * \sa setOriginalPasswordIsHash() originalPasswordIsHash()
     */
    void originalPasswordIsHashChanged(bool originalPasswordIsHash);

    /*!
     * This signal will be emitted if the \link CheckPwnedPassword::password password \endlink has been found in the HIBP
     * pwned password data. It will contain the checked password.
     */
    void passwordPwned(const QString &password);

    /*!
     * This signal will be emitted if the \link CheckPwnedPassword::password password \endlink has not been found in the HIBP
     * pwned password data. It will contain the checked password.
     */
    void passwordNotPwned(const QString &password);

protected:
    /*!
     * This will simply emit the passwordPwned() signal and will set Component::inOperation to \c false.
     */
    void successCallback(const QJsonDocument &json) override;

    /*!
     * Checks the HTTP status code of the API reply. If the status code is \c 404, the passwordNotPwned()
     * signal will be emitted, otherwise it calls Component::extractError(). At the end it sets
     * Component::inOperation to \c false.
     */
    void extractError(QNetworkReply *reply) override;
};

}

#endif // LIBINTFUORITCHECKPWNEDPASSWORD_H
