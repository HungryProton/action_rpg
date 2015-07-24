#include "game.hpp"
#include "core/services/render/render.hpp"
#include "tools/logger.hpp"

namespace game{

    void Game::Start(){
        log(INFO) << "Starting game" << std::endl;
        render_ = new Render();

        Update();
    }

    void Game::Update(){
        while(1){

            render_->Update();

        }
    }
    
    Render* Game::render_;
}
