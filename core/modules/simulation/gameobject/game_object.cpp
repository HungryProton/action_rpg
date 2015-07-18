#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <cstdlib>
#include <algorithm>

#include "game_object.hpp"
#include "core/modules/simulation/components/components_list.hpp"
#include "core/modules/simulation/components/component.hpp"
#include "core/modules/simulation/systems/system.hpp"
#include "core/messaging/message.hpp"

namespace game{

    GameObject::GameObject(){
        this->components.clear();
    }

    GameObject::~GameObject(){

        // Upon destruction, we iterate over each component and systems stored in the
        // GameObject


            /* We have to save the uid of the component that will be remove
             * and increment the iterator BEFORE actually removing the component
             * or else, the iterator is no longer valid and cause much
             * trouble (Segmentation fault)
             */

        std::multimap<std::type_index, Component*>::iterator it = this->components.begin();

        while(it!=this->components.end() ){
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
        this->components.clear();
        this->systems.clear();

    }

    void GameObject::AttachComponent(Component* c){
        if(!c->is_attached){
            this->components.insert(std::pair<std::type_index, Component*>(typeid(*c), c));
            c->is_attached = true;
            Message update;
            update.subject = UPDATE;
            this->HandleMessage(update);
        }else{
            std::cout << "Error, component " << typeid(*c).name() << " is already attached" << std::endl;
        }
    }

    void GameObject::AttachSystem(System* s){
        if(!s->IsAttached()){
            this->systems.push_back(s);
            s->Attach();
//            Message update;
//            update.subject = UPDATE;
//            this->RelayMessage(update);
        }else{
            std::cout << "Error : System already attached to a gameObject" << std::endl;
        }
    }

    void GameObject::HandleMessage(Message message){

        std::vector<System*>::iterator it;
        for(it = this->systems.begin(); it != this->systems.end(); it++){
            (*it)->HandleMessage(message);
        }

        if(message.children_recursive){
            for(unsigned int i=0; i < this->children.size(); i++){
                this->children[i]->HandleMessage(message);
            }
        }
    }
}
