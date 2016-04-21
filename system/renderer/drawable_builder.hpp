#ifndef GAME_SYSTEM_RENDERER_DRAWABLE_BUILDER_HPP
#define GAME_SYSTEM_RENDERER_DRAWABLE_BUILDER_HPP

#include "component/drawable.hpp"

namespace game{

	class DrawableBuilder{
		public:
			DrawableBuilder();
			~DrawableBuilder();
			int UpdateDrawableOf(unsigned long);

		private:
			int UpdateSpriteDrawable(Drawable*, unsigned long);
			int UpdateMeshDrawable(Drawable*, unsigned long);
	};
}

#endif //GAME_SYSTEM_RENDERER_DRAWABLE_BUILDER_HPP
