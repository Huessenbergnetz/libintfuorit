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

#ifndef LIBINTFUORITBREACH_H
#define LIBINTFUORITBREACH_H

#include <QObject>
#include <QDate>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QUrl>
#include "../intfuorit_global.h"

class QJsonObject;

namespace Intfuorit {

class BreachPrivate;

/*!
 * \brief The Breach class contains information about a single breach.
 *
 * \par HIBP API Docs
 * <A HREF="https://haveibeenpwned.com/API/v2#BreachModel">The breach model</A>
 *
 * \headerfile "" <Intfuorit/Objects/Breach>
 * \since libinitfuorit 1.0.0
 * \sa BreachesListModel, BreachesListFilterModel, GetAllBreaches, GetBreachedSite, GetBreachesForAccount
 */
class INTFUORITSHARED_EXPORT Breach : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Breach)
    Q_DECLARE_PRIVATE(Breach)
    /*!
     * This property holds the descriptive title for the breach suitable for displaying to end users.
     * It's unique across all breaches but individual values may change in the future (i.e. if another
     * breach occurs against an organisation already in the system). If a stable value is required to
     * reference the breach, refer to the \link Breach::name name \endlink property instead.
     *
     * \par Access functions
     * \li QString title() const
     */
    Q_PROPERTY(QString title READ title CONSTANT)
    /*!
     * This property holds a Pascal-cased name representing the breach which is unique across all
     * other breaches. This value never changes and may be used to name dependent assets (such as
     * images) but should not be shown directly to end users (see the \link Breach::title title \endlink
     * property instead).
     *
     * \par Access functions
     * \li QString name() const
     */
    Q_PROPERTY(QString name READ name CONSTANT)
    /*!
     * This property holds the domain of the primary website the breach occurred on. This may be used
     * for identifying other assets external systems may have for the site.
     *
     * \par Access functions
     * \li QString domain() const
     */
    Q_PROPERTY(QString domain READ domain CONSTANT)
    /*!
     * This property holds the date (with no time) the breach originally occurred on. This is not always
     * accurate — frequently breaches are discovered and reported long after the original incident.
     * Use this property as a guide only.
     *
     * \par Access functions
     * \li QDate breachDate() const
     */
    Q_PROPERTY(QDate breachDate READ breachDate CONSTANT)
    /*!
     * This property holds the date and time (precision to the minute) the breach was added to the HIBP system.
     *
     * \par Access functions
     * \li QDateTime addedDate() const
     */
    Q_PROPERTY(QDateTime addedDate READ addedDate CONSTANT)
    /*!
     * This property holds the date and time (precision to the minute) the breach was modified in the HIBP system.
     * This will only differ from the \link Breach::addedDate addedDate \endlink property if other attributes
     * represented here are changed or data in the breach itself is changed (i.e. additional data is identified
     * and loaded). It is always either equal to or greater then the \link Breach::addedDate addedDate \endlink
     * property, never less than.
     *
     * \par Access functions
     * \li QDateTime modifiedDate() const
     */
    Q_PROPERTY(QDateTime modifiedDate READ modifiedDate CONSTANT)
    /*!
     * This property holds the total number of accounts loaded into the HIBP system. This is usually less than
     * the total number reported by the media due to duplication or other data integrity issues in the source data.
     *
     * \par Access functions
     * \li quint32 pwnCount() const
     */
    Q_PROPERTY(quint32 pwnCount READ pwnCount CONSTANT)
    /*!
     * This property holds an overview of the breach represented in HTML markup. The description may include markup
     * such as emphasis and strong tags as well as hyperlinks.
     *
     * \par Access functions
     * \li QString description() const
     */
    Q_PROPERTY(QString description READ description CONSTANT)
    /*!
     * This property holds a list of attributes describing the nature of the data compromised in the breach. It is
     * an alphabetically orders list of strings of impacted data classes.
     *
     * \par Access functions
     * \li QStringList dataClasses() const
     */
    Q_PROPERTY(QStringList dataClasses READ dataClasses CONSTANT)
    /*!
     * This property holds translated names of the values available in the \link Breach::dataClasses dataClasse \endlink
     * property.
     *
     * \par Access functions
     * \li QStringList dataClassesTranslated() const
     *
     * \sa Breach::dataClasses
     */
    Q_PROPERTY(QStringList dataClassesTranslated READ dataClassesTranslated CONSTANT)
    /*!
     * This property indicates that the breach is considered unverified. An unverified breach may not have been
     * hacked from the indicated website. An unverified breach is still loaded into HIBP when there's sufficient
     * confidence that a significant portion of the data is legitimate.
     *
     * \par Access functions
     * \li bool isVerified() const
     */
    Q_PROPERTY(bool isVerified READ isVerified CONSTANT)
    /*!
     * This property indicates that the breach is considered fabricated. A fabricated breach is unlikely to have
     * been hacked from the indicated website and usually contains a large amount of manufactured data. However,
     * it still contains legitimate email addresses and asserts that the account owners were compromised in the
     * alleged breach.
     *
     * \par Access functions
     * \li bool isFabricated() const
     */
    Q_PROPERTY(bool isFabricated READ isFabricated CONSTANT)
    /*!
     * This property indicates if the breach is considered sensitive. The public API will not return any accounts
     * for a breach flagged as sensitive.
     *
     * \par Access functions
     * \li bool isSensitive() const
     */
    Q_PROPERTY(bool isSensitive READ isSensitive CONSTANT)
    /*!
     * This property holds something unkonwn it seems.
     *
     * \par Access functions
     * \li bool isActive() const
     */
    Q_PROPERTY(bool isActive READ isActive CONSTANT)
    /*!
     * This property indicates if the breach has been retired. This data has been permanently removed and will not
     * be returned by the API.
     *
     * \par Access functions
     * \li bool isRetired() const
     */
    Q_PROPERTY(bool isRetired READ isRetired CONSTANT)
    /*!
     * This property indicates if the breach is considered a spam list. This flag has no impact on any other properties
     * but it means that the data has not come as a result of a security compromise.
     *
     * \par Access functions
     * \li bool isSpamList() const
     */
    Q_PROPERTY(bool isSpamList READ isSpamList CONSTANT)
    /*!
     * This property holds the file type of the breaches site's logo.
     *
     * \par Access functions
     * \li QString logoType() const
     *
     * \deprecated Not returned by the API anymore, use \link Breach::logoPath logoPath \endlink
     */
    Q_PROPERTY(QString logoType READ logoType CONSTANT)
    /*!
     * This property holds the HTTP URL to the breched site's logo.
     *
     * \par Access functions
     * \li QUrl logoPath() const
     *
     * \since libintfuorit 1.1.0
     */
    Q_PROPERTY(QUrl logoPath READ logoPath CONSTANT)
