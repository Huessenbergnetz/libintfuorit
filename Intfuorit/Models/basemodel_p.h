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

#ifndef LIBINTFUORITBASEMODEL_P_H
#define LIBINTFUORITBASEMODEL_P_H

#include "basemodel.h"

namespace Intfuorit {

class BaseModelPrivate
{
    Q_DISABLE_COPY(BaseModelPrivate)
    Q_DECLARE_PUBLIC(BaseModel)
public:
    explicit BaseModelPrivate(BaseModel *parent);

    virtual ~BaseModelPrivate();

    void setInOperation(bool nInOperation);
    void setError(const Error &nError);

    QString userAgent;
    Error error;
    quint32 cachePeriod = 172800;
    bool inOperation = false;

protected:
    BaseModel * const q_ptr;
};

}

#endif // LIBINTFUORITBASEMODEL_P_H
