#include "polygon_helper.hpp"
#include "tools/opengl.hpp"
#include "tools/logger.hpp"

namespace game{

	PolygonHelper::PolygonHelper(){

	}

	PolygonHelper::~PolygonHelper(){

	}

	Polygon PolygonHelper::FloatArrayToSinglePolygon(std::vector<float> raw_array){
		auto vertices = this->FloatArrayToVertices(raw_array);
		return this->VertexArrayToPolygon(vertices);
	}

	std::vector<Vertex> PolygonHelper::FloatArrayToVertices(std::vector<float> raw_array){
		std::vector<Vertex> result;
		for(unsigned int i = 0; i < raw_array.size(); i+=3){
			Vertex v;
			v.position = glm::vec3(raw_array[i], raw_array[i+1], raw_array[i+2]);
			result.push_back(v);
		}
		this->UpdateTextureCoordinates(&result);
		return result;
	}

	void PolygonHelper::UpdateTextureCoordinates(std::vector<Vertex>* vertex_array){
		float max_x = (*vertex_array)[0].position.x;
		float max_y = (*vertex_array)[0].position.y;
		float min_x = max_x;
		float min_y = max_y;

		for(unsigned int i = 1; i < vertex_array->size(); i++){
			float current_x = (*vertex_array)[i].position.x;
			float current_y = (*vertex_array)[i].position.y;

			if(max_x < current_x){
				max_x = current_x;
			}
			if(min_x > current_x){
				min_x = current_x;
			}
			if(max_y < current_y){
				max_y = current_y;
			}
			if(min_y > current_y){
				min_y = current_y;
			}
		}

		float width = max_x - min_x;
		float height = max_y - min_y;

		for(unsigned int i = 0; i < vertex_array->size(); i++){
			Vertex* v = &((*vertex_array)[i]);
			v->texture_coordinates.x = (v->position.x + (width/2.f))/width;
			v->texture_coordinates.y = (v->position.y + (height/2.f))/height;
			v->texture_coordinates.x *= this->texture_modifier_;
			v->texture_coordinates.y *= this->texture_modifier_;
		}
	}

	Polygon PolygonHelper::VertexArrayToPolygon(std::vector<Vertex> vertex_array){
		Polygon polygon;
		if(IsCollectionValid(vertex_array)){
			polygon.vertices = vertex_array;
			polygon.indices = this->Triangulate(vertex_array);
		}
		return polygon;
	}

	std::vector<unsigned int> PolygonHelper::Triangulate(std::vector<Vertex> vertex_array){
		std::map<unsigned int, Vertex> vertex_map;
		for(unsigned int i = 0; i < vertex_array.size(); i++){
			vertex_map.insert(std::make_pair(i, vertex_array[i]));
		}

		std::vector<unsigned int> indices;

		while(vertex_map.size() >= 3){

			float smallest_edge = -1;
			int index_a;
			int index_b;
			int index_c;

			for(auto it = vertex_map.begin(); it != vertex_map.end(); it++){

				int index_current = it->first;
				int index_previous;
				int index_next;

				Vertex current = it->second;
				Vertex previous;
				Vertex next;

				if(it != vertex_map.begin()){
					it--;
					previous = it->second;
					index_previous = it->first;
					it++;
				}else{
					auto it2 = vertex_map.rbegin();
					previous = it2->second;
					index_previous = it2->first;
				}

				it++;
				if(it != vertex_map.end()){
					next = it->second;
					index_next = it->first;
				} else {
					auto it2 = vertex_map.begin();
					next = it2->second;
					index_next = it2->first;
				}
				it--;

				if(!IsTriangleConvex(previous, current, next)){
					continue;
				}

				float edge = glm::distance(previous.position, next.position);

				if((edge < smallest_edge) || (smallest_edge == -1)){
					smallest_edge = edge;
					index_a = index_previous;
					index_b = index_current;
					index_c = index_next;
				}
			}

			indices.push_back(index_c);
		 	indices.push_back(index_b);
			indices.push_back(index_a);

			auto element_to_remove = vertex_map.find(index_b);
			if(element_to_remove == vertex_map.end()){
				LOG(CRITICAL) << "This shouldn't have happened" << std::endl;
				return indices;
			}else{
				vertex_map.erase( element_to_remove );
			}
		}

		return indices;
	}

	bool PolygonHelper::IsCounterClockwise(Vertex a, Vertex b, Vertex c){
		return (b.position.x - a.position.x) * (c.position.y - b.position.y) -
			(c.position.x - b.position.x) * (b.position.y - a.position.y) > 0;
	}

	bool PolygonHelper::IsTriangleConvex(Vertex a, Vertex b, Vertex c){
		return !IsCounterClockwise(a, b, c);
	}

	bool PolygonHelper::IsPointWithinTriangle(Vertex point, Vertex a, Vertex b, Vertex c){
		float denom = (b.position.y - c.position.y) * (a.position.x - c.position.x) +
			(c.position.x - b.position.x) * (a.position.y - c.position.y);
		if(denom == 0){
			return true;
		}

		denom = 1.f/denom;
		float alpha = denom * ( (b.position.y - c.position.y) * (point.position.x - c.position.x) +
				(c.position.x - b.position.x) * (point.position.y - c.position.y) );

		float beta = denom * ( (c.position.y - a.position.y) * (point.position.x - c.position.x) +
				(a.position.x - c.position.x) * (point.position.y - c.position.y) );

		float gamma = 1.f - alpha - beta;
		return ((alpha >= 0) && (beta >= 0) && (gamma >= 0));
	}

	void PolygonHelper::SinglePolygonToGLData(Polygon polygon,
					std::multimap<int, std::vector<float>>* data,
					std::vector<unsigned int>* indices){

		std::vector<float> vertices = PositionToFloatArray(polygon.vertices);
		std::vector<float> textures = TextureToFloatArray(polygon.vertices);

		data->insert(std::make_pair(VERTEX_ARRAY, vertices));
		data->insert(std::make_pair(TEXTURE_COORDS, textures));
		indices->insert( indices->end(), polygon.indices.begin(), polygon.indices.end() );
	}

	std::vector<float> PolygonHelper::PositionToFloatArray(std::vector<Vertex> vertex_array){
		std::vector<float> result;
		for(Vertex v : vertex_array){
			result.push_back(v.position.x);
			result.push_back(v.position.y);
			result.push_back(v.position.z);
		}
		return result;
	}

	std::vector<float> PolygonHelper::TextureToFloatArray(std::vector<Vertex> vertex_array){
		std::vector<float> result;
		for(Vertex v : vertex_array){
			result.push_back(v.texture_coordinates.x);
			result.push_back(v.texture_coordinates.y);
		}
		return result;
	}

	bool PolygonHelper::IsCollectionValid(std::vector<Vertex> vertex_array){

		for(unsigned int i = 0; i < vertex_array.size(); i++){
			Vertex A = vertex_array[i];
			Vertex B = vertex_array[(i+1)%vertex_array.size()];

			for(unsigned int j = (i+2)%vertex_array.size(); j < vertex_array.size() - 2; j++){
				Vertex C = vertex_array[j];
				Vertex D = vertex_array[(j+1)%vertex_array.size()];

				if((IsCounterClockwise(A,C,D) != IsCounterClockwise(B, C, D))
						&& (IsCounterClockwise(A,B,C) != IsCounterClockwise(A, B, D))){
					return false;
				}
			}
		}
		return true;
	}

	void PolygonHelper::ClearMemory(){

	}

	void PolygonHelper::SetTextureCoordModifier(float modifier){
		this->texture_modifier_ = modifier;
	}
}

