#include "render.hpp"
#include "core/locator/locator.hpp"

namespace game{

    template<class T>
    void Render::RegisterHelper(){
        T* helper = new T();
        this->helpers_.push_back( helper );
        Locator::Provide(helper);
    }
}
