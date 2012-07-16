/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _TGUI_SPRITE_SHEET_INCLUDED_
#define _TGUI_SPRITE_SHEET_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API SpriteSheet : public Picture
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpriteSheet();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpriteSheet(const SpriteSheet& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpriteSheet& operator= (const SpriteSheet& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the picture cell, so the piece that is shown.
        ///
        /// This function will undo all scaling, as it just calculates the correct scale factors for you.
        ///
        /// \param width   The new width of the picture cell.
        /// \param height  The new height of the picture cell.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of a picture cell, so the piece that is shown, unaffected by scaling.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2u getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of a picture cell, so the piece that is shown, after the scaling transformation.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getScaledSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Change the number of rows and columns in the image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCells(unsigned int rows, unsigned int columns);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Change the number of rows in the image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setRows(unsigned int rows);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the number of rows in the image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getRows();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Change the number of columns in the image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setColumns(unsigned int columns);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the number of columns in the image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getColumns();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Choose which cell should be displayed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVisibleCell(unsigned int row, unsigned int column);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns which cell is being displayed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2u getVisibleCell();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        unsigned int m_Rows;
        unsigned int m_Columns;

        sf::Vector2u m_VisibleCell;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_SPRITE_SHEET_INCLUDED_

