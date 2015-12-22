#ifndef GAME_CORE_GAMEOBJECT_HPP
#define GAME_CORE_GAMEOBJECT_HPP

#include <vector>
#include <map>
#include <string>
#include <typeindex>
#include "core/messaging/message.hpp"
namespace game{

	class Game;
	class System;
	struct Component;

	class GameObject{

		public:

			/** \brief The base class of the game.
			 *
			 *	Every single game entity is a GameObject. No class should
			 *	inherit from this class. To create any Game Entity, create a
			 *	GameObject and attach different components on it to produce the
			 *	desired behavior.
			 */
			GameObject();


			/**
			 * The destructor detach properly every component attached to the
			 *	game object and destroys the object.
			 */
			~GameObject();


			/** \brief Add a new component
			 *
			 *	\param type : The ID of the component to attach
			 *
			 *	Add a new component for the current
			 *	GameObject and update the components entries in the
			 *	game ComponentManager.
			 */
			void AttachComponent(Component* c);

			void DetachComponent(Component* c);

			void AttachSystem(System* c);

			void DetachSystem(System* c);


			void Update();


			/** \brief Notify every systems attached to the gameobject
			 *	that a new component has been attached and their current
			 *	target list might no longer be valid
			 */
			void NotifyAttachedSystems();


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
			 *		the components that matched the type you asked for
			 */
			template<class T>
			std::vector<T*> GetAllMatchingComponents();


			std::vector<Component*> GetAllComponents();

			GameObject* Clone();

		private:

			/** \brief Stores pointers to the components attached
			 *	to the current GameObject
			 */
			std::multimap<std::type_index, Component*> components_;

			std::vector<System*> systems_;


			/** \brief Pointers to the GameObject's
			 *	direct children
			 */
			std::vector<GameObject*> children_;
	};
}

#include "game_object.tcc"
#endif // GAME_CORE_GAMEOBJECT_HPP
