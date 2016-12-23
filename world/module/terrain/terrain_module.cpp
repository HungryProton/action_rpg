#include "terrain_module.hpp"
#include "ecs/ecs.hpp"
#include "component/transform.hpp"
#include "component/graphic/mesh.hpp"
#include "component/graphic/drawable.hpp"
#include "component/collider.hpp"
#include "component/shapes/circle.hpp"
#include "common/logger.hpp"

namespace game{

	TerrainModule::TerrainModule() : random_(RealGenerator(0)){
		width_ = 35;
		height_ = 35;
		death_limit_ = 2;
		birth_limit_ = 4;
		chance_to_start_alive_ = 0.6f;
		chance_of_z_displacement_ = 0.2f;
		step_count_ = 4;
	}

	Terrain TerrainModule::Generate(double seed){
		random_ = RealGenerator(seed);
		Terrain terrain;

		std::vector<std::vector<bool>> map;

		for(int x = 0; x < width_; x++){
			map.push_back( std::vector<bool>() );
			terrain.map.push_back( std::vector<TerrainState>() );
			for(int y = 0; y < height_; y++){
				map[x].push_back(random_.Next(1.0f) >= chance_to_start_alive_);
				terrain.map[x].push_back(TerrainState::EMPTY);
			}
		}

		map = RunSimulation(step_count_, map);

		for(int x = 0; x < width_; x++){
			for(int y = 0; y < height_; y++){
				if(!map[x][y]){
					terrain.map[x][y] = TerrainState::BASE;
					terrain.blocks.push_back(CreateCell(x, y));
				}
			}
		}
		PlaceObstacles(terrain);
		return terrain;
	}

	std::vector<std::vector<bool>> TerrainModule::RunSimulation(int count, std::vector<std::vector<bool>> old_map){
		if(count <= 0){ return old_map; }
		std::vector<std::vector<bool>> new_map = old_map;

		for(unsigned int x = 0; x < old_map.size(); x++){
			for(unsigned int y = 0; y < old_map[0].size(); y++){
				int neighbors = CountAliveNeighbors(old_map, x, y);

				if(old_map[x][y]){
					new_map[x][y] = neighbors > death_limit_;
				} else {
					new_map[x][y] = neighbors > birth_limit_;
				}
			}
		}

		return RunSimulation(--count, new_map);
	}

	int TerrainModule::CountAliveNeighbors(std::vector<std::vector<bool>> map, int x, int y){
    int count = 0;
    for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				int neighbour_x = x+i;
				int neighbour_y = y+j;
				if(i == 0 && j == 0){ continue; }
				if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= width_ || neighbour_y >= height_){
						count = count + 1;
				}else if(map[neighbour_x][neighbour_y]){
						count = count + 1;
				}
			}
    }
		return count;
	}

	Entity TerrainModule::CreateCell(int x, int y){
		Entity cell = ecs::CreateEntity();
		float z = 0.f;
		if(chance_of_z_displacement_ > random_.Next(1.f)){
			z = -random_.Next(0.2f);
		}
		ecs::CreateComponent<Transform>(cell, glm::vec3((x*2)-(width_/2.f), (y*2)-(height_/2.f), z));
		ecs::CreateComponent<Mesh>(cell)->LoadFromFile("../data/environment/terrain/block/grass/grass_block_01.obj");
		ecs::CreateComponent<Drawable>(cell, DrawableType::MESH);

		return cell;
	}

	void TerrainModule::PlaceObstacles(Terrain terrain){
		// TODO : get this value from some sort of perlin map
		float chance_to_place_obstacle = 0.2f;

		for(int x = 0; x < width_; x++){
			for(int y = 0; y < height_; y++){
				if(terrain.map[x][y] == TerrainState::EMPTY){
					if(chance_to_place_obstacle > random_.Next(1.f)){
						terrain.obstacles.push_back(CreateRandomObstacle(x, y));
						terrain.map[x][y] = TerrainState::OCCUPIED;
					}
				}
			}
		}
	}

	Entity TerrainModule::CreateRandomObstacle(int x, int y){
		std::string path;
		float radius;
		switch((int)random_.Next(4.f)){
			case 0:
				path = "../data/environment/terrain/vegetation/bush.obj";
				radius = 0.2;
				break;
			case 1:
				path = "../data/environment/terrain/vegetation/tree.obj";
				radius = 0.2;
				break;
			case 2:
				path ="../data/environment/terrain/rock/rock_01.obj";
				radius = 1.1;
				break;
			case 3:
			default:
				path = "../data/environment/terrain/rock/rock_02.obj";
				radius = 1.1;
				break;
		}
		return CreateObstacle(path, radius, (x*2)-(width_/2), (y*2)-(height_/2));
	}

	Entity TerrainModule::CreateObstacle(std::string path, float radius, int x, int y){
		Entity obstacle = ecs::CreateEntity();
		//x += 0.25f - random_.Next(0.5f);
		//y += 0.25f - random_.Next(0.5f);
		ecs::CreateComponent<Transform>(obstacle, glm::vec3(x, y, 0));
		ecs::CreateComponent<Mesh>(obstacle)->LoadFromFile(path);
		Collider* c = ecs::CreateComponent<Collider>(obstacle);
		c->SetMass(0);
		c->shape_type = Shape::CIRCLE;
		ecs::CreateComponent<Circle>(obstacle)->radius = radius;
		ecs::CreateComponent<Drawable>(obstacle)->type = DrawableType::MESH;

		return obstacle;
	}
}
