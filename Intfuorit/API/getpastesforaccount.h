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

#ifndef LIBINTFUORITGETPASTESFORACCOUNT_H
#define LIBINTFUORITGETPASTESFORACCOUNT_H

#include "component.h"

namespace Intfuorit {

class Paste;
class GetPastesForAccountPrivate;

/*!
 * \ingroup api
 * Implements a request to get all pastes an email address occures in from the HIBP API.
 * Set the email address to the \link GetPastesForAccount::account account \endlink property
 * and call execute() to start the request.
 *
 * If there are pastes found on HIBP the \link GetPastesForAccount::account email addres \endlink is
 * part of, the gotPastesForAccount() will be emitted. If there are no pates, gotNoPastesForAccount()
 * will be emitted. If something failed, the Component::failed() signal will be emitted.
 *
 * For this API call it is mandator to set an \link GetPastesForAccount::account email addres \endlink.
 *
 * \par HIBP API docs
 * <a href="https://haveibeenpwned.com/API/v2#PastesForAccount" rel="external noopener">Getting all pastes for an account</a>
 *
 * \headerfile "" <Intfuorit/API/GetPastesForAccount>
 * \sa Paste, PastesListModel, PastesListFilterModel
 */
class INTFUORITSHARED_EXPORT GetPastesForAccount : public Component
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GetPastesForAccount)
    Q_DISABLE_COPY(GetPastesForAccount)
    /*!
     * This property holds the email addres used for an \a account to search the pastes for.
     * Other than with GetBreachesForAccount, this has to be a valid email address, the API
     * does not work with account user names when searching for pastes.
     *
     * \par Access functions
     * \li QString account() const
     * \li void setAccount(const QString &nAccount)
     *
     * \par Notifier signal
     * \li void accountChanged(const Qtring &account)
     */
    Q_PROPERTY(QString account READ account WRITE setAccount NOTIFY accountChanged)
public:
    /*!
     * Constructs a new %GetPastesForAccount with the given \a parent.
     */
    explicit GetPastesForAccount(QObject *parent = nullptr);

    /*!
     * Deconstructs the %GetPastesForAccount object.
     */
    ~GetPastesForAccount();

    /*!
     * Starts the API request. An \link GetPastesForAccount::account email address \endlink has to be set
     * before calling this function. Set \a reload to \c true to circumvent the cache file and to load
     * directly from the API. If something failed, the Component::failed() signal will be emitted. If there
     * were pastes found the \link GetPastesForAccount::account email address \endlink is part of, the
     * gotPastesForAccount() signal will be emitted, if no pastes were found the gotNoPastesForAccount()
     * signal will be emitted.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Sets the \link GetPastesForAccount::account account \endlink and starts the API request.
     * The \a account has to be an email address. Set \a reload to \c true to circumvent the cache
     * file and to load directly from the API.
     *
     * \overload
     */
    Q_INVOKABLE void execute(const QString &account, bool reload = false);

    /*!
     * Getter function for the \link GetPastesForAccount::account account \endlink property.
     * \sa setAccount() accountChanged()
     */
    QString account() const;

    /*!
     * Setter function for the \link GetPastesForAccount::account account \endlink property.
     * \sa account() accountChanged()
     */
    void setAccount(const QString &nAccount);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link GetPastesForAccount::account account \endlink property.
     * \sa setAccount() account()
     */
    void accountChanged(const QString &account);

    /*!
     * This signal will be emitted when the request has finished and the \link GetPastesForAccount::account email address \endlink
     * has been found in one or more pastes. It will contain the queried \a account name and the \a pastes the
     * email address was found in.
     */
    void gotPastesForAccount(const QString &account, const QVector<Paste> &pastes);

    /*!
     * This signal will be emitted when the request has finished and the  \link GetPastesForAccount::account email address \endlink
     * has not been found in the pastes data of HIBP. It will contain the queried \a account name.
     */
    void gotNoPastesForAccount(const QString &account);

protected:
    /*!
     * Extracts the pastes \a json array data from the reply, sets Component::inOperation to \c false and
     * emit the gotPastesForAccount() signal.
     */
    void successCallback(const QJsonDocument &json) override;
    /*!
     * Checks the HTTP status code of the API reply. If the status code is \c 404, the
     * gotNoPastesForAccount() signal will be emitted, otherwise it calls Component::extractError().
     * At the end it sets Component::inOperation to \c false.
     */
    void extractError(QNetworkReply *reply) override;
};

}

#endif // LIBINTFUORITGETPASTESFORACCOUNT_H
