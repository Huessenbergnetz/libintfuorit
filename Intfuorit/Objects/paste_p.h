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

#ifndef LIBINTFUORITPAST_P_H
#define LIBINTFUORITPAST_P_H

#include "paste.h"
#include <QStringBuilder>

namespace Intfuorit {

class PastePrivate
{
public:
    PastePrivate() {}

    PastePrivate(const QString &_source, const QString &_sourceId, const QString &_title, const QDateTime &_date, quint32 _emailcount) :
        source(_source),
        sourceId(_sourceId),
        title(_title),
        date(_date),
        emailCount(_emailcount)
    {
        QUrl _url;
        if (source == QLatin1String("Pastebin")) {
            _url.setScheme(QStringLiteral("https"));
            _url.setHost(QStringLiteral("pastebin.com"));
            _url.setPath(QLatin1Char('/') % sourceId);
        } else if (source == QLatin1String("Pastie")) {
            _url.setScheme(QStringLiteral("https"));
            _url.setHost(QStringLiteral("www.pastiebin.com"));
            _url.setPath(QLatin1Char('/') % sourceId);
        } else if (source == QLatin1String("Slexy")) {
            _url.setScheme(QStringLiteral("https"));
            _url.setHost(QStringLiteral("slexy.org"));
            _url.setPath(QLatin1String("/view/") % sourceId);
        } else if (source == QLatin1String("Ghostbin")) {
            _url.setScheme(QStringLiteral("https"));
            _url.setHost(QStringLiteral("ghostbin.com"));
            _url.setPath(QLatin1String("/paste/") % sourceId);
        } else if (source == QLatin1String("QuickLeak")) {
            _url.setScheme(QStringLiteral("https"));
            _url.setHost(QStringLiteral("www.quickleak.org"));
            _url.setPath(QLatin1Char('/') % sourceId);
        } else if (source == QLatin1String("JustPaste")) {
            _url.setScheme(QStringLiteral("https"));
            _url.setHost(QStringLiteral("justpaste.it"));
            _url.setPath(QLatin1Char('/') % sourceId);
        } else if (source == QLatin1String("AdHocUrl")) {
            _url.setUrl(sourceId);
        }

        if (_url.isValid()) {
            url = _url;
        }
    }

    QUrl url;
    QString source;
    QString sourceId;
    QString title;
    QDateTime date;
    quint32 emailCount;
};

}

#endif // LIBINTFUORITPAST_P_H
