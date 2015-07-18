#include <iostream>
#include <map>
#include "game_object.hpp"

namespace game{

    template<class T>
    T* GameObject::GetComponent(){
        std::multimap<std::type_index, Component*>::iterator it;
        for( it = this->components.begin();
             it != this->components.end();
             it ++ ){
            
            if( it->first == typeid(T) ){
                T* component = static_cast<T*>(it->second);
                return component;
            }
        }
        return NULL;
    }

    template<class T>
    std::vector<T*> GameObject::GetAllComponents(){

        std::vector<T*> selected_components;
        std::multimap<std::type_index, Component*>::iterator it;

        for(it = this->components.begin(); it != this->components.end(); it++){
            if( it->first == typeid(T) ){
                selected_components.push_back( static_cast<T*>(it->second) );
            }
        }

        return selected_components;
    }

}
