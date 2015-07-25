#include "locator.hpp"

namespace game{

    void Locator::Provide(Service* service){
        services_.insert( std::pair<std::type_index, Service*>(
                                   typeid(*service), service) );
    }

    void Locator::Remove(Service* service){
        for( auto it = services_.begin();
                  it != services_.end() ;
                  it++){

            if( it->first == typeid(*service) ){
                services_.erase(it);
                return;
            }
        }
    }

    std::map<std::type_index, Service*> Locator::services_;
}
