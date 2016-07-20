#ifndef GAME_CORE_ENTITY_COMPONENT_MESH_HPP
#define GAME_CORE_ENTITY_COMPONENT_MESH_HPP

#include <vector>
#include <map>
#include "common/opengl.hpp"
#include "common/glm.hpp"
#include "deps/tiny_obj_loader.hpp"
#include "ecs/entity/entity.hpp"

namespace game{

	/** \brief Mesh component
	 *
	 *	This component store geometry data, texture coordinates
	 *	and textures pointer. Texture coordinates and textures
	 *	are stored in arrays to handle multiple textures at once.
	 *
	 */
	struct Mesh{

		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		GLenum draw_type;
		std::string file_path;
		std::string base_path;

		Entity parent;

		// ---- Helper methods ----

		Mesh(std::string);
		void LoadFromFile(std::string);
		void LoadTextureFromMaterial();
	};
}

#endif // GAME_CORE_ENTITY_COMPONENT_MESH_HPP
