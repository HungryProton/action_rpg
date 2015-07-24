#include "game.hpp"
#include "core/services/render/render.hpp"
#include "tools/logger.hpp"

namespace game{

    void Game::Start(){
        log(INFO) << "Starting game" << std::endl;
        render_ = new Render();
        state_ = RUNNING;

        Update();
    }

    void Game::Stop(){
        state_ = EXITING;
    }

    void Game::ClearMemory(){
        delete render_;
    }

    void Game::Update(){
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
