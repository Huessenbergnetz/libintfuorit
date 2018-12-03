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

#ifndef LIBINTFUORITGETALLDATACLASSES_P_H
#define LIBINTFUORITGETALLDATACLASSES_P_H

#include "getalldataclasses.h"
#include "component_p.h"

namespace Intfuorit {

class GetAllDataClassesPrivate : public ComponentPrivate
{
    Q_DISABLE_COPY(GetAllDataClassesPrivate)
public:
    explicit GetAllDataClassesPrivate(GetAllDataClasses *parent) :
        ComponentPrivate(parent)
    {
        expectedJSONType = ComponentPrivate::Array;
        namOperation = QNetworkAccessManager::GetOperation;
    }
};

}

#endif // LIBINTFUORITGETALLDATACLASSES_P_H
