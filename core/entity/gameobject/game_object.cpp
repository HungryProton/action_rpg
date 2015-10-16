#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <cstdlib>
#include <algorithm>

#include "game_object.hpp"
#include "core/entity/component/component.hpp"
#include "core/entity/system/system.hpp"

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

        std::vector<System*>::iterator it2 = this->systems.begin();

        while(it2!=this->systems.end() ){
            System* s = *it2;
            it2++;
            delete s;
        }

        // Once everything have been removed, we clear the maps, just to be sure
        this->components_.clear();
        this->systems.clear();

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

		std::vector<Component*> GameObject::GetAllComponents(){
			std::vector<Component*> components;

			for(auto it = this->components_.begin();
					it != this->components_.end();
					it++){
				components.push_back(it->second);
			}
			return components;
		}

    void GameObject::RelayMessage(Message message){

        if(message.children_recursive){
            for(unsigned int i=0; i < this->children_.size(); i++){
                this->children_[i]->RelayMessage(message);
            }
        }
    }
}
