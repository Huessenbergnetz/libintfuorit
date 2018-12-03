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

#ifndef INTFUORITNETWORKACCESSMANAGERFACTORY_H
#define INTFUORITNETWORKACCESSMANAGERFACTORY_H

#include <QObject>
#include "intfuorit_global.h"

class QNetworkAccessManager;

namespace Intfuorit {

/*!
 * The %NetworkAccessManagerFactory class create QNetworkAccessManager instances for the
 * requests to the HIBP API.
 *
 * The Intfuorit API request classes use QNetworkAccessManager for all network access. By
 * implementing a factory, it is possible to provide the request classes with custom
 * QNetworkAccessManager instances with specialized caching, proxy and cookies support.
 *
 * To implement a factory, subclass NetworkAccessManagerFactory and implement the virtual create()
 * method, then assign it global to the API request classes by using Component::setNetworkAccessManagerFactory().
 *
 * \headerfile "" <Intfuorit/NetworkAccessManagerFactory>
 */
class INTFUORITSHARED_EXPORT NetworkAccessManagerFactory
{
    Q_DISABLE_COPY(NetworkAccessManagerFactory)
public:
    /*!
     * Destroys the factory. The default implementation does nothing.
     */
    virtual ~NetworkAccessManagerFactory();

    /*!
     * Creates and returns a network access manager with the specified \a parent. This method
     * must return a new QNetworkAccessManager instance each time it is called.
     */
    virtual QNetworkAccessManager *create(QObject *parent) = 0;
};

}

#endif // INTFUORITNETWORKACCESSMANAGERFACTORY_H
