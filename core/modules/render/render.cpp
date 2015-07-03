#include "tools/logger.hpp"
#include "render.hpp"

namespace game{

    Render::Render(){

    }

    Render::~Render(){

    }

    void Render::Start(){
        Module::Start();

    }

    void Render::Stop(){

    }

    void Render::HandleMessage(Message msg){

    }

    void Render::Process(){
        log(INFO) << "Render process method was called !!!!!!! " << std::endl;

    }
}
