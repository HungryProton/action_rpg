#include <cstdlib>
#include "core/game/game.hpp"

int main(){
    game::Game::Initialize();
    game::Game::Play();
    return EXIT_SUCCESS;
}
