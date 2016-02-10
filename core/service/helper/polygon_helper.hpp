#ifndef GAME_CORE_SERVICE_HELPER_POLYGON_HPP
#define GAME_CORE_SERVICE_HELPER_POLYGON_HPP

#include <vector>
#include <map>
#include "core/service/service.hpp"
#include "core/component/common.hpp"
#include "tools/opengl.hpp"

namespace game{

	struct Polygon{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

	class PolygonHelper : public Service{
		public:
			PolygonHelper();
			~PolygonHelper();

			virtual void ClearMemory();

			// Convertion methods
			std::vector<Vertex> FloatArrayToVertices(std::vector<float>);
			Polygon FloatArrayToSinglePolygon(std::vector<float>);
			Polygon VertexArrayToPolygon(std::vector<Vertex>);
			void SinglePolygonToGLData(Polygon, std::multimap<int, std::vector<float>>*, std::vector<unsigned int>*);
			void PolygonsToGLData(std::vector<Polygon>, std::multimap<int, std::vector<float>>*, std::vector<unsigned int>*);

			// Utility methods
			std::vector<Polygon> ExtrudePolygon(Polygon);
			void SetTextureCoordModifier(float);

		private:
			void UpdateTextureCoordinates(std::vector<Vertex>*);
			std::vector<unsigned int> Triangulate(std::vector<Vertex>);
			bool IsCounterClockwise(Vertex, Vertex, Vertex);
			bool IsTriangleConvex(Vertex, Vertex, Vertex);
			bool IsPointWithinTriangle(Vertex, Vertex, Vertex, Vertex);
			std::vector<float> PositionToFloatArray(std::vector<Vertex>);
			std::vector<float> TextureToFloatArray(std::vector<Vertex>);
			bool IsCollectionValid(std::vector<Vertex>);

			float texture_modifier_;
	};
}

#endif //GAME_CORE_SERVICE_HELPER_POLYGON_HPP
