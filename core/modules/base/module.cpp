#include "module.hpp"
#include "tools/logger.hpp"

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
            this->thread_ = new std::thread(&Module::Run, this);
            this->thread_->join();
            this->initialized_ = true;
        }
    }

    ModuleState Module::GetState(){
        return this->module_state_;
    }

    void Module::Stop(){
        this->module_state_ = EXITING;
    }
}
