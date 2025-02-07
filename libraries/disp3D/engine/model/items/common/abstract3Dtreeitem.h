//=============================================================================================================
/**
* @file     abstract3Dtreeitem.h
* @author   Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2015
*
* @section  LICENSE
*
* Copyright (C) 2015, Lorenz Esch and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief     Abstract3DTreeItem class declaration.
*
*/

#ifndef DISP3DLIB_ABSTRACT3DTREEITEM_H
#define DISP3DLIB_ABSTRACT3DTREEITEM_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../../../../disp3D_global.h"
#include "../../3dhelpers/renderable3Dentity.h"
#include "types.h"


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QStandardItem>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE DISP3DLIB
//=============================================================================================================

namespace DISP3DLIB
{


//*************************************************************************************************************
//=============================================================================================================
// DISP3DLIB FORWARD DECLARATIONS
//=============================================================================================================

class MetaTreeItem;


//=============================================================================================================
/**
* Abstract3DTreeItem provides Abstract3DTreeItem provides the basic tree item. This item should be used as a base class for all tree items throughout the disp3D library.
*
* @brief Provides the basic tree item.
*/
class DISP3DSHARED_EXPORT Abstract3DTreeItem : public Renderable3DEntity, public QStandardItem
{
    Q_OBJECT

public :
    //=========================================================================================================
    /**
    * Default constructor.
    *
    * @param[in] p3DEntityParent    The parent 3D entity.
    * @param[in] iType      The type of the item. See types.h for declaration and definition.
    * @param[in] text       The text of this item. This is also by default the displayed name of the item in a view.
    */
    Abstract3DTreeItem(QEntity* p3DEntityParent = 0,
                       int iType = Data3DTreeModelItemTypes::UnknownItem,
                       const QString& text = "");

    //=========================================================================================================
    /**
    * QStandardItem functions
    */
    void setData(const QVariant& value, int role = Qt::UserRole + 1);
    int type() const;

    //=========================================================================================================
    /**
    * Returns all children of this item based on their type.
    *
    * @param[in] type    The type of the child items which should be looked for.
    *
    * @return           List with all found items.
    */
    QList<QStandardItem*> findChildren(int type);

    //=========================================================================================================
    /**
    * Returns all children of this item based on their text.
    *
    * @param[in] text    The text of the child items which should be looked for.
    *
    * @return           List with all found items.
    */
    QList<QStandardItem*> findChildren(const QString& text);

    //=========================================================================================================
    /**
    * Overloaded stream operator to add a child to this item based on a pointer.
    *
    * @param[in] newItem    The new item as a pointer.
    */
    Abstract3DTreeItem &operator<<(Abstract3DTreeItem* newItem);

    //=========================================================================================================
    /**
    * Overloaded stream operator to add a child to this item based on a reference.
    *
    * @param[in] newItem    The new item as a reference.
    */
    Abstract3DTreeItem &operator<<(Abstract3DTreeItem& newItem);

    //=========================================================================================================
    /**
    * Creates colors for given color for a number of input vertices.
    *
    * @param[in] numVert        The number of vertices.
    * @param[in] color          The vertex color information.
    *
    * @return The colors per vertex
    */
    static Eigen::MatrixX4f createVertColor(int numVert, const QColor& color = QColor(0,49,69));

    //=========================================================================================================
    /**
    * Set the alpha value.
    *
    * @param[in] fAlpha    The new alpha value.
    */
    void setAlpha(float fAlpha);

protected:
    //=========================================================================================================
    /**
    * Init this item.
    */
    virtual void initItem();

    //=========================================================================================================
    /**
    * Call this function whenever the check box of this item was checked.
    *
    * @param[in] checkState        The current checkstate.
    */
    virtual void onCheckStateChanged(const Qt::CheckState& checkState);

    //=========================================================================================================
    /**
    * Call this function whenever the the translation x of this item changed.
    *
    * @param[in] fTransX        The current x translation.
    */
    virtual void onTranslationXChanged(const QVariant& fTransX);

    //=========================================================================================================
    /**
    * Call this function whenever the the translation y of this item changed.
    *
    * @param[in] fTransY        The current y translation.
    */
    virtual void onTranslationYChanged(const QVariant& fTransY);

    //=========================================================================================================
    /**
    * Call this function whenever the the translation z of this item changed.
    *
    * @param[in] fTransZ        The current z translation.
    */
    virtual void onTranslationZChanged(const QVariant& fTransZ);

    //=========================================================================================================
    /**
    * Call this function whenever the the scaling of this item changed.
    *
    * @param[in] fScale        The current scale value for all axis.
    */
    virtual void onScaleChanged(const QVariant& fScale);

    //=========================================================================================================
    /**
    * Call this function whenever the color was changed.
    *
    * @param[in] color        The new surface color.
    */
    virtual void onColorChanged(const QVariant& color);

    //=========================================================================================================
    /**
    * Call this function whenever the alpha value changed.
    *
    * @param[in] fAlpha     The new alpha value.
    */
    virtual void onAlphaChanged(const QVariant& fAlpha);

    int     m_iType;        /**< This item's type. */

    QPointer<MetaTreeItem>      m_pItemTransformationOptions;       /**< The item holding the transfomation (translation, etc.) group. */
    QPointer<MetaTreeItem>      m_pItemAppearanceOptions;           /**< The item holding the appearance (color, alpha, etc.) group. */

signals:
    //=========================================================================================================
    /**
    * Emit this signal whenever this item's check state changed.
    *
    * @param[in] checkState     The current check state.
    */
    void checkStateChanged(const Qt::CheckState& checkState);
};

} //NAMESPACE DISP3DLIB

#endif // DISP3DLIB_ABSTRACT3DTREEITEM_H
