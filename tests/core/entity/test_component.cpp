#ifndef TEST_ENTITY_COMPONENTS_HPP
#define TEST_ENTITY_COMPONENTS_HPP

#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "tools/logger.hpp"
#include "core/entity/component/texture.hpp"
#include "core/entity/gameobject/game_object.hpp"
#include "core/game/game.hpp"

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
            Texture texture("tests/resources/1.png");
            EXPECT( texture.IsValid() == true );

            Texture unknow_texture("this/file/does/not/exists.png");
            EXPECT( unknow_texture.IsValid() == false );
        }

    };

    extern lest::tests & specifications();
    lest_ADD_MODULE(specifications(), components);
}

#endif //TEST_TOOLS_LOGGER_HPP