public:
    /*!
     * \brief Constructs a new empty Breach object.
     */
    explicit Breach(QObject *parent = nullptr);

    /*!
     * Constructs a new Breach with the given parameters and \a parent.
     * All data parameters belong to one of the properties of the Breach class,
     * look at the properties to learn more about the parameters.
     *
     * \deprecated logoType is not returned by the API anymore. Use the constructor that
     * has the logoPath argument
     */
    Q_DECL_DEPRECATED_X("logoType is not returned anymore by the API, use the constructor that has the logoPath argument") Breach(const QString &title,
           const QString &name,
           const QString &domain,
           QDate breachDate,
           const QDateTime &addedDate,
           const QDateTime &modifiedDate,
           quint32 pwnCount,
           const QString &description,
           const QStringList &dataClasses,
           bool isVerified,
           bool isFabricated,
           bool isSensitive,
           bool isActive,
           bool isRetired,
           bool isSpamList,
           const QString &logoType,
           QObject *parent = nullptr);

    /*!
     * Constructs a new Breach with the given parameters and \a parent.
     * All data parameters belong to one of the properties of the Breach class,
     * look at the properties to learn more about the parameters.
     */
    Breach(const QString &title,
               const QString &name,
               const QString &domain,
               QDate breachDate,
               const QDateTime &addedDate,
               const QDateTime &modifiedDate,
               quint32 pwnCount,
               const QString &description,
               const QStringList &dataClasses,
               bool isVerified,
               bool isFabricated,
               bool isSensitive,
               bool isActive,
               bool isRetired,
               bool isSpamList,
               const QUrl &logoPath,
               QObject *parent = nullptr);



    /*!
     * Deconstructs the Breach object.
     */
    ~Breach();

    /*!
     * Getter function for the \link Breach::title title \endlink property.
     */
    QString title() const;
    /*!
     * Getter function for the \link Breach::name name \endlink property.
     */
    QString name() const;
    /*!
     * Getter function for the \link Breach::domain domain \endlink property.
     */
    QString domain() const;
    /*!
     * Getter function for the \link Breach::breachDate breachDate \endlink property.
     */
    QDate breachDate() const;
    /*!
     * Getter function for the \link Breach::addedDate addedDate \endlink property.
     */
    QDateTime addedDate() const;
    /*!
     * Getter function for the \link Breach::modifiedDate modifiedDate \endlink property.
     */
    QDateTime modifiedDate() const;
    /*!
     * Getter function for the \link Breach::pwnCount pwnCount \endlink property.
     */
    quint32 pwnCount() const;
    /*!
     * Getter function for the \link Breach::description description \endlink property.
     */
    QString description() const;
    /*!
     * Getter function for the \link Breach::dataClasses dataClasses \endlink property.
     */
    QStringList dataClasses() const;
    /*!
     * Getter function for the \link Breach::dataClassesTranslated dataClassesTranslated \endlink property.
     */
    QStringList dataClassesTranslated() const;
    /*!
     * Getter function for the \link Breach::isVerified isVerified \endlink property.
     */
    bool isVerified() const;
    /*!
     * Getter function for the \link Breach::isFabricated isFabricated \endlink property.
     */
    bool isFabricated() const;
    /*!
     * Getter function for the \link Breach::isSensitive isSensitive \endlink property.
     */
    bool isSensitive() const;
    /*!
     * Getter function for the \link Breach::isActive isActive \endlink property.
     */
    bool isActive() const;
    /*!
     * Getter function for the \link Breach::isRetired isRetired \endlink property.
     */
    bool isRetired() const;
    /*!
     * Getter function for the \link Breach::isSpamList isSpamList \endlink property.
     */
    bool isSpamList() const;
    /*!
     * Getter function for the \link Breach::logoType logoType \endlink property.
     * \deprecated Not returned by the API anymore, use logoPath()
     */
    Q_DECL_DEPRECATED_X("Not returned by the API anymore, use logoPath()") QString logoType() const;
    /*!
     * Getter function for the \link Breach::logoPath logoPath \endlink property.
     * \since libintfuorit 1.1.0
     */
    QUrl logoPath() const;

    /*!
     * \brief Creates a new Breach object from JSON object \a o with the given \a parent and returns the pointer to it.
     */
    static Breach* fromJson(const QJsonObject &o, QObject *parent = nullptr);

    /*!
     * \brief Clones the Breach \a other by creating a new Breach with the given \a parent and \a other's values.
     */
    static Breach* clone(Breach *other, QObject *parent = nullptr);

protected:
    const QScopedPointer<BreachPrivate> d_ptr;
};

}

#endif // LIBINTFUORITBREACH_H
