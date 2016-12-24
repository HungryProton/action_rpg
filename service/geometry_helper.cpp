#include "geometry_helper.hpp"
#include "service/service.hpp"
#include "buffer_allocator.hpp"
#include "common/opengl.hpp"
#include "common/logger.hpp"

namespace game{

	GeometryHelper::GeometryHelper(){
		this->box_ = 0;
		this->box_offset_ = 0;
		this->screen_box_ = 0;
		this->screen_box_offset_ = 0;
	}

	GeometryHelper::~GeometryHelper(){

	}

	void GeometryHelper::ClearMemory(){

	}

	void GeometryHelper::MakeDrawableUseBoxBuffer(Drawable* drawable){

		if( this->box_ == 0){

			std::multimap<int, std::vector<float> > data;

			float vertexArray[] = {
				-1/2.f, 0, 1,
				-1/2.f, 0, 0,
				1/2.f, 0, 1,
				1/2.f, 0, 0
			};

			data.insert( std::pair<int, std::vector<float> >(
								VERTEX_ARRAY,
								std::vector<float>(
									vertexArray,
									vertexArray + 12))); // 4 vertex * 3

			float normalArray[] = {
				0.f, -1.f, 0.f,
				0.f, -1.f, 0.f,
				0.f, -1.f, 0.f,
				0.f, -1.f, 0.f
			};

			data.insert( std::pair<int, std::vector<float> >(
								NORMAL_ARRAY,
								std::vector<float>(
									normalArray,
									normalArray + 12))); // 4 vertex * 3

			// Build the texture coordinates array
			float texture_coords_array[] = {
				0, 1,
				0, 0,
				1, 1,
				1, 0
			};

			data.insert( std::pair<int, std::vector<float> >(
							 TEXTURE_COORDS,
							 std::vector<float>(texture_coords_array,
												texture_coords_array + 8)));

			unsigned int indexArray[] = {
				0, 1, 2,
				3, 2, 1
			};

			std::vector<unsigned int> indices = std::vector<unsigned int>(
									indexArray, indexArray + 6); // 2 triangles * 3

			this->box_ = Service::Get<BufferAllocator>()->RegisterData(data, indices, &(drawable->offset));
			this->box_offset_ = drawable->offset;
		}

		drawable->vao = this->box_;
		drawable->draw_type = GL_TRIANGLES;
		drawable->vertex_amount = 6;
		drawable->offset = this->box_offset_;
	}

	/*
	void GeometryHelper::GetCircle(Circle* circle, GLuint* vao, GLuint* draw_type, int* amount, int* offset){

		int resolution = circle->vertex_amount;

		auto it = circles.find(resolution);

		if( it != circles.end()){
			*vao = it->second;
		} else {
			if( circle->radius < 0){
				circle->radius = 1.f;
			}

			if( circle->vertex_amount < 3){
				circle->vertex_amount = 3;
			}

			std::multimap<int, std::vector<float> > data;
			std::vector<float> vertex_array;
			std::vector<float> texture_coords;
			std::vector<unsigned int> index_array;

			// First vertex, middle of the circle
			vertex_array.push_back(0.f);
			vertex_array.push_back(0.f);
			vertex_array.push_back(0.f);

			index_array.push_back(0);

			texture_coords.push_back(0.5f);
			texture_coords.push_back(0.5f);

			for( int i = 0; i < circle->vertex_amount+1; i++ ){
				float angle = i * (2*PI / circle->vertex_amount) ;

				float x = cos(angle);
				float z = sin(angle);

				texture_coords.push_back((x/2)+0.5f);
				texture_coords.push_back((z/2)+0.5f);

				x *= circle->radius;
				z *= circle->radius;

				vertex_array.push_back(x);
				vertex_array.push_back(0.f);
				vertex_array.push_back(z);
				index_array.push_back(i+1);
			}

			data.insert( std::pair<int, std::vector<float> >(
						VERTEX_ARRAY, vertex_array));

			data.insert( std::pair<int, std::vector<float> >(
						TEXTURE_COORDS, texture_coords));

			*vao = Service::Get<BufferAllocator>()->RegisterData(data, index_array, offset);
			this->circles.insert(std::pair<int, GLuint>(resolution, *vao));
		}

		*draw_type = GL_TRIANGLE_FAN;
		*amount = circle->vertex_amount+2;
	}
	*/

	void GeometryHelper::MakeDrawableUseMeshBuffer(Mesh* mesh, Drawable* drawable){
		std::string full_path = mesh->base_path + mesh->file_name;
		drawable->vertex_amount = mesh->data->shapes[0].mesh.indices.size();
		drawable->draw_type = GL_TRIANGLES;

		auto it = this->meshes_.find(full_path);
		if(it != this->meshes_.end()){
			drawable->vao = it->second.vao;
			drawable->offset = it->second.offset;
			return;
		}

		// else load the mesh in video memory

		std::multimap<int, std::vector<float>> data;
		data.insert(std::pair<int, std::vector<float>>(VERTEX_ARRAY, mesh->data->shapes[0].mesh.positions));
		data.insert(std::pair<int, std::vector<float>>(NORMAL_ARRAY, mesh->data->shapes[0].mesh.normals));
		data.insert(std::pair<int, std::vector<float>>(TEXTURE_COORDS, mesh->data->shapes[0].mesh.texcoords));
		std::vector<unsigned int> indices = mesh->data->shapes[0].mesh.indices;

		BufferData buffer;

		buffer.vao = Service::Get<BufferAllocator>()->RegisterData(data, indices, &(buffer.offset));
		drawable->vao = buffer.vao;
		drawable->offset = buffer.offset;
		this->meshes_.insert(std::pair<std::string, BufferData>(full_path, buffer));
	}

	void GeometryHelper::MakeDrawableUseScreenSpaceBox(Drawable* drawable){
		if(!drawable){
			LOG(ERROR) << "Null pointer was passed" << std::endl;
			return;
		}

		if(this->screen_box_ == 0){
			std::multimap<int, std::vector<float> > data;

			float vertexArray[] = {
				-1.f, 1.f, 0.f,
				-1.f, -1.f, 0.f,
				1.f, 1.f, 0.f,
				1.f, -1.f, 0.f
			};

			data.insert( std::pair<int, std::vector<float> >(
								VERTEX_ARRAY,
								std::vector<float>(
									vertexArray,
									vertexArray + 12))); // 4 vertex * 3

			// Build the texture coordinates array
			float texture_coords_array[] = {
				0, 1,
				0, 0,
				1, 1,
				1, 0
			};

			data.insert( std::pair<int, std::vector<float> >(
							 TEXTURE_COORDS,
							 std::vector<float>(texture_coords_array,
												texture_coords_array + 8)));

			unsigned int indexArray[] = {
				0, 1, 2, 3
			};

			std::vector<unsigned int> indices = std::vector<unsigned int>(
									indexArray, indexArray + 4);

			this->screen_box_ = Service::Get<BufferAllocator>()->RegisterData(data, indices, &(drawable->offset));
			this->screen_box_offset_ = drawable->offset;
		}
		drawable->vao = this->screen_box_;
		drawable->vertex_amount = 4;
		drawable->draw_type = GL_TRIANGLE_STRIP;
		drawable->offset = this->screen_box_offset_;
	}
}
