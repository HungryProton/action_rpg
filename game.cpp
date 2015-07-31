#include "game.hpp"
#include "core/service/render/render.hpp"
#include "tools/logger.hpp"

namespace game{

    void Game::Initialize(){
        log(INFO) << "Initialize game" << std::endl;

        render_ = new Render();
    }

    void Game::Stop(){
        state_ = EXITING;
    }

    void Game::ClearMemory(){
        delete render_;
    }

    void Game::Play(){
        state_ = RUNNING;

        while(state_ == RUNNING){
            render_->Update();
        }

        ClearMemory();
    }

    State Game::GetState(){
        return state_;
    } 
    
    Render* Game::render_;
    State Game::state_ = UNINITIALIZED;
}
