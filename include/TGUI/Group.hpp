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


#ifndef _TGUI_GROUP_INCLUDED_
#define _TGUI_GROUP_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Parent struct for objects that store multiple objects.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct TGUI_API Group
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Group();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Group(const Group& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Group();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Group& operator= (const Group& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Creates and adds an object to the group.
        ///
        /// \param objectName  If you want to access the object later then you must do this with this name.
        ///
        /// Usage example:
        /// \code tgui::Picture* pic = group.add<tgui::Picture>("picName"); \endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        T* add(const std::string objectName = "")
        {
            T* newObject = new T();
            newObject->m_Parent = this;
            m_EventManager.addObject(newObject);

            newObject->initialize(globalFont);

            m_Objects.push_back(newObject);
            m_ObjName.push_back(objectName);

            return newObject;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to an earlier created object.
        ///
        /// \param objectName The name that was given to the object when it was added to the group.
        ///
        /// \warning Make sure that the name belongs to the object you are trying to get.
        ///         Behaviour is undefined when e.g. calling this function to get a picture but
        ///         when passing a name that was given to a button.
        ///
        /// \warning This function will return NULL when an unknown object name was passed.
        ///
        /// Usage example:
        /// \code tgui::Picture* pic = group.get<tgui::Picture>("picName"); \endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        T* get(const std::string objectName)
        {
            for (unsigned int i=0; i<m_ObjName.size(); ++i)
            {
                if (m_ObjName[i].compare(objectName) == 0)
                    return static_cast<T*>(m_Objects[i]);
            }

            return NULL;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Makes a copy of any existing object and returns the pointer to the new object.
        ///
        /// \param oldObject     A pointer to the old object.
        /// \param newObjectName If you want to access the object later then you must do this with this name.
        ///
        /// \see copy
        ///
        /// Usage example:
        /// \code tgui::Picture* pic = group.copyObject(pictureToCopy, "NameOfNewPic"); \endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        T* copyObject(T* oldObject, const std::string newObjectName = "")
        {
            T* newObject = new T(*oldObject);
            m_EventManager.addObject(newObject);

            m_Objects.push_back(newObject);
            m_ObjName.push_back(newObjectName);

            return newObject;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Makes a copy of any existing object and returns the pointer to the new object.
        ///
        /// \param oldObjectName The name that was given to the object when it was added to the group.
        /// \param newObjectName If you want to access the copied object later then you must do this with this name.
        ///
        /// \warning This function will return NULL when an unknown object name was passed.
        ///
        /// \see copyObject
        ///
        /// Usage example:
        /// \code tgui::Picture* pic = group.copy<tgui::Picture>("PicToCopy", "NameOfNewPic"); \endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        T* copy(const std::string oldObjectName, const std::string newObjectName = "")
        {
            for (unsigned int i=0; i<m_ObjName.size(); ++i)
            {
                if (m_ObjName[i].compare(oldObjectName) == 0)
                {
                    T* newObject = new T(*static_cast<T*>(m_Objects[i]));
                    m_EventManager.addObject(newObject);

                    m_Objects.push_back(newObject);
                    m_ObjName.push_back(newObjectName);

                    return newObject;
                }
            }

            return NULL;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of all the objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<OBJECT*>& getObjects();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of the names of all the objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<std::string>& getObjectNames();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single object that was added to the panel.
        ///
        /// If there are multiple objects with the same name then only the first matching object
        /// will be removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeObject(const std::string objectName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all objects that were added to the panel.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllObjects();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses an object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focus(OBJECT* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocuses an object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocus(OBJECT* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Uncheck all the radio buttons.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheckRadioButtons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds a callback to the list in tgui::Window.
        ///
        /// This callback can be obtained by calling the getCallback function of the window.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void addCallback(Callback& callback) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Update the internal clock to make animation possible.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTime(const sf::Time& elapsedTime);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places an object before all other objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveObjectToFront(OBJECT* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places an object behind all other objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveObjectToBack(OBJECT* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will call the draw function from all the objects in the correct order.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void drawObjectGroup(sf::RenderTarget* target, const sf::RenderStates& states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// The internal font, used by all objects by default. If not changed then this is the default SFML font.
        sf::Font globalFont;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        std::vector<OBJECT*>      m_Objects;
        std::vector<std::string>  m_ObjName;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // The internal event manager
        EventManager m_EventManager;

        // Is the group focused? If so, then one of the objects inside the group may be focused
        bool m_GroupFocused;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_GROUP_INCLUDED_
