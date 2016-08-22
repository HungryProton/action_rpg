#include "wall_generator.hpp"
#include "common/logger.hpp"
#include "common/random.hpp"
#include "common/structure.hpp"
#include "ecs/ecs.hpp"
#include "component/transform.hpp"
#include "component/mesh.hpp"
#include "component/drawable.hpp"
#include <dirent.h>

namespace game{

	WallGenerator::WallGenerator() : random_(0){

	}

	std::vector<Wall> WallGenerator::Generate(double seed){
		random_ = IntGenerator(seed);

		GenerateFoundationsLayout();
		return PlaceWalls();
		//return std::vector<Wall>();
	}

	void WallGenerator::GenerateFoundationsLayout(){

		// Generate random square
		int min_w = parameters_.minimum_dimensions.x;
		int min_h = parameters_.minimum_dimensions.y;
		int max_w = parameters_.maximum_dimensions.x;
		int max_h = parameters_.maximum_dimensions.y;

		const int width = random_.Next(min_w, max_w);
		const int height = random_.Next(min_h, max_h);

		Structure::Fill2DVector(&foundations_, width, height, 0);
		AddSquare(0, 0, width, height);

		// Generate other square or maybe 2

		// substract generated square to base square
	}

	std::vector<Wall> WallGenerator::PlaceWalls(){
		std::vector<Wall> walls;

		unsigned int width = foundations_.size();
		unsigned int height = foundations_[0].size();

		for(unsigned int i = 0; i < foundations_.size(); i++){
			for(unsigned int j = 0; j < foundations_[0].size(); j++){
				if(foundations_[i][j] == 0){ continue; } // Ignore if empty space
				if(i == 0){
					if(j == 0){ // Top left corner
						walls.push_back(GetCorner(0, 0, 0, true));
						walls.push_back(GetCorner(0, 0, 0, false));
					} else if(j == height - 1){ // Bottom left corner
						walls.push_back(GetCorner(0, 0, -90, true));
						walls.push_back(GetCorner(0, 0, -90, false));
					} else if(foundations_[i+1][j] == 1) {
						if(foundations_[i][j+1] == 1){ // TopLeft corner
							walls.push_back(GetCorner(0, 0, 0, true));
							walls.push_back(GetCorner(0, 0, 0, false));
						} else {
							walls.push_back(GetCorner(0, 0, -90, true));
							walls.push_back(GetCorner(0, 0, -90, false));
						}
					} else if(foundations_[i][j+1] == 1 && foundations_[i][j-1] == 1){
						walls.push_back(GetFlat(0, 0, -90, true));
						walls.push_back(GetFlat(0, 0, -90, false));
					}
				}
			}
		}

		return walls;
	}

	Wall WallGenerator::GetCorner(int delta_x, int delta_y, int angle, bool inner){
		Wall wall;
		wall.entity = ecs::CreateEntity();
		Transform* t = ecs::CreateComponent<Transform>(wall.entity);
		t->position.x = delta_x + parameters_.building_position.x;
		t->position.y = delta_y + parameters_.building_position.y;
		t->position.z = parameters_.building_position.y;
		t->rotation.z = angle;

		std::string name = parameters_.base_directory;
		if(inner){
			name += "inner_corner_A1.obj";
		} else {
			name += "outer_corner_A1.obj";
		}

		ecs::CreateComponent<Mesh>(wall.entity)->LoadFromFile(name);
		ecs::CreateComponent<Drawable>(wall.entity, DrawableType::MESH);

		return wall;
	}

	Wall WallGenerator::GetFlat(int delta_x, int delta_y, int angle, bool inner){
		Wall wall;

		return wall;
	}

	void WallGenerator::AddSquare(int x, int y, unsigned int width, unsigned int height){
		if(width == 0 || height == 0){ return; }
		if(width > foundations_.size()){ return; }
		if(height > foundations_[0].size()){ return; }

		for(unsigned int i = 0; i < width; i++){
			for(unsigned int j = 0; j < height; j++){
				if(i == 0 || j == 0 || i == width - 1 || j == height - 1){
					foundations_[i+x][j+y] = 1;
				}
			}
		}
	}

	void WallGenerator::SetParameters(WallParameters params){
		parameters_ = params;
	}
}
