#include "render.hpp"

namespace game{

    template<class T>
    void Render::RegisterHelper(){
        T* helper = new T();
        this->helpers_.insert( std::pair<std::type_index, Service*>(
                                               typeid(T), helper) );
    }
}
