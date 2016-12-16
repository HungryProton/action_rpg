#ifndef GAME_CORE_SERVICE_GEOMETRY_HELPER_HPP
#define GAME_CORE_SERVICE_GEOMETRY_HELPER_HPP

#include <map>
#include "common/opengl.hpp"
#include "component/graphic/drawable.hpp"
#include "component/graphic/mesh.hpp"
#include "service_worker.hpp"

namespace game{

	class GeometryHelper : public ServiceWorker{
		public:
			GeometryHelper();
			~GeometryHelper();
			void ClearMemory();

			void MakeDrawableUseBoxBuffer(Drawable*);
			void MakeDrawableUseCircleBuffer(Drawable*);
			void MakeDrawableUseMeshBuffer(Mesh*, Drawable*);
			void MakeDrawableUseScreenSpaceBox(Drawable*);

		private:
			/**
			 * @brief Stores the circles ibo according to their resolution
			 * (The amount of vertices used to draw the perimeter of the circle)
			 */
			std::map<int, GLuint> circles_;

			/**
			 * @brief Stores the meshes ibo sorted associated with their file name
			 */

			std::map<std::string, GLuint> meshes_;

			/**
			 * @brief All the boxes are the same, they are scaled to their
			 * proper dimensions on the render system
			 */
			GLuint box_;
			int box_offset_;
			GLuint screen_box_;
			int screen_box_offset_;
	};
}

#endif //GAME_CORE_SERVICE_GEOMETRY_HELPER_HPP
