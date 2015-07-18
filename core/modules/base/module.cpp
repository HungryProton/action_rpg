#include "module.hpp"
#include "tools/logger.hpp"

namespace game{

    Module::Module(){
        this->thread_ = nullptr;
        this->state_ = UNINITIALIZED;
    }

    Module::~Module(){
        this->Stop();
        if(this->thread_) delete this->thread_;
    }

    void Module::Start(){
        if( this->state_ == UNINITIALIZED ){
            this->state_ = RUNNING;
            this->thread_ = new std::thread(&Module::Run, this);

            if(!this->thread_){
                log(ERROR) << "Cannot start rendering thread" << std::endl;
                this->state_ = UNINITIALIZED;
            }
        }
    }

    ModuleState Module::GetState(){
        return this->state_;
    }

    void Module::Stop(){
        this->state_ = EXITING;
    }
}
