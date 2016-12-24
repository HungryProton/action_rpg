#include <iostream>
#include "common/string.hpp"
#include "ecs/ecs.hpp"
#include "ecs/entity/entity.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "service/service.hpp"
#include "service/mesh_loader.hpp"

namespace game{

	void Mesh::LoadFromFile(std::string path){
		MeshLoader* mesh_loader = Service::Get<MeshLoader>();
		if(mesh_loader == nullptr){ return; }
		this->parent = ecs::GetParentOf(this);

		// Save base path
		auto found = path.find_last_of("/\\");
		this->base_path = path.substr(0, found+1);
		this->file_name = path.substr(found+1);

		data = mesh_loader->LoadFromFile(base_path, file_name);
		if(data == nullptr){ return; }
		LoadTextureFromMaterial();
	}

	void Mesh::LoadTextureFromMaterial(){
		std::string texture_path = this->base_path + StringUtil::Trim(this->data->materials[0].diffuse_texname.c_str());
		ecs::CreateComponent<Texture>(parent, texture_path);
	}
}
