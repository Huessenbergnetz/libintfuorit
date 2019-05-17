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

#ifndef LIBINTFUORITBREACHESLISTMODEL_H
#define LIBINTFUORITBREACHESLISTMODEL_H

#include "breachesmodel.h"

namespace Intfuorit {

class BreachesListModelPrivate;

/*!
 * \ingroup models
 * The %BreachesListModel class provides a single column list model containing Breach objects
 * requested from the HIBP API. This model is designed to be usable in QML list views, the
 * different data fields are accessible via the \link BreachesListModel::Roles model data roles \endlink.
 *
 * Use BreachesModel::getAllBreaches() to request the list of breaches from the HIBP API. See BreachesListFilterModel
 * for a model that can filter the API result locally.
 *
 * \headerfile "" <Intfuorit/Models/BreachesListModel>
 * \sa Breach, BreachesListFilterModel, GetAllBreaches, GetBreachesForAccount
 */
class INTFUORITSHARED_EXPORT BreachesListModel : public BreachesModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BreachesListModel)
    Q_DISABLE_COPY(BreachesListModel)
public:
    /*!
     * Constructs a new %BreachesListModel with the given \a parent.
     */
    explicit BreachesListModel(QObject *parent = nullptr);

    /*!
     * Deconstructs the %BreachesListModel.
     */
    ~BreachesListModel();

    /*!
     * The model data roles. From QML, use the enum name starting lower case to access
     * the model data. The role names correspond to the property names of the Breach class.
     */
    enum Roles : quint16 {
        Title = Qt::UserRole + 1,   /**< The display \link Breach::title title \endlink of the breach. */
        Name,                       /**< The unique \link Breach::name name \endlink of the breach. */
        Domain,                     /**< The \link Breach::domain domain \endlink of the breached site. */
        BreachDate,                 /**< The \link Breach::breachDate date \endlink the breach has happened. */
        AddedDate,                  /**< \link Breach::addedDate Date and time \endlink the breach data has been added to HIBP. */
        ModifiedDate,               /**< \link Breach::modifiedDate Date and time \endlink the breach data has last been modified on HIBP. */
        PwnCount,                   /**< The number of \link Breach::pwnCount pwned accounts \endlink. */
        Description,                /**< \link Breach::description Description \endlink of the breach. */
        DataClasses,                /**< List of \link Breach::dataClasses classes of data \endlink that were affected by the breach. */
        DataClassesTranslated,      /**< Translated list of \link Breach::dataClasses classes of data \endlink that were affected by the breach. */
        DataClassesTranslatedString,/**< A locally joined string of \link Breach::dataClasses classes of data \endlink that were affected by the breach. */
        IsVerified,                 /**< Indicates that the breach is considered \link Breach::isVerified unverified \endlink. */
        IsFabricated,               /**< Indicates that the breach is considered \link Breach::isFabricated fabricated \endlink. */
        IsSensitive,                /**< Indicates if the breach is considered \link Breach::isSensitive sensitive \endlink. */
        IsActive,                   /**< ??? */
        IsRetired,                  /**< Indicates if the breach has been \link Breach::isRetired retired \endlink. */
        IsSpamList,                 /**< Indicates if the breach is considered a \link Breach::isSpamList spam list \endlink. */
        LogoPath,                   /**< \link Breach::logoPath HTTP URL \endlink to the breached site's logo. */
    };
    Q_ENUM(Roles)

    /*!
     * Returns the model's \link BreachesListModel::Roles role names \endlink.
     */
    QHash<int, QByteArray> roleNames() const override;
    /*!
     * Returns the number of Breach objects in this model.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /*!
     * Returns the index of the item in the model specified by the given \a row, \a column and \a parent index.
     */
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    /*!
     * Returns the data stored under the given \a role for the Breach referred to by the \a index.
     * \sa BreachesListModel::Roles
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
    BreachesListModel(BreachesListModelPrivate &dd, QObject *parent = nullptr);
};

}

#endif // LIBINTFUORITBREACHESLISTMODEL_H
