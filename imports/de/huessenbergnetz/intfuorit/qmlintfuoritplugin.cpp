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

#include <Intfuorit/Error>
#include <Intfuorit/API/CheckPwnedPassword>
#include <Intfuorit/Objects/Breach>
#include <Intfuorit/Objects/Paste>
#include <Intfuorit/Models/BreachesListFilterModel>
#include <Intfuorit/Models/BreachesListModel>
#include <Intfuorit/Models/PastesListModel>

#include <QtQml>
#include <QDebug>

class QmlIntfuoritPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid FILE "plugin.json")
public:
    QmlIntfuoritPlugin(QObject *parent = nullptr) : QQmlExtensionPlugin(parent) {}

    virtual void registerTypes(const char *uri)
    {
        if (Q_LIKELY(QLatin1String(uri) == QLatin1String("de.huessenbergnetz.intfuorit"))) {
            qDebug() << "REGISTERING TYPES!!!!!!!";
            int major = 1;
            int minor = 0;

            qRegisterMetaType<Intfuorit::Error>();
            QMetaType::registerEqualsComparator<Intfuorit::Error>();
            QMetaType::registerDebugStreamOperator<Intfuorit::Error>();
            qmlRegisterUncreatableType<Intfuorit::Error>(uri, major, minor, "Error", QStringLiteral("Intfuorit::Error can not be created in QML!"));

            qRegisterMetaType<Intfuorit::Breach>();
            QMetaType::registerEqualsComparator<Intfuorit::Breach>();
            QMetaType::registerDebugStreamOperator<Intfuorit::Breach>();

            qRegisterMetaType<Intfuorit::Paste>();
            QMetaType::registerEqualsComparator<Intfuorit::Paste>();
            QMetaType::registerDebugStreamOperator<Intfuorit::Paste>();

            qmlRegisterType<Intfuorit::BreachesListModel        >(uri, major, minor, "BreachesListModel");
            qmlRegisterType<Intfuorit::BreachesListFilterModel  >(uri, major, minor, "BreachesListFilterModel");
            qmlRegisterType<Intfuorit::PastesListModel          >(uri, major, minor, "PastesListModel");
            qmlRegisterType<Intfuorit::CheckPwnedPassword       >(uri, major, minor, "CheckPwnedPassword");
        } else {
            qCritical() << "Unsupported URI given to load Intfuorit QML plugin: " << QLatin1String(uri);
        }
    }
};

#include "qmlintfuoritplugin.moc"
