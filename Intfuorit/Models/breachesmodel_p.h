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

#ifndef LIBINTFUORITBREACHESMODEL_P_H
#define LIBINTFUORITBREACHESMODEL_P_H

#include "breachesmodel.h"
#include "basemodel_p.h"
#include "../API/getallbreaches.h"
#include "../API/getbreachesforaccount.h"
#include "../Objects/breach.h"
#include <QVector>

namespace Intfuorit {

class BreachesModelPrivate : public BaseModelPrivate
{
    Q_DISABLE_COPY(BreachesModelPrivate)
    Q_DECLARE_PUBLIC(BreachesModel)
public:
    explicit BreachesModelPrivate(BreachesModel *parent);

    ~BreachesModelPrivate();

    void gotBreaches(const QVector<Breach> &breaches);

    void clearModel();

    QVector<Breach> list;

    GetAllBreaches *gab = nullptr;
    GetBreachesForAccount *gbfa = nullptr;
};

}

#endif // LIBINTFUORITBREACHESMODEL_P_H
