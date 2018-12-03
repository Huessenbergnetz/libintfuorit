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

#ifndef LIBINTFUORITGETBREACHEDSITE_P_H
#define LIBINTFUORITGETBREACHEDSITE_P_H

#include "getbreachedsite.h"
#include "component_p.h"

namespace Intfuorit {

class GetBreachedSitePrivate : public ComponentPrivate
{
    Q_DISABLE_COPY(GetBreachedSitePrivate)
public:
    explicit GetBreachedSitePrivate(GetBreachedSite *parent) :
        ComponentPrivate(parent)
    {
        expectedJSONType = ComponentPrivate::Object;
        namOperation = QNetworkAccessManager::GetOperation;
    }

    QString name;
};

}

#endif // LIBINTFUORITGETBREACHEDSITE_P_H
