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

#ifndef LIBINTFUORITCHECKPWNEDPASSWORD_P_H
#define LIBINTFUORITCHECKPWNEDPASSWORD_P_H

#include "checkpwnedpassword.h"
#include "component_p.h"

namespace Intfuorit {

class CheckPwnedPasswordPrivate : public ComponentPrivate
{
    Q_DISABLE_COPY(CheckPwnedPasswordPrivate)
public:
    explicit CheckPwnedPasswordPrivate(CheckPwnedPassword *parent) :
        ComponentPrivate(parent)
    {
        expectedJSONType = ComponentPrivate::PlainText;
        namOperation = QNetworkAccessManager::GetOperation;
    }

    QString password;
    QString pwPrefix;
    QString pwSuffix;
    int count = -1;
};

}

#endif // LIBINTFUORITCHECKPWNEDPASSWORD_P_H
