#ifndef GAME_SYSTEM_RENDERER_DRAWABLE_BUILDER_HPP
#define GAME_SYSTEM_RENDERER_DRAWABLE_BUILDER_HPP

#include "component/drawable.hpp"

namespace game{

	class DrawableBuilder{
		public:
			DrawableBuilder();
			~DrawableBuilder();
			int UpdateDrawableOf(Entity);

		private:
			int UpdateSpriteDrawable(Drawable*, Entity);
			int UpdateMeshDrawable(Drawable*, Entity);
	};
}

#endif //GAME_SYSTEM_RENDERER_DRAWABLE_BUILDER_HPP
