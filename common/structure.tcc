#include "structure.hpp"
#include "common/logger.hpp"

namespace game{

	template<class T>
	void Structure::Fill2DVector(std::vector<std::vector<T>>* vector, int width, int height, T value){
		vector->clear();
		for(int i = 0; i < width; i++){
			std::vector<T> column;
			for(int j = 0; j < height; j++){
				column.push_back(value);
			}
			vector->push_back(column);
		}
	}

	template<class T>
	void Structure::Display2DVector(std::vector<std::vector<T>> *vector){
		for(auto first_dimension : *vector){
			for(auto element : first_dimension){
				std::cout << element << " ";
			}
			std::cout << std::endl;
		}
	}
}
