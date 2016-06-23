#ifndef GAME_CORE_ENTITY_COMPONENT_MESH_HPP
#define GAME_CORE_ENTITY_COMPONENT_MESH_HPP

#include <vector>
#include <map>
#include "common/opengl.hpp"
#include "common/glm.hpp"
#include "deps/tiny_obj_loader.hpp"
#include "component.hpp"

namespace game{

	/** \brief Mesh component
	 *
	 *	This component store geometry data, texture coordinates
	 *	and textures pointer. Texture coordinates and textures
	 *	are stored in arrays to handle multiple textures at once.
	 *
	 */
	struct Mesh : public Component{

		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		GLenum draw_type;
		std::string file_path;
		std::string base_path;

		// ---- Helper methods ----

		Mesh();
		virtual ~Mesh();
		Mesh(Entity);
		Mesh(std::string, Entity);
		Mesh(std::string);
		Mesh(Mesh*);
		void LoadFromFile(std::string);
		void LoadTextureFromMaterial();
		virtual Mesh* Clone();
	};
}

#endif // GAME_CORE_ENTITY_COMPONENT_MESH_HPP
