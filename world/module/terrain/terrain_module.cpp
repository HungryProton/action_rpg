#include "terrain_module.hpp"
#include "ecs/ecs.hpp"
#include "component/transform.hpp"
#include "component/graphic/mesh.hpp"
#include "component/graphic/drawable.hpp"
#include "common/logger.hpp"

namespace game{

	TerrainModule::TerrainModule() : random_(RealGenerator(0)){
		width_ = 25;
		height_ = 25;
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
		LOG(DEBUG) << x << ", " << y << std::endl;
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
}
