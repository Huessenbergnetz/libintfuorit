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

#ifndef INTFUORITCOMPONENT_P_H
#define INTFUORITCOMPONENT_P_H

#include "component.h"
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QTimer>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QStandardPaths>
#include <QFileInfo>
#include <QNetworkAccessManager>

namespace Intfuorit {

class ComponentPrivate
{
    Q_DISABLE_COPY(ComponentPrivate)
    Q_DECLARE_PUBLIC(Component)
    Component * const q_ptr;
public:
    explicit ComponentPrivate(Component *parent);

    virtual ~ComponentPrivate();

    /*!
     * \internal
     * \brief Defines the expected JSON type.
     */
    enum ExpectedJSONType {
        Empty   = 0,    /**< Expects an empty body in the reply. */
        Array   = 1,    /**< Expects a JSON array in the reply body. */
        Object  = 2     /**< Expects a JSON object in the reply body. */
    };

    QNetworkRequest buildRequest(const QUrl &url, int contentLength = 0) const;
    void requestFinished();
    void requestTimedOut();
    void requestReadyRead();
    QJsonDocument checkOutput(const QByteArray &result, bool *checkResult);
    bool isInCache() const;
    bool openCacheFile(QIODevice::OpenMode mode);
    bool removeCacheFile();

    QNetworkAccessManager *nam = nullptr;
    QNetworkAccessManager::Operation namOperation = QNetworkAccessManager::GetOperation;
    bool inOperation = false;
    quint8 requestTimeout = 120;
    Error *error = nullptr;
    QString userAgent;

    QTimer *timeoutTimer = nullptr;
    ExpectedJSONType expectedJSONType = Empty;
    QNetworkReply *reply = nullptr;

    quint32 cachePeriod = 3600*48; // two days
    bool useCache = false;

    QFile cacheFile;
    QString cacheDirPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
};

}

#endif // INTFUORITCOMPONENT_P_H
