#include <iostream>
#include "mesh.hpp"
#include "texture.hpp"

namespace game{

	Mesh::Mesh(){

	}

	Mesh::Mesh(GameObject* p) : Mesh() {
		this->parent = p;
	}

	Mesh::Mesh(std::string path, GameObject* p ) : Mesh(p){
		p->AttachComponent(this);
		this->LoadFromFile(path);
	}

	Mesh::Mesh(Mesh* mesh){
		this->shapes = mesh->shapes;
		this->materials = mesh->materials;
		this->draw_type = mesh->draw_type;
		this->file_path = mesh->file_path;
		this->is_attached = false;
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
		new Texture(texture_path, this->parent);
	}

	Mesh* Mesh::Clone(){
		return new Mesh(this);
	}
}
