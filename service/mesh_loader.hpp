#ifndef GAME_SERVICE_MESH_LOADER_HPP
#define GAME_SERVICE_MESH_LOADER_HPP

#include <map>
#include "mesh_data.hpp"
#include "service_worker.hpp"

namespace game{

	class MeshLoader : public ServiceWorker{
		public:
			MeshLoader();
			~MeshLoader();

			void ClearMemory();
			MeshData* LoadFromFile(std::string base_path, std::string file_name);

		private:
			MeshData* GetAlreadyLoadedMesh(std::string);

			std::map<std::string, MeshData*> meshes_;
	};
}

#endif //GAME_SERVICE_MESH_LOADER_HPP
