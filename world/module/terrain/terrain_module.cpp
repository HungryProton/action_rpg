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

		FillCellData();
		FillCellItems();
	}

	// TODO : Read these data from files
	void TerrainModule::FillCellData(){
		CellData grass;
		grass.type = CellType::GRASS;
		grass.path = "../data/environment/terrain/block/grass/grass_block_01.obj";
		grass.probability = 0.4;

		CellData rock;
		rock.type = CellType::ROCK;
		rock.path = "../data/environment/terrain/block/rock/rock_block_01.obj";
		rock.probability = 0.35;

		CellData dirt;
		dirt.type = CellType::DIRT;
		dirt.path = "../data/environment/terrain/block/dirt/dirt_block_01.obj";
		dirt.probability = 0.25;

		cell_data_.push_back(grass);
		cell_data_.push_back(rock);
		cell_data_.push_back(dirt);
	}

	void TerrainModule::FillCellItems(){
		CellItem bush;
		bush.radius = 0.2;
		bush.path = "../data/environment/terrain/vegetation/bush.obj";
		bush.affinity.insert(std::make_pair(CellType::GRASS, 0.9f));
		bush.affinity.insert(std::make_pair(CellType::DIRT, 0.1f));
		bush.affinity.insert(std::make_pair(CellType::ROCK, 0.f));

		CellItem tree;
		tree.path = "../data/environment/terrain/vegetation/tree.obj";
		tree.radius = 0.2;
		tree.affinity.insert(std::make_pair(CellType::GRASS, 0.9f));
		tree.affinity.insert(std::make_pair(CellType::DIRT, 0.1f));
		tree.affinity.insert(std::make_pair(CellType::ROCK, 0.f));

		CellItem rock1;
		rock1.path = "../data/environment/terrain/rock/rock_01.obj";
		rock1.radius = 1.1;
		rock1.affinity.insert(std::make_pair(CellType::GRASS, 0.3f));
		rock1.affinity.insert(std::make_pair(CellType::DIRT, 0.3f));
		rock1.affinity.insert(std::make_pair(CellType::ROCK, 0.4f));

		CellItem rock2;
	  rock2.path = "../data/environment/terrain/rock/rock_02.obj";
		rock2.radius = 1.1;
		rock1.affinity.insert(std::make_pair(CellType::GRASS, 0.1f));
		rock1.affinity.insert(std::make_pair(CellType::DIRT, 0.2f));
		rock1.affinity.insert(std::make_pair(CellType::ROCK, 0.7f));

		cell_items_.push_back(bush);
		cell_items_.push_back(tree);
		cell_items_.push_back(rock1);
		cell_items_.push_back(rock2);
	}

	Terrain TerrainModule::Generate(double seed){
		random_ = RealGenerator(seed);
		FillInitialStates();
		RunSimulation(step_count_);

		Terrain terrain;
		for(int x = 0; x < width_; x++){
			terrain.map.push_back(std::vector<TerrainState>());
			for(int y = 0; y < height_; y++){
				if(!occupation_map_[x][y]){
					terrain.map[x].push_back(TerrainState::BASE);
					terrain.blocks.push_back(CreateCell(x, y));
				} else {
					terrain.map[x].push_back(TerrainState::EMPTY);
				}
			}
		}
		PlaceObstacles(terrain);
		return terrain;
	}

	void TerrainModule::FillInitialStates(){
		// Clear the maps from previous generations
		occupation_map_.clear();
		type_map_.clear();

		for(int x = 0; x < width_; x++){
			occupation_map_.push_back(std::vector<bool>());
			type_map_.push_back(std::vector<CellType>());
			for(int y = 0; y < height_; y++){
				occupation_map_[x].push_back(random_.Next(1.0f) >= chance_to_start_alive_);
				type_map_[x].push_back(GetRandomCellType());
			}
		}
	}

	CellType TerrainModule::GetRandomCellType(){
		float rand = random_.Next(1.f);
		for(CellData data : cell_data_){
			if(rand < data.probability){
				return data.type;
			}
			rand -= data.probability;
		}
		return cell_data_[0].type;
	}

	std::string TerrainModule::GetPathForCell(CellType cell){
		for(CellData data : cell_data_){
			if(data.type == cell){
				return data.path;
			}
		}
		return cell_data_[0].path;
	}

	void TerrainModule::RunSimulation(int count){
		if(count <= 0){ return; }
		std::vector<std::vector<bool>> new_map = occupation_map_;
		std::vector<std::vector<CellType>> new_type_map = type_map_;

		for(unsigned int x = 0; x < occupation_map_.size(); x++){
			for(unsigned int y = 0; y < occupation_map_[0].size(); y++){
				new_map[x][y] = OccupationStep(x, y);
				new_type_map[x][y] = TypeStep(x, y);
			}
		}
		occupation_map_ = new_map;
		type_map_ = new_type_map;
		RunSimulation(--count);
	}

	bool TerrainModule::OccupationStep(int x, int y){
		int neighbors = CountAliveNeighbors(x, y);

		if(occupation_map_[x][y]){
			return neighbors > death_limit_;
		} else {
			return neighbors > birth_limit_;
		}
	}

	CellType TerrainModule::TypeStep(int x, int y){
		CellType initial = type_map_[x][y];
		int grass_count = 0;
		int rock_count = 0;
		int dirt_count = 0;
    for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				int neighbour_x = x+i;
				int neighbour_y = y+j;
				if(i == 0 && j == 0){ continue; }
				if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= width_ || neighbour_y >= height_){
						continue;
				}
				switch(type_map_[neighbour_x][neighbour_y]){
					case CellType::GRASS:
						grass_count++;
						break;
					case CellType::ROCK:
						rock_count++;
						break;
					case CellType::DIRT:
						dirt_count++;
						break;
				}
			}
		}
		if(grass_count > rock_count && grass_count > dirt_count){
			return CellType::GRASS;
		}
		if(rock_count > grass_count && rock_count > dirt_count){
			return CellType::ROCK;
		}
		if(dirt_count > grass_count && dirt_count > rock_count){
			return CellType::DIRT;
		}
		return initial;
	}

	int TerrainModule::CountAliveNeighbors(int x, int y){
    int count = 0;
    for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				int neighbour_x = x+i;
				int neighbour_y = y+j;
				if(i == 0 && j == 0){ continue; }
				if(neighbour_x < 0 || neighbour_y < 0 || neighbour_x >= width_ || neighbour_y >= height_){
						count = count + 1;
				}else if(occupation_map_[neighbour_x][neighbour_y]){
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
		ecs::CreateComponent<Mesh>(cell)->LoadFromFile(GetPathForCell(type_map_[x][y]));
		ecs::CreateComponent<Drawable>(cell, DrawableType::MESH);
		return cell;
	}

	void TerrainModule::PlaceObstacles(Terrain terrain){
		// TODO : get this value from some sort of perlin map
		float chance_to_place_obstacle = 0.15f;

		for(int x = 0; x < width_; x++){
			for(int y = 0; y < height_; y++){
				if(terrain.map[x][y] != TerrainState::EMPTY){
					if(chance_to_place_obstacle > random_.Next(1.f)){
						terrain.obstacles.push_back(CreateRandomObstacle(x, y));
						terrain.map[x][y] = TerrainState::OCCUPIED;
					}
				}
			}
		}
	}

	Entity TerrainModule::CreateRandomObstacle(int x, int y){
		float rand = random_.Next(1.f);
		CellType current_cell = type_map_[x][y];

		while(1){
			for(CellItem item : cell_items_){
				LOG(DEBUG) << rand << std::endl;
				float affinity = item.affinity.find(current_cell)->second;
				if(affinity > rand){
					return CreateObstacle(item.path, item.radius, (x*2)-(width_/2), (y*2)-(height_/2));
				}
				rand -= affinity;
			}
		}
	}

	Entity TerrainModule::CreateObstacle(std::string path, float radius, int x, int y){
		Entity obstacle = ecs::CreateEntity();
		x += 0.25f - random_.Next(0.5f);
		y += 0.25f - random_.Next(0.5f);
		ecs::CreateComponent<Transform>(obstacle, glm::vec3(x, y, 0))->rotation.z = random_.Next(180);
		ecs::CreateComponent<Mesh>(obstacle)->LoadFromFile(path);
		Collider* c = ecs::CreateComponent<Collider>(obstacle);
		c->SetMass(0);
		c->shape_type = Shape::CIRCLE;
		ecs::CreateComponent<Circle>(obstacle)->radius = radius;
		ecs::CreateComponent<Drawable>(obstacle)->type = DrawableType::MESH;

		return obstacle;
	}
}
