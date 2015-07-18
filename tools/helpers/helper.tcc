#include <typeinfo>
#include "helper.hpp"

namespace game{
    
    template<class T>
    T* Helper::Get(){ 
        for( auto it = helpers_.begin(); it != helpers_.end(); it++ ){
            
            if( it->first == typeid(T) ){
                T* helper = static_cast<T*>(it->second);
                return helper;
            }
        }

        // If no matching helper exists, create one
        
        T* helper = new T();
        auto pair = std::pair<std::type_index, ConcreteHelper*>(typeid(T), helper);
        helpers_.insert(pair);
        return helper;
    }

    std::multimap<std::type_index, ConcreteHelper*> Helper::helpers_;
}
