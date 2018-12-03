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

#ifndef LIBINTFUORITPASTESLISTMODEL_H
#define LIBINTFUORITPASTESLISTMODEL_H

#include <QObject>
#include "pastesmodel.h"
#include "../intfuorit_global.h"

namespace Intfuorit {

class PastesListModelPrivate;

/*!
 * \ingroup models
 * The %PastesListModel class provides a single column list model containing Paste objects
 * requested from the HIBP API. This model is designed to be usable in QML list view, the
 * different data fields are accessible via the \link PastesListModel::Roles model data roles \endlink.
 *
 * Use PastesModel::getPastesForAccount() to request the list of pates from the HIBP API and
 * to populate the model.
 *
 * \headerfile "" <Intfuorit/Models/PastesListModel>
 * \sa Paste, PastesListFilterModel, GetPastesForAccount
 */
class INTFUORITSHARED_EXPORT PastesListModel : public PastesModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(PastesListModel)
    Q_DISABLE_COPY(PastesListModel)
public:
    /*!
     * Constructs a new %PastesListModel with the given \a parent.
     */
    explicit PastesListModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the %PastesListModel.
     */
    ~PastesListModel();

    /*!
     * The model data roles. From QML, use the enum name starting lower case to access the
     * model data. The role names correspond to the property names of the Paste class.
     */
    enum Roles : quint16 {
        Item = Qt::UserRole + 1,    /**< Pointer to the complete Paste object. */
        Source,                     /**< The \link Paste::source source \endlink service the paste is published on. */
        SourceId,                   /**< The \link Paste::sourceId ID \endlink of the paste as it was given at the source service. */
        Title,                      /**< The \link Paste::title title \endlink of the paste, if any. Might be a null string. */
        Date,                       /**< The \link Paste::date date \endlink and time that the paste was posted. */
        EmailCount,                 /**< The \link Paste::emailCount number of emails \endlink that were found when processing the paste. */
        Url                         /**< The \link Paste::url url \endlink the paste is available on, composed of SourceId and the Source service. */
    };

    /*!
     * Returns the model's \link PastesListModel::Roles role names \endlink.
     */
    QHash<int, QByteArray> roleNames() const override;
    /*!
     * Returns the number of Paste objects in this model.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /*!
     * Returns the index of the item in the model specified by the given \a row, \a column and \a parent index.
     */
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    /*!
     * Returns the data stored under the given \a role for the Paste referred to by the \a index.
     * \sa PastesListModel::Roles
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    /*!
     * Always returns an invalid QModelIndex for this type of model.
     */
    QModelIndex parent(const QModelIndex &child) const override;
    /*!
     * Always returns \c 1 for this type of model.
     */
    int columnCount(const QModelIndex &parent) const override;

protected:
    PastesListModel(PastesListModelPrivate &dd, QObject *parent = nullptr);
};

}

#endif // LIBINTFUORITPASTESLISTMODEL_H
