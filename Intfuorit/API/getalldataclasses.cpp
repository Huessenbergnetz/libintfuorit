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

#include "getalldataclasses_p.h"
#include <QJsonDocument>
#include <QJsonArray>

using namespace Intfuorit;

GetAllDataClasses::GetAllDataClasses(QObject *parent) :
    Component(* new GetAllDataClassesPrivate(this), parent)
{

}


GetAllDataClasses::~GetAllDataClasses()
{

}


void GetAllDataClasses::execute(bool reload)
{
    if (inOperation()) {
        qWarning("Getting all data classes still in progress. Aborting.");
        return;
    }

    setInOperation(true);
    setError(nullptr);

    const QUrl url = buildUrl(QStringLiteral("dataclasses"), QString());

    setCacheFileName(QStringLiteral("dataclasses.json"));

    sendRequest(url, reload);
}


void GetAllDataClasses::successCallback(const QJsonDocument &json)
{
    qDebug("Got all data classes.");
    qDebug("%s", json.toJson().constData());
    const QJsonArray a = json.array();
    Q_EMIT gotAllDataClasses(a);
    setInOperation(false);
}

#include "moc_getalldataclasses.cpp"
