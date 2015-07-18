#ifndef GAME_CORE_MODULE_SIMULATION_GAMEOBJECT_HPP
#define GAME_CORE_MODULE_SIMULATION_GAMEOBJECT_HPP

#include <vector>
#include <map>
#include <string>
#include <typeindex>

#define SELECT_ANY 0
#define SELECT_SPECIFIC 1

#define GROUP_GRAPHIC 1
#define GROUP_PHYSIC 2
#define GROUP_LOGIC 3

namespace game{

    class Game;
    class System;
    class Component;
    class Message;

    class GameObject{

        public:

            /** \brief The base class of the game.
             *
             *  Every single game entity is a GameObject. No class should 
             *  inherit from this class. To create any Game Entity, create a
             *  GameObject and attach different components on it to produce the
             *  desired behavior.
             */
            GameObject();


            /**
             * The destructor detach properly every component attached to the
             *  game object and destroys the object.
             */
            ~GameObject();


            /** \brief Add a new component
             *
             *  \param type : The ID of the component to attach
             *
             *  Add a new component for the current
             *  GameObject and update the components entries in the
             *  game ComponentManager.
             */
            void AttachComponent(Component* c);


            /** \brief Add a new System
             *
             *  \param type : type of the system to add
             */
            void AttachSystem(System* s);


            /** \brief Relay the message to all of the other systems
             *
             * \param Message : The message that will be relayed.
             */
            void HandleMessage(Message);


            /**
             * @brief Get the first matching component
             *
             * @return a pointer to the first matching component.
             */
            template< class T >
            T* GetComponent();


            /** \brief Get all the matching components
             * 
             *
             * \return std::vector<T*> : Vector containing all 
             *      the components that matched the type you asked for
             */
            template<class T>
            std::vector<T*> GetAllComponents();

        private:

            /** \brief Stores pointers to the components attached
             *  to the current GameObject
             */
            std::multimap<std::type_index, Component*> components;

            std::vector<System*> systems;

            /** \brief Pointers to the GameObject's
             *  direct children
             */
            std::vector<GameObject*> children;
    };
}

#include "game_object.tcc"
#endif // GAME_CORE_GAMEOBJECT_HPP
