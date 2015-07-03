#include "module.hpp"

namespace game{

    Module::Module(){
        this->initialized_ = false;
        this->thread_ = nullptr;
    }

    Module::~Module(){
        this->Stop();
        if(this->thread_) delete this->thread_;
    }

    void Module::Start(){
        if( !this->initialized_ ){
            this->thread_ = new std::thread(&Module::Process, this);
            this->initialized_ = true;
        }
    }

    void Module::Stop(){

    }
}
