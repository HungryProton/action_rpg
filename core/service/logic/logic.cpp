#include "logic.hpp"
#include "core/locator/locator.hpp"
#include "core/service/builder/world_builder.hpp"

namespace game{

    Logic::Logic(){

    }

    Logic::~Logic(){
        this->ClearMemory();
    }


    void Logic::Initialize(){

        WorldBuilder* world_builder = Locator::Get<WorldBuilder>();


    }

    void Logic::ClearMemory(){

    }

    void Logic::Update(){



    }

}
