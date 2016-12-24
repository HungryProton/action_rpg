#include <iostream>
#include "mesh_loader.hpp"
#include "common/logger.hpp"

namespace game{

	MeshLoader::MeshLoader(){

	}

	MeshLoader::~MeshLoader(){
		this->ClearMemory();
	}

	void MeshLoader::ClearMemory(){
		auto it = this->meshes_.begin();
		while(it != this->meshes_.end()){
			MeshData* data = it->second;
			it++;
			delete data;
		}
		meshes_.clear();
	}

	MeshData* MeshLoader::LoadFromFile(std::string base_path, std::string file_name){
		std::string full_path = base_path + file_name;

		// If Mesh was already loaded, return it
		MeshData* m = this->GetAlreadyLoadedMesh(full_path);
		if(m){ return m; }

		// Actually load the mesh from file
		m = new MeshData();
		std::string err = tinyobj::LoadObj(m->shapes, m->materials,
										   full_path.c_str(), base_path.c_str());

		if (!err.empty()) {
			LOG(WARNING) << "Cannot load file " << full_path << std::endl;
			std::cout << err << std::endl;
			return nullptr;
		}

		this->meshes_.insert( std::pair<std::string, MeshData*>(full_path, m));
		return m;
	}

	MeshData* MeshLoader::GetAlreadyLoadedMesh(std::string file_path){
		auto it = this->meshes_.find(file_path);

		if(it != this->meshes_.end()){
			return it->second;
		}
		return nullptr;
	}
}
