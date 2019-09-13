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

#ifndef LIBINTFUORITGETBREACHESFORACCOUNT_P_H
#define LIBINTFUORITGETBREACHESFORACCOUNT_P_H

#include "getbreachesforaccount.h"
#include "component_p.h"

namespace Intfuorit {

class GetBreachesForAccountPrivate : public ComponentPrivate
{
    Q_DISABLE_COPY(GetBreachesForAccountPrivate)
public:
    explicit GetBreachesForAccountPrivate(GetBreachesForAccount *parent) :
        ComponentPrivate(parent)
    {
        expectedJSONType = ComponentPrivate::Array;
        namOperation = QNetworkAccessManager::GetOperation;
        useApiKey = true;
    }

    QString domain;
    QString account;
    bool truncateResponse = false;
    bool includeUnverified = false;
};

}

#endif // LIBINTFUORITGETBREACHESFORACCOUNT_P_H
