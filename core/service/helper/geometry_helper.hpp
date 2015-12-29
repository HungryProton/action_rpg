#ifndef GAME_CORE_SERVICE_GEOMETRY_HELPER_HPP
#define GAME_CORE_SERVICE_GEOMETRY_HELPER_HPP

#include <map>
#include "tools/opengl.hpp"
#include "core/service/service.hpp"
#include "core/component/drawable.hpp"
#include "core/component/mesh.hpp"

namespace game{

	class GeometryHelper : public Service{
		public:
			GeometryHelper();
			~GeometryHelper();
			void ClearMemory();

			void GetBox(Drawable*);
			void GetCircles(Drawable*);
			void GetMesh(Mesh*, Drawable*);

		private:
			/**
			 * @brief Stores the circles ibo according to their resolution
			 * (The amount of vertices used to draw the perimeter of the circle)
			 */
			std::map<int, GLuint> circles;

			/**
			 * @brief Stores the meshes ibo sorted associated with their file name
			 */

			std::map<std::string, GLuint> meshes;

			/**
			 * @brief All the boxes are the same, they are scaled to their
			 * proper dimensions on the render system
			 */
			GLuint box;
	};
}

#endif //GAME_CORE_SERVICE_GEOMETRY_HELPER_HPP
