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

#ifndef LIBINTFUORITBREACH_P_H
#define LIBINTFUORITBREACH_P_H

#include "breach.h"
#include <QSharedData>

namespace Intfuorit {

class BreachData : public QSharedData
{
public:
    inline BreachData() : QSharedData() {}

    inline BreachData(const QString &_title,
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
                      const QUrl &_logoPath) :
        QSharedData(),
        dataClasses{_dataClasses},
        title{_title},
        name{_name},
        domain{_domain},
        description{_description},
        logoPath{_logoPath},
        addedDate{_addedDate},
        modifiedDate{_modifiedDate},
        breachDate{_breachDate},
        pwnCount{_pwnCount},
        isVerified{_isVerified},
        isFabricated{_isFabricated},
        isSensitive{_isSensitive},
        isActive{_isActive},
        isRetired{_isRetired},
        isSpamList{_isSpamList}
    {}

    inline BreachData(const BreachData &copy) :
        QSharedData(copy),
        dataClasses{copy.dataClasses},
        title{copy.title},
        name{copy.name},
        domain{copy.domain},
        description{copy.description},
        logoPath{copy.logoPath},
        addedDate{copy.addedDate},
        modifiedDate{copy.modifiedDate},
        breachDate{copy.breachDate},
        pwnCount{copy.pwnCount},
        isVerified{copy.isVerified},
        isFabricated{copy.isFabricated},
        isSensitive{copy.isSensitive},
        isActive{copy.isActive},
        isRetired{copy.isRetired},
        isSpamList{copy.isSpamList}
    {}

    QStringList dataClasses;
    QString title;
    QString name;
    QString domain;
    QString description;
    QUrl logoPath;
    QDateTime addedDate;
    QDateTime modifiedDate;
    QDate breachDate;
    quint32 pwnCount = 0;
    bool isVerified = false;
    bool isFabricated = false;
    bool isSensitive = false;
    bool isActive = false;
    bool isRetired = false;
    bool isSpamList = false;
};

}

#endif // LIBINTFUORITBREACH_P_H
