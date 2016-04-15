#include <iostream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "service/buffer_allocator.hpp"
#include "test/context_util.hpp"
#include "common/random.hpp"

namespace game{

	void GenerateRandomData(int, std::multimap<int, std::vector<float>>*,
													std::vector<unsigned int>*);

	const lest::test buffer_allocator[] = {

		SCENARIO("BufferAllocator should store data in OpenGL buffer"){

			GIVEN("an BufferAllocator and a valid OpenGL context"){
				ContextUtil::CreateOpenGLContext();
				BufferAllocator allocator;

				WHEN("a new array is registered"){
					int offset = -1;
					GLuint index = 0;
					std::multimap<int, std::vector<float>> data;
					std::vector<unsigned int> indices;

					index = allocator.RegisterData(data, indices, &offset);

					THEN("it should have allocated the data in a buffer"){
						EXPECT(index != 0);
						EXPECT(offset != -1);
					}
					THEN("it should not have produced openGL errors"){
						EXPECT(check_gl_error() == 0);
					}
				}
				WHEN("a huge amount of data is registered"){
					int offset = -1;
					GLuint index = 0;
					std::multimap<int, std::vector<float>> data;
					std::vector<unsigned int> indices;
					GenerateRandomData(2097152, &data, &indices);

					index = allocator.RegisterData(data, indices, &offset);

					THEN("it should have allocated the data in a buffer"){
						EXPECT(index != 0);
						EXPECT(offset != -1);
					}
					THEN("it should not have produced openGL errors"){
						EXPECT(check_gl_error() == 0);
					}
				}
				allocator.ClearMemory();
				ContextUtil::DestroyOpenGLContext();
			}
		}
	};

	void GenerateRandomData(int size,
													std::multimap<int, std::vector<float>>* data,
		 											std::vector<unsigned int>* indices){

		int element_count = size / sizeof(float);

		std::vector<float> vertexArray;
		for(int i = 0; i < element_count; i++){
			vertexArray.push_back(Random::NextInt(10));
		}
		data->insert(std::make_pair(VERTEX_ARRAY, vertexArray));

		for(int i = 0; i < element_count / 3; i++){
			indices->push_back(Random::NextInt(element_count-1));
		}
	}

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), buffer_allocator);
}
