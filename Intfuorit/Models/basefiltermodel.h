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

#ifndef LIBINTFUORITBASEFILTERMODEL_H
#define LIBINTFUORITBASEFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "../intfuorit_global.h"

#define INTF_MODEL(Class) Class * const model = d->intf_get_model()

namespace Intfuorit {

class Error;
class BaseFilterModelPrivate;

/*!
 * \brief The BaseFilterModel class is the base class for all Intfuorit sort and filter proxy models.
 *
 * Do not use this class directly, use one of the derived classes.
 *
 * BaseFilterModel and its subclasses in libintfuorit use a
 * <a href="https://techbase.kde.org/Policies/Library_Code_Policy/Shared_D-Pointer_Example">shared D-pointer</a>.
 *
 * \headerfile "" <Intfuorit/Model/basefiltermodel.h>
 * \since libintfuorit 1.0.0
 */
class INTFUORITSHARED_EXPORT BaseFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_DISABLE_COPY(BaseFilterModel)
    Q_DECLARE_PRIVATE(BaseFilterModel)
    /*!
     * This property holds wether the model is loading data.
     *
     * \par Access functions
     * \li bool inOperation() const
     *
     * \par Notifier signal
     * \li void inOperationChanged(bool inOperation)
     */
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    /*!
     * This property holds a pointer to the last occured Error. If no error has occured, it holds a \c nullptr.
     *
     * \par Access functions
     * \li Error* error() const
     *
     * \par Notifier signal
     * \li void errorChanged(Error *error)
     */
    Q_PROPERTY(Error* error READ error NOTIFY errorChanged)
    /*!
     * This property holds the cache time in seconds. For more information see Component::cachePeriod.
     * The default value of this property is \c 172800 seconds (2 days).
     *
     * \par Access functions
     * \li quint32 cachePeriod() const
     * \li void setCachePeriod(quint32 nCachePeriod)
     *
     * \par Notifier signal
     * \li void cachePeriodChanged(quint32 cachePeriod)
     */
    Q_PROPERTY(quint32 cachePeriod READ cachePeriod WRITE setCachePeriod NOTIFY cachePeriodChanged)
    /*!
     * This property holds the user agent  that will be added to the API request. For more information
     * see Component::userAgent.
     *
     * \par Access functions
     * \li QString userAgent() const
     * \li void setUserAgent(const QString &nUserAgent)
     *
     * \par Notifier signal
     * \li void userAgentChanged(const QString &userAgent)
     */
    Q_PROPERTY(QString userAgent READ userAgent WRITE setUserAgent NOTIFY userAgentChanged)
    /*!
     * This property holds the search string that will be used to filter the model data.
     *
     * \par Access functions
     * \li QString serach() const
     * \li void setSearch(const QString &nSearch)
     *
     * \par Notifier signal
     * \li void searchChanged(const QString &search)
     */
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    /*!
     * This property holds the sort order that will be used to sort the model.
     *
     * \par Access functions
     * \li int QSortFilterProxyModel::sortOrder() const
     * \li void setSortOrder(Qt::SortOrder nSortOrder)
     */
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
public:
    /*!
     * Constructs a new BaseFilterModel with the given \a parent.
     */
    explicit BaseFilterModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the BaseFilterModel object.
     */
    ~BaseFilterModel();

    /*!
     * Getter function for the \link BaseFilterModel::inOperation inOperation \endlink property.
     * \sa inOperationChanged()
     */
    bool inOperation() const;

    /*!
     * Getter function fro the \link BaseFilterModel::error error \endlink property.
     * \sa errorChanged() const;
     */
    Error* error() const;

    /*!
     * Getter function for the \link BaseFilterModel::cachePeriod cachePeriod \endlink property.
     * \sa setCachePeriod() cachePeriodChanged()
     */
    quint32 cachePeriod() const;

    /*!
     * Getter function for the \link BaseFilterModel::userAgent userAgent \endlink property.
     * \sa setUserAgent() userAgentChanged()
     */
    QString userAgent() const;

    /*!
     * Getter function for the \link BaseFilterModel::search search \endlink property.
     * \sa setSearch() searchChanged()
     */
    QString search() const;

    /*!
     * Setter function for the \link BaseFilterModel::cachePeriod cachePeriod \endlink property.
     * \sa cachePeriod() cachePeriodChanged()
     */
    void setCachePeriod(quint32 nCachePeriod);

    /*!
     * Setter function for the \link BaseFilterModel::userAgent userAgent \endlink property.
     * \sa userAgent() userAgentChanged()
     */
    void setUserAgent(const QString &nUserAgent);

    /*!
     * Setter function for the \link BaseFilterModel::search search \endlink property.
     * \sa search() searchChanged()
     */
    void setSearch(const QString &nSearch);

    /*!
     * Setter function for the \link BaseFilterModel::sortOrder sortOder \endlink property.
     * \sa QSortFilterProxyModel::sortOrder()
     */
    void setSortOrder(Qt::SortOrder nSortOrder);

Q_SIGNALS:
    /*!
     * Notifier signal for the \link BaseFilterModel::inOperation inOperation \endlink property.
     * \sa inOperation()
     */
    void inOperationChanged(bool inOperation);
    /*!
     * Notifier signal for the \link BaseFilterModel::error error \endlink property.
     * \sa error()
     */
    void errorChanged(Error *error);
    /*!
     * This signal is emitted when loading the data into the model failed. It will contain
     * the pointer to an Error object providing further information about the occured error.
     * \sa Component::error
     */
    void failed(Error *error);
    /*!
     * Notifier signal for the \link BaseFilterModel::cachePeriod cachePeriod \endlink property.
     * \sa setCachePeriod() cachePeriod()
     */
    void cachePeriodChanged(quint32 cachePeriod);
    /*!
     * Notifier signal for the \link BaseFilterModel::userAgent userAgent \endlink property.
     * \sa setUserAgent() userAgent()
     */
    void userAgentChanged(const QString &userAgent);

    /*!
     * Notifier signal for the \link BaseFilterModel::search search \endlink property.
     * \sa setSearch() search()
     */
    void searchChanged(const QString &search);

    /*!
     * Notifier signal for the \link BaseFilterModel::sortOrder sortOrder \endlink property.
     * \sa setSortOrder() QSortFilterProxyModel::sortOrder()
     */
    void sortOrderChanged(Qt::SortOrder sortOrder);

protected:
    const QScopedPointer<BaseFilterModelPrivate> d_ptr;
    BaseFilterModel(BaseFilterModelPrivate &dd, QObject *parent = nullptr);
};

}

#endif // LIBINTFUORITBASEFILTERMODEL_H
