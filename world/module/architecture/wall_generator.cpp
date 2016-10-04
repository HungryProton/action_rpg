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

		if(width > 3 && height > 3){
			bool symetrical = random_.Next(0, 10) > 5 ? true : false;
			if(symetrical){
				int w = width/2;
				int h = height/2;
				SubstractSquare(0, 0, w, h);
				SubstractSquare(width-w, 0, w, h);
			} else {
				int w = random_.Next(std::max(2, width/4), std::max(3, width/2));
				int h = random_.Next(std::max(2, height/4), std::max(3, height/2));
				int corner = random_.Next(0, 4);
				int x = 0;
				int y = 0;
				switch(corner){
					case 1:
						x = width-w;
						break;
					case 2:
						y = height-h;
						break;
					case 3:
						x = width-w;
						y = height-h;
						break;
					case 0:
					default:
						break;
				}
				SubstractSquare(x, y, w, h);
			}
		}

		/*SubstractSquare(0, 0, 3, 3);
		SubstractSquare(width-3, 0, 3, 3);
		SubstractSquare(width-3, height-3, 3, 3);
		SubstractSquare(0, height-3, 3, 3); */

		Structure::Display2DVectorTranspose(&foundations_);

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
			case 1:	// Standard facing right
				return GetWall(x, y, 270, false, inner, false);
			case 2:	// Standard facing down
				return GetWall(x, y, 180, false, inner, false);
			case 3: // Standard facing up
				return GetWall(x, y, 0, false, inner, false);
			case 4: // Standard facing left
				return GetWall(x, y, 90, false, inner, false);
			case 5:	// Bottom left corner
				return GetWall(x, y, 270, true, inner, false);
			case 6: // corner
				return GetWall(x, y, 0, true, inner, false);
			case 7: // corner
				return GetWall(x, y, 180, true, inner, false);
			case 8: // corner
				return GetWall(x, y, 90, true, inner, false);
			case 9: // corner
				return GetWall(x, y, 0, true, inner, true);
			case 10: // reverse corner
				return GetWall(x, y, 90, true, inner, true);
			case 11: // bottom right reverse corner
				return GetWall(x, y, 180, true, inner, true);
			case 12: // Top right reverse corner
				return GetWall(x, y, 270, true, inner, true);
			default:
				return Wall();
		}
	}

	Wall WallGenerator::GetWall(int delta_x, int delta_y, int angle, bool corner, bool inner, bool reverse){
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
			if(reverse){
				name += "_corner2_A1.obj";
			} else {
				name += "_corner_A1.obj";
			}
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

	void WallGenerator::SubstractSquare(unsigned int x, unsigned int y, unsigned int width, unsigned int height){
		if(width == 0 || height == 0){ return; }
		if(width + x > foundations_.size()){ return; }
		if(height + y > foundations_[0].size()){ return; }

		for(unsigned int i = x; i < x+width; i++){
			for(unsigned int j = y; j < y+height; j++){
				// Handle corners

				// Bottom left
				if(j == y && i == x){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 10;
					} else if(foundations_[i][j] == 5){
						foundations_[i][j] = 0;
					} else if(foundations_[i][j] == 1) {
						foundations_[i][j] = 7;
					} else if(foundations_[i][j] == 3){
						foundations_[i][j] = 6;
					}
					continue;
				}

				// Top left
				if(j == (y+height) - 1 && i == x){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 9;
					} else if(foundations_[i][j] == 7){
						foundations_[i][j] = 0;
					} else if(foundations_[i][j] == 2) {
						foundations_[i][j] = 8;
					} else if(foundations_[i][j] == 1){
						foundations_[i][j] = 5;
					}
					continue;
				}

				// Bottom right corner
				if(j == y && i == x+width - 1){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 11;
					} else if(foundations_[i][j] == 6){
						foundations_[i][j] = 0;
					} else if(foundations_[i][j] == 3){
						foundations_[i][j] = 5;
					} else if(foundations_[i][j] == 4){
						foundations_[i][j] = 8;
					}
					continue;
				}

				// Top right
				if(j == y+height - 1 && i == x+width - 1){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 12;
					} else if(foundations_[i][j] == 8){
						foundations_[i][j] = 0;
					} else if(foundations_[i][j] == 2) {
						foundations_[i][j] = 7;
					} else if(foundations_[i][j] == 4) {
						foundations_[i][j] = 6;
					}
					continue;
				}

				//foundations_[i][j] = 0;
				//continue;

				if(j == y){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 2;
					} else {
						foundations_[i][j] = 0;
					}
				} else if (j == y+height - 1){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 3;
					} else {
						foundations_[i][j] = 0;
					}
				}

				if(i == x){
					if(foundations_[i][j] == 0){	// Left Border
						foundations_[i][j] = 4;
					} else {
						foundations_[i][j] = 0;
					}
				} else if(i == x+width - 1){
					if(foundations_[i][j] == 0){
						foundations_[i][j] = 1;
					} else {
						foundations_[i][j] = 0;
					}
				}
			}
		}
	}

	void WallGenerator::SetParameters(WallParameters params){
		parameters_ = params;
	}
}
