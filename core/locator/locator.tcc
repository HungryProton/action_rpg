#include "locator.hpp"
#include "tools/logger.hpp"

namespace game{

    template <class T>
    T* Locator::Get(){
        for( auto it = services_.begin();
             it != services_.end();
             it ++ ){
            
            if( it->first == typeid(T) ){
                T* service = static_cast<T*>(it->second);
                return service;
            }
        }
        log(ERROR) << "Could not find service " << typeid(T).name() << std::endl;
        return nullptr; 
    }
}
