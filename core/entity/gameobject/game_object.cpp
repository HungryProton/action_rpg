#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <cstdlib>
#include <algorithm>

#include "game_object.hpp"
#include "core/entity/component/component.hpp"
#include "core/entity/system/system.hpp"
#include "tools/logger.hpp"

namespace game{

	GameObject::GameObject(){
		this->components_.clear();
	}

	GameObject::~GameObject(){

		// Upon destruction, we iterate over each component and systems stored in the
		// GameObject


			/* We have to save the uid of the component that will be remove
			 * and increment the iterator BEFORE actually removing the component
			 * or else, the iterator is no longer valid and cause much
			 * trouble (Segmentation fault)
			 */

		std::multimap<std::type_index, Component*>::iterator it = this->components_.begin();

		while(it!=this->components_.end() ){
			Component* c = it->second;
			it++;
			delete c;
		}

		this->components_.clear();
	}

	void GameObject::AttachComponent(Component* c){
		if(!c->is_attached){
			this->components_.insert(std::pair<std::type_index, Component*>(typeid(*c), c));
			c->is_attached = true;
			Message update;
			update.subject = UPDATE;
			this->RelayMessage(update);
		}else{
			std::cout << "Error, component " << typeid(*c).name() << " is already attached" << std::endl;
		}
	}

	void GameObject::AttachSystem(System* s){
		if(!s->IsAttached()){
			this->systems_.push_back(s);
			s->Attach();
		} else {
			LOG(WARNING) << "System is already attached to a GameObject" << std::endl;
		}
	}

	std::vector<Component*> GameObject::GetAllComponents(){
		std::vector<Component*> components;

		for(auto it = this->components_.begin();
						 it != this->components_.end();
						 it++){
			components.push_back(it->second);
		}
		return components;
	}

	void GameObject::Update(){
		for(auto it = this->systems_.begin();
				it != this->systems_.end();
				it++){
			(*it)->Update();
		}
	}

	void GameObject::RelayMessage(Message message){

		for(auto it = this->systems_.begin();
				it != this->systems_.end();
				it++ ){
			(*it)->HandleMessage(message);
		}

		if(message.children_recursive){
			for(unsigned int i=0; i < this->children_.size(); i++){
				this->children_[i]->RelayMessage(message);
			}
		}
	}

	GameObject* GameObject::Clone(){

		GameObject* new_game_object = new GameObject();

		std::vector<Component*> components_to_clone;

		for(auto it = this->components_.begin();
				it != this->components_.end();
				it++){
			Component* cloned_component = it->second->Clone();
			new_game_object->AttachComponent(cloned_component);
		}

		return new_game_object;
	}
}
