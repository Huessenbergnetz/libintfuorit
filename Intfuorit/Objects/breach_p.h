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

#ifndef LIBINTFUORITBREACH_P_H
#define LIBINTFUORITBREACH_P_H

#include "breach.h"

namespace Intfuorit {

class BreachPrivate
{
public:
    BreachPrivate() {}

    BreachPrivate(const QString &_title,
                  const QString &_name,
                  const QString &_domain,
                  QDate _breachDate,
                  const QDateTime &_addedDate,
                  const QDateTime &_modifiedDate,
                  quint32 _pwnCount,
                  const QString &_description,
                  const QStringList &_dataClasses,
                  bool _isVerified,
                  bool _isFabricated,
                  bool _isSensitive,
                  bool _isActive,
                  bool _isRetired,
                  bool _isSpamList,
                  const QString &_logoType) :
        title(_title),
        name(_name),
        domain(_domain),
        breachDate(_breachDate),
        addedDate(_addedDate),
        modifiedDate(_modifiedDate),
        pwnCount(_pwnCount),
        description(_description),
        dataClasses(_dataClasses),
        isVerified(_isVerified),
        isFabricated(_isFabricated),
        isSensitive(_isSensitive),
        isActive(_isActive),
        isRetired(_isRetired),
        isSpamList(_isSpamList),
        logoType(_logoType)
    {}

    ~BreachPrivate() {}

    QString title;
    QString name;
    QString domain;
    QDate breachDate;
    QDateTime addedDate;
    QDateTime modifiedDate;
    quint32 pwnCount = 0;
    QString description;
    QStringList dataClasses;
    bool isVerified = false;
    bool isFabricated = false;
    bool isSensitive = false;
    bool isActive = false;
    bool isRetired = false;
    bool isSpamList = false;
    QString logoType;
};

}

#endif // LIBINTFUORITBREACH_P_H
