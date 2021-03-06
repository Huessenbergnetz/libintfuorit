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

#ifndef INTFUORITERROR_P_H
#define INTFUORITERROR_P_H

#include "error.h"

namespace Intfuorit {

class ErrorData : public QSharedData
{
public:
    inline ErrorData() : QSharedData() {}
    inline ErrorData(Error::Type _type, Error::Severity _severity, const QString &_text) :
        QSharedData(),
        text{_text},
        type{_type},
        severity{_severity}
    {}

    inline ErrorData(const ErrorData &copy) :
        QSharedData(copy),
        text{copy.text},
        type{copy.type},
        severity{copy.severity}
    {}

    inline void clear() {
        text.clear();
        type = Error::NoError;
        severity = Error::Nothing;
    }

    void printOut()
    {
        switch(severity) {
        case Error::Warning:
            qWarning("Error type %i: %s", type, qUtf8Printable(text));
            break;
        case Error::Critical:
            qCritical("Error type %i: %s", type, qUtf8Printable(text));
            break;
        case Error::Fatal:
            qFatal("Error type %i, %s", type, qUtf8Printable(text));
            break;
        default:
            break;
        }
    }

    QString text;
    Error::Type type = Error::NoError;
    Error::Severity severity = Error::Nothing;
};

}

#endif // INTFUORITERROR_P_H
