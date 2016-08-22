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

		Structure::Display2DVector(&foundations_);

		// Generate other square or maybe 2

		// substract generated square to base square
	}

	std::vector<Wall> WallGenerator::PlaceWalls(){
		std::vector<Wall> walls;

		unsigned int width = foundations_.size();
		unsigned int height = foundations_[0].size();

		for(unsigned int i = 0; i < width; i++){
			for(unsigned int j = 0; j < height; j++){
				int wall_id = foundations_[i][j];
				if(wall_id == 0){ continue; }
				walls.push_back(GetWall(wall_id, i - (width/2), j - (height/2), false));
				walls.push_back(GetWall(wall_id, i - (width/2), j - (height/2), true));
			}
		}
		return walls;
	}

	Wall WallGenerator::GetWall(int wall_id, int x, int y,  bool inner){
		switch(wall_id){
			case 1:	// Standard facing down
				return GetWall(x, y, 270, false, inner);
			case 2:	// Standard facing left
				return GetWall(x, y, 180, false, inner);
			case 3: // Standard facing right
				return GetWall(x, y, 0, false, inner);
			case 4: // Standard facing up
				return GetWall(x, y, 90, false, inner);
			case 5:	// Top left corner
				return GetWall(x, y, 270, true, inner);
			case 6: // Top right corner
				return GetWall(x, y, 0, true, inner);
			case 7: // bottom left corner
				return GetWall(x, y, 180, true, inner);
			case 8: // bottom right corner
				return GetWall(x, y, 90, true, inner);
			default:
				return Wall();
		}
	}

	Wall WallGenerator::GetWall(int delta_x, int delta_y, int angle, bool corner, bool inner){
		Wall wall;
		wall.entity = ecs::CreateEntity();
		Transform* t = ecs::CreateComponent<Transform>(wall.entity);
		t->position.x = delta_x + parameters_.building_position.x;
		t->position.y = delta_y + parameters_.building_position.y;
		t->position.z = parameters_.building_position.y;
		t->rotation.z = angle;

		std::string name = parameters_.base_directory;
		if(inner){
			name += "inner";
		} else {
			name += "outer";
		}
		if(corner){
			name += "_corner_A1.obj";
		} else {
			name += "_standard_A1.obj";
		}

		ecs::CreateComponent<Mesh>(wall.entity)->LoadFromFile(name);
		ecs::CreateComponent<Drawable>(wall.entity, DrawableType::MESH);

		return wall;
	}

	void WallGenerator::AddSquare(int x, int y, unsigned int width, unsigned int height){
		if(width == 0 || height == 0){ return; }
		if(width > foundations_.size()){ return; }
		if(height > foundations_[0].size()){ return; }

		for(unsigned int i = 0; i < width; i++){
			for(unsigned int j = 0; j < height; j++){
				if(i == 0){
					foundations_[i+x][j+y] = 1;
				} else if (i == width - 1){
					foundations_[i+x][j+y] = 4;
				}
				if(j == 0){
					foundations_[i+x][j+y] = 3;
				} else if (j == height - 1){
					foundations_[i+x][j+y] = 2;
				}

				if(i == 0 && j == 0){
					foundations_[i+x][j+y] = 5;
				} else if (i == 0 && j == height - 1){
					foundations_[i+x][j+y] = 7;
				} else if (i == width -1 && j == 0){
					foundations_[i+x][j+y] = 6;
				} else if (i == width -1 && j == height - 1){
					foundations_[i+x][j+y] = 8;
				}
			}
		}
	}

	void WallGenerator::SetParameters(WallParameters params){
		parameters_ = params;
	}
}
