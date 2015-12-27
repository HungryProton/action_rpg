#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/game/game.hpp"
#include "core/entity/game_object.hpp"

namespace game{

    const lest::test game[] = {

        CASE("Should create a playable character"){
            Game::Initialize();
            //GameObject* character = Locator::Get<CharacterMaker>().Create(PLAYABLE);
            //EXPECT( character != nullptr );
        },

        CASE("Should create some NPCs"){

        },

        CASE("Should generate a simple world"){
            Game::Initialize();
            //World* world = Locator::Get<WorldBuilder>().GenerateRandomWorld();
            //EXPECT( world != nullptr );
        },

        CASE("Character should move upon player input"){

        },

        CASE("Character should attack and kill a target"){

        },

        CASE("Character should receive damages when attacked"){

        },

        CASE("Character should died when he receives too much damage"){

        },

        CASE("Character should interact with environment"){

        }

    };
}

