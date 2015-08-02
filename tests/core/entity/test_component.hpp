#ifndef TEST_ENTITY_COMPONENTS_HPP
#define TEST_ENTITY_COMPONENTS_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "tools/logger.hpp"
#include "core/entity/component/texture.hpp"
#include "core/entity/gameobject/game_object.hpp"
#include "game.hpp"

namespace game{

    const lest::test components[] = {

        CASE("Should attach properly to a GameObject"){
            GameObject* game_object = new GameObject();
            Component* component = new Component();

            // Attach manually
            EXPECT( component->is_attached == false );
            game_object->AttachComponent( component );

            EXPECT( component->is_attached == true );

            // Attached automatically by constructor
            Component* component2 = new Component( game_object );
            EXPECT( component2->is_attached == true );

            // CAUTION, deleting a GameObject also deletes all of his components
            delete game_object;
        },

        CASE("Should create a texture component from file"){
            Game::Initialize();
            Texture texture("tests/resources/1.png");
            EXPECT( texture.IsValid() == true );

            Texture unknow_texture("this/file/does/not/exists.png");
            EXPECT( unknow_texture.IsValid() == false );
        }

    };

    static int run_components_test_suite(int argc, char** argv){

        log(SILENT) << std::endl;
        log(SILENT) << "#--------------------" << std::endl;
        log(SILENT) << "# Components test suite " << std::endl;
        log(SILENT) << "#--------------------" << std::endl << std::endl;

        return lest::run( components, argc, argv, std::cout );
    }
}

#endif //TEST_TOOLS_LOGGER_HPP
