#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "messaging/message_handler.hpp"
#include "test/context_util.hpp"
#include "entity/entity.hpp"
#include "component/texture.hpp"
#include "component/drawable.hpp"
#include "system/renderer/drawable_builder.hpp"
#include "service/service.hpp"

namespace game{

	const lest::test drawable_builder[] = {
		SCENARIO("DrawableBuilder should process empty drawables when requested"){

			GIVEN("a newly created sprite entity with a drawable component"){
				unsigned long sprite = Entity::Create();
				new Texture("test/data/1.png", sprite);
				Drawable* d = new Drawable(sprite);
				d->type = DrawableType::SPRITE;
				EXPECT(d->vao == 0);

				WHEN("the entity is passed to a drawableBuilder"){
					DrawableBuilder builder;
					LOG(DEBUG) << builder.UpdateDrawableOf(sprite) << std::endl;

					EXPECT(d->vao != 0);
				}
				Entity::Destroy(sprite);
				Service::ClearMemory();
			}
		}
	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), drawable_builder);
}
