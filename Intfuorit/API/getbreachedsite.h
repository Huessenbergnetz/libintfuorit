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

#ifndef LIBINTFUORITGETBREACHEDSITE_H
#define LIBINTFUORITGETBREACHEDSITE_H

#include <QObject>
#include "component.h"
#include "../intfuorit_global.h"

class QJsonObject;
class QJsonDocument;

namespace Intfuorit {

class GetBreachedSitePrivate;

/*!
 * The GetBreachedSite class implements a request to get a single breached site,
 * identified by the internal HIBP API \link GetBreachedSite::name name \endlink,
 * from the HIBP API.
 *
 * \par HIBP API Docs
 * <A HREF="https://haveibeenpwned.com/API/v2#SingleBreach">Getting a single breached site</A>
 *
 * \headerfile "" <Intfuorit/API/GetBreachedSite>
 * \since libintfuorit 1.0.0
 * \sa Breach, BreachesListMode, BreachesListFilterModel, GetAllBreaches, GetBreachesForAccount
 */
class INTFUORITSHARED_EXPORT GetBreachedSite : public Component
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GetBreachedSite)
    Q_DISABLE_COPY(GetBreachedSite)
    /*!
     * This property holds the HIBP internal name of the breached site to request
     * data for from the API. Setting this property will trim the name automatically.
     * Setting this property is mandatory to request the data from the API.
     *
     * \par Access functions
     * \li QString name() const
     * \li void setName(const QString &nName)
     *
     * \par Notified signal
     * \li void nameChanged(const QString &name)
     */
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    /*!
     * Constructs a new GetBreachedSite object with the given \a parent.
     */
    explicit GetBreachedSite(QObject *parent = nullptr);

    /*!
     * Deconstructs the GetBreachedSite object.
     */
    ~GetBreachedSite();

    /*!
     * Starts the API request. Set \a reload to \c true to circumvent the local cache
     * file and to load directly from the API. A valid site \link GetBreachedSite::name name \endlink
     * has to be set before calling this function. If something failed, the Component::failed() signal
     * will be emitted, on success, the gotBreach() signal will be emitted containg the breached site
     * data.
     */
    Q_INVOKABLE void execute(bool reload = false) override;

    /*!
     * Sets the \link GetBreachedSite::name name \endlink of the breached site to request and start the API call.
     * Set \a reload to \c true to circumvent the local cache file and to load directly from the API.
     *
     * \overload
     */
    Q_INVOKABLE void execute(const QString &name, bool reload = false);

    /*!
     * Getter function for the \link GetBreachedSite::name name \endlink property.
     * \sa setName() nameChanged()
     */
    QString name() const;

    /*!
     * Setter function for the \link GetBreachedSite::name name \endlink property.
     * \sa name() nameChanged()
     */
    void setName(const QString &nName);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link GetBreachedSite::name name \endlink property.
     * \sa setName() name()
     */
    void nameChanged(const QString &name);

    /*!
     * This signal will be emitted when the request to the HIBP API was successfull. It will contain
     * the breached site data as JSON object. See the <A HREF="https://haveibeenpwned.com/API/v2#BreachModel">HIBP API docs</A>
     * for a description of the JSON breach object values.
     */
    void gotBreach(const QJsonObject &breach);

protected:
    /*!
     * Extracts the breach \a json object data from the reply, set Component::inOperation to \c false and
     * emit the gotBreach() signal.
     */
    void successCallback(const QJsonDocument &json) override;
};

}

#endif // LIBINTFUORITGETBRECHEDSITE_H
