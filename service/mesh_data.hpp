#ifndef GAME_SERVICE_MESH_DATA_HPP
#define GAME_SERVICE_MESH_DATA_HPP

#include <vector>
#include "deps/tiny_obj_loader.hpp"

namespace game{

	struct MeshData{
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
	};
}

#endif //GAME_SERVICE_MESH_DATA_HPP
