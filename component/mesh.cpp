#include <iostream>
#include "ecs/ecs.hpp"
#include "ecs/entity/entity.hpp"
#include "mesh.hpp"
#include "texture.hpp"

namespace game{

	Mesh::Mesh(std::string path){
		this->parent = ecs::GetParentOfComponent(this);
		this->LoadFromFile(path);
	}

	void Mesh::LoadFromFile(std::string path){
		// Save base path
		this->file_path = path;
		auto found = path.find_last_of("/\\");
		this->base_path = this->file_path.substr(0, found+1);

		// Actually load the mesh from file
		std::string err = tinyobj::LoadObj(this->shapes, this->materials,
										   path.c_str(), this->base_path.c_str());

		if (!err.empty()) {
			  std::cout << err << std::endl;
			  return;
		}
		LoadTextureFromMaterial();
	}

	void Mesh::LoadTextureFromMaterial(){
		std::string texture_path = this->base_path + this->materials[0].diffuse_texname.c_str();
		Texture* tex = ecs::CreateComponentForEntity<Texture>(parent, texture_path);
	}
}
