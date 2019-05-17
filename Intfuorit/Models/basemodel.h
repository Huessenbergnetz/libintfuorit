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

#ifndef LIBINTFUORITBASEMODEL_H
#define LIBINTFUORITBASEMODEL_H

#include "../intfuorit_global.h"
#include "../error.h"
#include <QAbstractItemModel>


namespace Intfuorit {

/*!
 * \defgroup models Data Models
 * \brief Classes in this module are used to present requested data in data models.
 */

class BaseModelPrivate;

/*!
 * \ingroup models
 * The %BaseModel class is the base class of all %Intfuorit data models.
 *
 * Do not use this class directly, use one of the derived classes.
 *
 * BaseModel and its subclasses in libintfuorit use a
 * <a href="https://techbase.kde.org/Policies/Library_Code_Policy/Shared_D-Pointer_Example">shared D-pointer</a>.
 *
 * \headerfile "" <Intfuorit/Models/basemodel.h>
 */
class INTFUORITSHARED_EXPORT BaseModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_DISABLE_COPY(BaseModel)
    Q_DECLARE_PRIVATE(BaseModel)
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
    Q_PROPERTY(Intfuorit::Error error READ error NOTIFY errorChanged)
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
public:
    /*!
     * Constructs a new %BaseModel with the given \a parent.
     */
    explicit BaseModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the %BaseModel.
     */
    ~BaseModel();

    /*!
     * Getter function for the \link BaseModel::inOperation inOperation \endlink property.
     * \sa inOperationChanged()
     */
    bool inOperation() const;

    /*!
     * Getter function fro the \link BaseModel::error error \endlink property.
     * \sa errorChanged() const;
     */
    Error error() const;

    /*!
     * Getter function for the \link BaseModel::cachePeriod cachePeriod \endlink property.
     * \sa setCachePeriod() cachePeriodChanged()
     */
    quint32 cachePeriod() const;

    /*!
     * Getter function for the \link BaseModel::userAgent userAgent \endlink property.
     * \sa setUserAgent() userAgentChanged()
     */
    QString userAgent() const;

    /*!
     * Setter function for the \link BaseModel::cachePeriod cachePeriod \endlink property.
     * \sa cachePeriod() cachePeriodChanged()
     */
    void setCachePeriod(quint32 nCachePeriod);

    /*!
     * Setter function for the \link BaseModel::userAgent userAgent \endlink property.
     * \sa userAgent() userAgentChanged()
     */
    void setUserAgent(const QString &nUserAgent);

public Q_SLOTS:
    /*!
     * Clears the model data. The default implementation does nothing.
     */
    virtual void clear();

Q_SIGNALS:
    /*!
     * Notifier signal for the \link BaseModel::inOperation inOperation \endlink property.
     * \sa inOperation()
     */
    void inOperationChanged(bool inOperation);
    /*!
     * Notifier signal for the \link BaseModel::error error \endlink property.
     * \sa error()
     */
    void errorChanged(const Intfuorit::Error &error);
    /*!
     * This signal is emitted when loading the data into the model failed. It will contain
     * the pointer to an Error object providing further information about the occured error.
     * \sa Component::error
     */
    void failed(const Intfuorit::Error &error);
    /*!
     * Notifier signal for the \link BaseModel::cachePeriod cachePeriod \endlink property.
     * \sa setCachePeriod() cachePeriod()
     */
    void cachePeriodChanged(quint32 cachePeriod);
    /*!
     * Notifier signal for the \link BaseModel::userAgent userAgent \endlink property.
     * \sa setUserAgent() userAgent()
     */
    void userAgentChanged(const QString &userAgent);

protected:
    const QScopedPointer<BaseModelPrivate> d_ptr;
    BaseModel(BaseModelPrivate &dd, QObject *parent = nullptr);
};

}

#endif // LIBINTFUORITBASEMODEL_H
