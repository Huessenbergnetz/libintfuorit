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

#ifndef LIBINTFUORITBASEFILTERMODEL_P_H
#define LIBINTFUORITBASEFILTERMODEL_P_H

#include "basefiltermodel.h"
#include "basemodel.h"
#include <QStringMatcher>

#define INTFUORIT_GET_MODEL(Class) \
    inline Class * intf_get_model() { return reinterpret_cast<Class *>(bsm); } \
    inline const Class * intf_get_model() const { return reinterpret_cast<const Class *>(bsm); }

namespace Intfuorit {

class BaseFilterModelPrivate
{
    Q_DISABLE_COPY(BaseFilterModelPrivate)
public:
    explicit BaseFilterModelPrivate()
    {
        search.setCaseSensitivity(Qt::CaseInsensitive);
    }

    virtual ~BaseFilterModelPrivate() {}

    BaseModel *bsm = nullptr;

    QStringMatcher search;
};

}


#endif // LIBINTFUORITBASEFILTERMODEL_P_H
