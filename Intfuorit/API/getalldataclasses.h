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

#ifndef LIBINTFUORITGETALLDATACLASSES_H
#define LIBINTFUORITGETALLDATACLASSES_H

#include "component.h"

namespace Intfuorit {

class GetAllDataClassesPrivate;

/*!
 * \ingroup api
 * The %GetAllDataClasses class implements a request to get all data classes from the HIBP API.
 * A "data class" is an attribute of a record compromised in a breach. For example, many breaches
 * expose data classes such as "Email addresses" and "Passwords".
 *
 * \par HIBP API docs
 * <a href="https://haveibeenpwned.com/API/v2#AllDataClasses" rel="external noopener">Getting all data classes in the system</a>
 *
 * \headerfile "" <Intfuorit/API/GetAllDataClasses>
 */
class INTFUORITSHARED_EXPORT GetAllDataClasses : public Component
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GetAllDataClasses)
    Q_DISABLE_COPY(GetAllDataClasses)
public:
    /*!
     * Constructs a new %GetAllDataClasses object with the given \a parent.
     */
    explicit GetAllDataClasses(QObject *parent = nullptr);

    /*!
     * Deconstructs the %GetAllDataClasses object.
     */
    ~GetAllDataClasses();

    /*!
     * Starts the API request. Set \a reload to \c true to circumvent the local cache
     * file and to load directly from the API. If the request was successful, the
     * gotAllDataClasses() signal will be emitted, otherwise the Component::failed()
     * signal will be emitted.
     *
     * \note This function can be invoked via the meta-object system and from QML. See Q_INVOKABLE.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Gets the list of available data classes from the HIBP API. If \a reload is set to
     * \c false, cached results will be returned where the default cache time (2 days) will
     * be used.
     *
     * f \a userAgent is empty, a default user agent will be created, using QCoreApplication::applicationName()
     * and QCoreApplication::applicationVersion(). Note that the HIBP API does not allow sending an empty user
     * agent string.
     *
     * If \a ok ist not \c nullptr, failure is reported by setting \a *ok to \c false, and success
     * by setting \a *ok to \c true.
     *
     * This function performs a synchronous request and will block the event loop until the request has finished
     * or failed.
     */
    static QStringList get(const QString &userAgent = QString(), bool reload = false, bool *ok = nullptr);

Q_SIGNALS:
    /*!
     * This signal will be emitted when the API request was successful and returned the
     * list of data classes in the HIBP system. The \a dataClasses string list will
     * contain the list of data classes.
     */
    void gotAllDataClasses(const QStringList &dataClasses);

protected:
    /*!
     * Extracts the data classes \a json data from the reply, sets Component::inOperation to
     * \c false and emits the gotAllDataClasses() signal.
     */
    void successCallback(const QJsonDocument &json) override;
};

}

#endif // LIBINTFUORITGETALLDATACLASSES_H
