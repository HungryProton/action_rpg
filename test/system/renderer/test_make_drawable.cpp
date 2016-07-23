#include <iostream>
#include <fstream>
#include "deps/catch.hpp"
#include "messaging/message_handler.hpp"
#include "test/context_util.hpp"
#include "ecs/ecs.hpp"
#include "component/texture.hpp"
#include "component/drawable.hpp"
#include "system/renderer/drawable_builder.hpp"
#include "service/service.hpp"

namespace game{

	SCENARIO("DrawableBuilder should process empty drawables when requested"){
		ContextUtil::CreateOpenGLContext();

		GIVEN("a newly created sprite entity with a drawable component"){
			Entity sprite = ecs::CreateEntity();
			ecs::CreateComponent<Texture>(sprite, "test/data/1.png");
			Drawable* d = ecs::CreateComponent<Drawable>(sprite);
			d->type = DrawableType::SPRITE;
			REQUIRE(d->vao == 0);

			WHEN("the entity is passed to a drawableBuilder"){
				DrawableBuilder builder;
				builder.UpdateDrawableOf(sprite);

				REQUIRE(d->vao != 0);
			}
			ecs::ClearMemory();
			Service::ClearMemory();
		}
		ContextUtil::DestroyOpenGLContext();
	}
}
