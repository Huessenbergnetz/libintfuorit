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

#ifndef LIBINTFUORITBREACHESLISTMODEL_P_H
#define LIBINTFUORITBREACHESLISTMODEL_P_H

#include "breacheslistmodel.h"
#include "breachesmodel_p.h"

namespace Intfuorit {

class BreachesListModelPrivate : public BreachesModelPrivate
{
    Q_DISABLE_COPY(BreachesListModelPrivate)
    Q_DECLARE_PUBLIC(BreachesListModel)
public:
    explicit BreachesListModelPrivate(BreachesListModel *parent) : BreachesModelPrivate(parent) {}
    ~BreachesListModelPrivate() {}
};

}

#endif // LIBINTFUORITBREACHESLISTMODEL_P_H
