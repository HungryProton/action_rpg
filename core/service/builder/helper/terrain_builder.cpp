#include <vector>
#include <cmath>
#include "terrain_builder.hpp"
#include "tools/random.hpp"
#include "core/game/game.hpp"
#include "core/service/helper/buffer_helper.hpp"
#include "core/locator/locator.hpp"
#include "core/component/transform.hpp"
#include "core/component/drawable.hpp"
#include "core/component/texture.hpp"
#include "core/service/helper/polygon_helper.hpp"

namespace game{

	TerrainBuilder::TerrainBuilder(){
		Game::RequestForService<BufferHelper>();
		this->size_.x=10;
		this->size_.y=10;
		this->max_altitude_variation_ = 4;
		this->layers_count_ = 3;
		this->resolution_ = 4;
	}

	TerrainBuilder::~TerrainBuilder(){

	}

	void TerrainBuilder::ClearMemory(){

	}

	GameObject* TerrainBuilder::GenerateTerrain(){
		std::vector<unsigned int> index_array;
		std::multimap<int, std::vector<float>> data;

		for(int i = 0; i < this->layers_count_; i++){

		}

		GeneratePolygon(&data, &index_array);

		GameObject* terrain = new GameObject();
		new Transform(terrain);
		Drawable* drawable = new Drawable(terrain);
		new Texture("../data/environment/terrain/grass.png", terrain);

		drawable->vao = Locator::Get<BufferHelper>()->RegisterData(data, index_array, &(drawable->offset));
		drawable->draw_type = GL_TRIANGLES;
		drawable->vertex_amount = index_array.size();

		return terrain;
	}

	void TerrainBuilder::GeneratePolygon(std::multimap<int, std::vector<float>>* data, std::vector<unsigned int>* index_array){
		std::vector<float> vertex_array = this->GenerateOutline();
		PolygonHelper polygon_helper;
		Polygon surface = polygon_helper.FloatArrayToSinglePolygon(vertex_array);
		polygon_helper.SinglePolygonToGLData(surface, data, index_array);
	}

	std::vector<float> TerrainBuilder::GenerateOutline(){
		std::vector<float> vertex_array;

		// Generate first triangle
		float triangle[] = {
			-size_.x/2.f, -size_.y/2.f, 0.f,
			-Random::NextFloat(size_.x/2.f), size_.y/2.f, 0.f,
			size_.x/2.f, (size_.y/4.f) - Random::NextFloat(size_.y/2.f), 0.f
		};

		vertex_array.insert(vertex_array.begin(), triangle, triangle + 9);

		// Refine surface area
		float attenuation = 0.6f;
		this->resolution_ = 6;
		for(int i = 0; i < this->resolution_; i++){
			vertex_array = MidpointDisplacement(vertex_array, attenuation);
			attenuation /= 2.f;
		}
		return vertex_array;
	}

	std::vector<float> TerrainBuilder::MidpointDisplacement(std::vector<float> vertex_array, float attenuation){

		for(unsigned int i = 0; i < vertex_array.size(); i+=6){

			glm::vec3 vertex_a = glm::vec3(vertex_array[i], vertex_array[i+1], vertex_array[i+2]);
			glm::vec3 vertex_b;
			if(i >= vertex_array.size()-3){
				vertex_b = glm::vec3(vertex_array[0], vertex_array[1], vertex_array[2]);
			} else {
				vertex_b = glm::vec3(vertex_array[(i+3)],
														vertex_array[(i+4)],
														vertex_array[(i+5)]);
			}

			glm::vec3 midpoint = (vertex_a + vertex_b)/2.f;
			float A = (3.14/2.f) - ( std::atan( (midpoint.x - vertex_a.x) / (midpoint.y - vertex_a.y) ) );
			float displacement = ((this->size_.x/2.f) - Random::NextFloat(this->size_.x)) * attenuation;


			midpoint.x += displacement * -std::sin(A);
			midpoint.y += displacement * std::cos(A);

			vertex_array.insert(vertex_array.begin()+i+3, midpoint.x);
			vertex_array.insert(vertex_array.begin()+i+4, midpoint.y);
			vertex_array.insert(vertex_array.begin()+i+5, midpoint.z);
		}
		return vertex_array;
	}

	std::vector<float> TerrainBuilder::GetTextureCoordinates(std::vector<float> vertex_array){
		std::vector<float> texture_coords;

		float max_x = vertex_array[0];
		float max_y = vertex_array[1];
		float min_x = vertex_array[0];
		float min_y = vertex_array[1];

		for(unsigned int i = 3; i < vertex_array.size(); i+=3){
			if(max_x < vertex_array[i]){
				max_x = vertex_array[i];
			}
			if(min_x > vertex_array[i]){
				min_x = vertex_array[i];
			}
			if(max_y < vertex_array[i+1]){
				max_y = vertex_array[i+1];
			}
			if(min_y > vertex_array[i+1]){
				min_y = vertex_array[i+1];
			}
		}

		float width = max_x - min_x;
		float height = max_y - min_y;

		for(unsigned int i = 0; i < vertex_array.size(); i+=3){
			texture_coords.push_back( (vertex_array[i] + (width/2.f))/width );
			texture_coords.push_back( (vertex_array[i+1] + (height/2.f))/height );
		}

		return texture_coords;
	}

	void TerrainBuilder::SetResolution(int resolution){
		this->resolution_ = resolution;
	}

	void TerrainBuilder::SetMapSize(float width, float height){
		this->size_.x = width;
		this->size_.y = height;
	}

	void TerrainBuilder::SetMaxAltitudeVariation(float variation){
		this->max_altitude_variation_ = variation;
	}

	void TerrainBuilder::SetLayersCount(int count){
		this->layers_count_ = count;
	}

}
