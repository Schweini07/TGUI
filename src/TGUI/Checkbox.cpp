/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Objects.hpp>
#include <TGUI/ClickableObject.hpp>
#include <TGUI/Checkbox.hpp>

#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Checkbox::Checkbox() :
    m_Checked          (false),
    m_AllowTextClick   (true),
    m_TextSize         (0)
    {
        m_Callback.objectType = Type_Checkbox;
        m_Text.setColor(sf::Color::Black);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Checkbox::Checkbox(const Checkbox& copy) :
    ClickableObject (copy),
    m_Checked       (copy.m_Checked),
    m_AllowTextClick(copy.m_AllowTextClick),
    m_Text          (copy.m_Text),
    m_TextSize      (copy.m_TextSize)
    {
        // Copy the textures
        TGUI_TextureManager.copyTexture(copy.m_TextureUnchecked, m_TextureUnchecked);
        TGUI_TextureManager.copyTexture(copy.m_TextureChecked, m_TextureChecked);
        TGUI_TextureManager.copyTexture(copy.m_TextureHover, m_TextureHover);
        TGUI_TextureManager.copyTexture(copy.m_TextureFocused, m_TextureFocused);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Checkbox::~Checkbox()
    {
        if (m_TextureUnchecked.data != NULL)  TGUI_TextureManager.removeTexture(m_TextureUnchecked);
        if (m_TextureChecked.data != NULL)    TGUI_TextureManager.removeTexture(m_TextureChecked);
        if (m_TextureHover.data != NULL)      TGUI_TextureManager.removeTexture(m_TextureHover);
        if (m_TextureFocused.data != NULL)    TGUI_TextureManager.removeTexture(m_TextureFocused);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Checkbox& Checkbox::operator= (const Checkbox& right)
    {
        if (this != &right)
        {
            Checkbox temp(right);
            this->ClickableObject::operator=(right);

            std::swap(m_Checked,          temp.m_Checked);
            std::swap(m_AllowTextClick,   temp.m_AllowTextClick);
            std::swap(m_Text,             temp.m_Text);
            std::swap(m_TextSize,         temp.m_TextSize);
            std::swap(m_TextureUnchecked, temp.m_TextureUnchecked);
            std::swap(m_TextureChecked,   temp.m_TextureChecked);
            std::swap(m_TextureHover,     temp.m_TextureHover);
            std::swap(m_TextureFocused,   temp.m_TextureFocused);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Checkbox* Checkbox::clone()
    {
        return new Checkbox(*this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Checkbox::load(const std::string& configFileFilename)
    {
        // When everything is loaded successfully, this will become true.
        m_Loaded = false;

         // If the checkbox was loaded before then remove the old textures
        if (m_TextureUnchecked.data != NULL) TGUI_TextureManager.removeTexture(m_TextureUnchecked);
        if (m_TextureChecked.data != NULL)   TGUI_TextureManager.removeTexture(m_TextureChecked);
        if (m_TextureHover.data != NULL)     TGUI_TextureManager.removeTexture(m_TextureHover);
        if (m_TextureFocused.data != NULL)   TGUI_TextureManager.removeTexture(m_TextureFocused);

        // Open the config file
        ConfigFile configFile;
        if (!configFile.open(configFileFilename))
        {
            TGUI_OUTPUT("TGUI error: Failed to open " + configFileFilename + ".");
            return false;
        }

        // Read the properties and their values (as strings)
        std::vector<std::string> properties;
        std::vector<std::string> values;
        if (!configFile.read("Checkbox", properties, values))
        {
            TGUI_OUTPUT("TGUI error: Failed to parse " + configFileFilename + ".");
            return false;
        }

        // Close the config file
        configFile.close();

        // Find the folder that contains the config file
        std::string configFileFolder = "";
        std::string::size_type slashPos = configFileFilename.find_last_of("/\\");
        if (slashPos != std::string::npos)
            configFileFolder = configFileFilename.substr(0, slashPos+1);

        // Handle the read properties
        for (unsigned int i = 0; i < properties.size(); ++i)
        {
            std::string property = properties[i];
            std::string value = values[i];

            if (property == "textcolor")
            {
                m_Text.setColor(configFile.readColor(value));
            }
            else if (property == "checkedimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_TextureChecked))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for CheckedImage in section Checkbox in " + configFileFilename + ".");
                    return false;
                }
            }
            else if (property == "uncheckedimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_TextureUnchecked))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for UncheckedImage in section Checkbox in " + configFileFilename + ".");
                    return false;
                }
            }
            else if (property == "hoverimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_TextureHover))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for HoverImage in section Checkbox in " + configFileFilename + ".");
                    return false;
                }
            }
            else if (property == "focusedimage")
            {
                if (!configFile.readTexture(value, configFileFolder, m_TextureFocused))
                {
                    TGUI_OUTPUT("TGUI error: Failed to parse value for FocusedImage in section Checkbox in " + configFileFilename + ".");
                    return false;
                }
            }
            else
                TGUI_OUTPUT("TGUI warning: Unrecognized property '" + property + "' in section Checkbox in " + configFileFilename + ".");
        }

        // Make sure the required texture was loaded
        if ((m_TextureChecked.data != NULL) && (m_TextureUnchecked.data != NULL))
        {
            m_Size = Vector2f(m_TextureChecked.getSize());
        }
        else
        {
            TGUI_OUTPUT("TGUI error: Not all needed images were loaded for the checkbox. Is the Checkbox section in " + configFileFilename + " complete?");
            return false;
        }

        // Check if optional textures were loaded
        if (m_TextureFocused.data != NULL)
        {
            m_AllowFocus = true;
            m_ObjectPhase |= ObjectPhase_Focused;
        }
        if (m_TextureHover.data != NULL)
        {
            m_ObjectPhase |= ObjectPhase_Hover;
        }

        // When there is no error we will return true
        return m_Loaded = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::setSize(float width, float height)
    {
        // Don't do anything when the checkbox wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // A negative size is not allowed for this object
        if (width  < 0) width  = -width;
        if (height < 0) height = -height;

        // Set the size of the checkbox
        m_Size.x = width;
        m_Size.y = height;

        // If the text is auto sized then recalculate the size
        if (m_TextSize == 0)
            setText(m_Text.getString());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::check()
    {
        if (m_Checked == false)
        {
            // Add the callback (if the user requested it)
            if (m_CallbackFunctions[Checked].empty() == false)
            {
                m_Callback.trigger = Checked;
                m_Callback.checked = true;
                addCallback();
            }
        }

        m_Checked = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::uncheck()
    {
        if (m_Checked)
        {
            // Add the callback (if the user requested it)
            if (m_CallbackFunctions[Unchecked].empty() == false)
            {
                m_Callback.trigger = Unchecked;
                m_Callback.checked = false;
                addCallback();
            }
        }

        m_Checked = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Checkbox::isChecked() const
    {
        return m_Checked;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::setText(const sf::String& text)
    {
        // Don't do anything when the checkbox wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Set the new text
        m_Text.setString(text);

        // Check if the text is auto sized
        if (m_TextSize == 0)
        {
            // Set the text size
            m_Text.setCharacterSize(static_cast<unsigned int>(m_Size.y));
            m_Text.setCharacterSize(static_cast<unsigned int>(m_Text.getCharacterSize() - m_Text.getLocalBounds().top));
        }
        else // When the text has a fixed size
        {
            // Set the text size
            m_Text.setCharacterSize(m_TextSize);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String Checkbox::getText() const
    {
        return m_Text.getString();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::setTextFont(const sf::Font& font)
    {
        m_Text.setFont(font);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Font* Checkbox::getTextFont() const
    {
        return m_Text.getFont();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::setTextColor(const sf::Color& Color)
    {
        m_Text.setColor(Color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& Checkbox::getTextColor() const
    {
        return m_Text.getColor();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::setTextSize(unsigned int size)
    {
        // Change the text size
        m_TextSize = size;

        // Call setText to reposition the text
        setText(m_Text.getString());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int Checkbox::getTextSize() const
    {
        return m_Text.getCharacterSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::allowTextClick(bool acceptTextClick)
    {
        m_AllowTextClick = acceptTextClick;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Checkbox::mouseOnObject(float x, float y)
    {
        // Don't do anything when the checkbox wasn't loaded correctly
        if (m_Loaded == false)
            return false;

        // Check if the mouse is on top of the image
        if (getTransform().transformRect(sf::FloatRect(0, 0, m_Size.x, m_Size.y)).contains(x, y))
            return true;
        else
        {
            // Check if the mouse is on top of the text
            if (m_AllowTextClick)
            {
                sf::FloatRect bounds = m_Text.getLocalBounds();
                if (sf::FloatRect(bounds.left, bounds.top, bounds.width * getScale().x, bounds.height * getScale().y).contains(x - (getPosition().x + ((m_Size.x * 11.0f / 10.0f) * getScale().x)), y - getPosition().y - ((m_Size.y - bounds.height) / 2.0f) + bounds.top))
                    return true;
            }
        }

        if (m_MouseHover == true)
            mouseLeftObject();

        // The mouse is not on top of the checkbox
        m_MouseHover = false;
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::leftMouseReleased(float x, float y)
    {
        // Add the callback (if the user requested it)
        if (m_CallbackFunctions[LeftMouseReleased].empty() == false)
        {
            m_Callback.trigger = LeftMouseReleased;
            m_Callback.checked = m_Checked;
            m_Callback.mouse.x = x - getPosition().x;
            m_Callback.mouse.y = y - getPosition().y;
            addCallback();
        }

        // Check if we clicked on the checkbox (not just mouse release)
        if (m_MouseDown == true)
        {
            // Check or uncheck the checkbox
            if (m_Checked)
                uncheck();
            else
                check();

            // Add the callback (if the user requested it)
            if (m_CallbackFunctions[LeftMouseClicked].empty() == false)
            {
                m_Callback.trigger = LeftMouseClicked;
                m_Callback.checked = m_Checked;
                m_Callback.mouse.x = x - getPosition().x;
                m_Callback.mouse.y = y - getPosition().y;
                addCallback();
            }

            m_MouseDown = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::keyPressed(sf::Keyboard::Key key)
    {
        // Check if the space key or the return key was pressed
        if (key == sf::Keyboard::Space)
        {
            // Check or uncheck the checkbox
            if (m_Checked)
                uncheck();
            else
                check();

            // Add the callback (if the user requested it)
            if (m_CallbackFunctions[SpaceKeyPressed].empty() == false)
            {
                m_Callback.trigger = SpaceKeyPressed;
                m_Callback.checked = m_Checked;
                addCallback();
            }
        }
        else if (key == sf::Keyboard::Return)
        {
            // Check or uncheck the checkbox
            if (m_Checked)
                uncheck();
            else
                check();

            // Add the callback (if the user requested it)
            if (m_CallbackFunctions[ReturnKeyPressed].empty() == false)
            {
                m_Callback.trigger = ReturnKeyPressed;
                m_Callback.checked = m_Checked;
                addCallback();
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::objectFocused()
    {
        // We can't be focused when we don't have a focus image
        if ((m_ObjectPhase & ObjectPhase_Focused) == 0)
            m_Parent->unfocusObject(this);
        else
            Object::objectFocused();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::initialize(tgui::Group *const parent)
    {
        m_Parent = parent;
        m_Text.setFont(m_Parent->getGlobalFont());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Don't do draw when the checkbox wasn't loaded correctly
        if (m_Loaded == false)
            return;

        // Adjust the transformation
        states.transform *= getTransform();

        // Remember the current transformation
        sf::Transform oldTransform = states.transform;

        // Give the checkbox the correct size
        states.transform.scale(m_Size.x / m_TextureUnchecked.getSize().x, m_Size.y / m_TextureUnchecked.getSize().y);

        // Check if the checkbox was checked
        if (m_Checked)
        {
            // The checked image may be a little bigger than the unchecked one, so put it on the right position
            states.transform.translate(0, static_cast<float>(m_TextureUnchecked.getHeight()) - m_TextureChecked.getHeight());

            // Draw the image of the checked checkbox
            target.draw(m_TextureChecked, states);

            // Undo the translation
            states.transform.translate(0, static_cast<float>(m_TextureChecked.getHeight()) - m_TextureUnchecked.getHeight());
        }
        else // The checkbox was unchecked, just draw it
            target.draw(m_TextureUnchecked, states);

        // When the checkbox is focused then draw an extra image
        if ((m_Focused) && (m_ObjectPhase & ObjectPhase_Focused))
            target.draw(m_TextureFocused, states);

        // When the mouse is on top of the checkbox then draw an extra image
        if ((m_MouseHover) && (m_ObjectPhase & ObjectPhase_Hover))
            target.draw(m_TextureHover, states);


        // Restore the old transformation
        states.transform = oldTransform;

        // Get the bounds of the text
        sf::FloatRect textBounds = m_Text.getGlobalBounds();

        // Set the position of the text
        states.transform.translate(std::floor(m_Size.x * 11.0f / 10.0f - textBounds.left), std::floor(((m_Size.y - textBounds.height) / 2.0f) - textBounds.top));

        // Draw the text
        target.draw(m_Text, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
