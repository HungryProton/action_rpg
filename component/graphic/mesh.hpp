#ifndef GAME_CORE_ENTITY_COMPONENT_MESH_HPP
#define GAME_CORE_ENTITY_COMPONENT_MESH_HPP

#include <vector>
#include <map>
#include "common/opengl.hpp"
#include "common/glm.hpp"
#include "ecs/entity/entity.hpp"
#include "service/mesh_data.hpp"

namespace game{

	/** \brief Mesh component
	 *
	 *	This component store geometry data, texture coordinates
	 *	and textures pointer. Texture coordinates and textures
	 *	are stored in arrays to handle multiple textures at once.
	 *
	 */
	struct Mesh{

		MeshData* data;
		GLenum draw_type;
		std::string file_name;
		std::string base_path;

		Entity parent;

		// ---- Helper methods ----

		void LoadFromFile(std::string);
		void LoadTextureFromMaterial();
	};
}

#endif // GAME_CORE_ENTITY_COMPONENT_MESH_HPP
