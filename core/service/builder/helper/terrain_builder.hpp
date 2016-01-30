#ifndef CORE_SERVICE_TERRAIN_BUILDER_HPP
#define CORE_SERVICE_TERRAIN_BUILDER_HPP

#include "tools/opengl.hpp"
#include "core/entity/game_object.hpp"

namespace game{

	class TerrainBuilder{
		public:
			TerrainBuilder();
			~TerrainBuilder();

			void ClearMemory();
			GameObject* GenerateTerrain();

			void SetMapSize(float, float);
			void SetMaxAltitudeVariation(float);
			void SetLayersCount(int);
			void SetResolution(int);

		private:
			glm::vec2 size_;
			float max_altitude_variation_;
			float layers_count_;
			int resolution_;

			// Generate the top surface
			void GeneratePolygon(std::multimap<int, std::vector<float>>*, std::vector<unsigned int>*);

			// Generate the border of the polygon
			std::vector<float> GenerateOutline();

			// Apply the midpoint displacement algorithm on an outiline
			std::vector<float> MidpointDisplacement(std::vector<float>, float);

			// return the index array needed to fill the outline with solid triangles
			std::vector<unsigned int> FillOutline(std::vector<float>);

			// Adds thickness to a polygon
			std::vector<float> ExtrudePolygon(std::vector<float>, float);
	};
}
#endif //CORE_SERVICE_TERRAIN_BUILDER_HPP

