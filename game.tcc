#include "game.hpp"
#include "core/locator/locator.hpp"

namespace game{

    // TODO : Refactor that thing, default argument didn't worked when I wrote
    // that. Those 2 methods got the same code, except for the final container
    template<class T>
    void Game::RequestForService(){

        T* service = Locator::Get<T>();
        if(service){
            // Service already loaded and available
            return;
        }

        // Create service otherwise
        service = new T();
        
        secondary_services_.push_back( service );
        Locator::Provide(service);
    }

    template<class T>
    void Game::RequestForCoreService(){

        T* service = Locator::Get<T>();
        if(service){
            // Service already loaded and available
            return;
        }

        // Create service otherwise
        service = new T();
        
        core_services_.push_back( service );
        Locator::Provide(service);
    }

    template<class T>
    void Game::DeleteServices( std::vector<T*>* services ){
        auto it = services->begin();

        while( it != services->end() ){
            Service* service = (*it);
            it++;
            Locator::Remove(service);
            delete service;
        }
    }
}
