#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <cstdlib>
#include <algorithm>

#include "game_object.hpp"
#include "core/component/component.hpp"
#include "tools/logger.hpp"

namespace game{

	GameObject::GameObject(){
		this->components_.clear();
		this->channel_id_ = 0;
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
			c->parent = this;
			this->NotifyAttachedComponents();
		}else{
			LOG(ERROR) << "Error, component " << typeid(*c).name() << " is already attached" << std::endl;
		}
	}

	Component* GameObject::DetachComponent(Component* c){
		if(!c->is_attached){ return nullptr; }

		for(auto it = this->components_.begin();
				it != this->components_.end();
				it++){
			if(c != it->second){ continue; }

			Component* component = it->second;
			this->components_.erase(it);
			return component;
		}
		return nullptr;
	}

	void GameObject::DetachAndDestroyComponent(Component* c){
		Component* component = this->DetachComponent(c);
		if(component){
			delete component;
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
		for(auto c : this->components_){
			if(c.second->manual_update){continue;}
			if(!c.second->enabled){continue;}
			c.second->Update();
		}
	}

	void GameObject::NotifyAttachedComponents(){
		for(auto c : this->components_){
			c.second->NotifyNewComponentAdded();
		}
	}

	GameObject* GameObject::Clone(){
		GameObject* new_game_object = new GameObject();

		for(auto it = this->components_.begin();
				it != this->components_.end();
				it++){
			Component* cloned_component = it->second->Clone();
			new_game_object->AttachComponent(cloned_component);
		}
		return new_game_object;
	}
}
