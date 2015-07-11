#include "tools/logger.hpp"
#include "render.hpp"

namespace game{

    Render::Render(){

    }

    Render::~Render(){

    }

    void Render::HandleMessage(Message msg){

    }

    void Render::Run(){
        log(INFO) << "Render process method was called !!!!!!! " << std::endl;

    }
}
