#ifndef GAME_CORE_SERVICE_BUFFER_HELPER_HPP
#define GAME_CORE_SERVICE_BUFFER_HELPER_HPP

#include <map>
#include <vector>
#include "tools/opengl.hpp"
#include "core/service/service.hpp"

#define VERTEX_ARRAY 0
#define COLOR_ARRAY 1
#define TEXTURE_COORDS 2
#define INDEX_ARRAY 3

#define MAX_BUFFER_SIZE 1048576 // 1024 x 1024

#ifndef BUFFER_OFFSET
	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

namespace game{

    class BufferHelper : public Service{
        public:
            BufferHelper();
            ~BufferHelper();
            /**
             * @brief Register the given vertices to a VBO
             *
             *  Internally, multiple 1Mb VBOs are created to store geometry.
             *  When a VBO is full, another 1MB VBO is created.
             *
             * @param std::multimap<int, std::vector> the data to store.
             * the int represent the type (VERTEX or TEXTURE_COORD), the vector
             * contains the actual data.
             *
             * @return The vertex array object containing all the data.
             */
            GLuint RegisterData(std::multimap<int, std::vector<float>>, std::vector<unsigned int>, int*);

            void ClearMemory();

        private:
            void BindBuffer(GLuint, int);
            int CountDataToRegister(std::multimap<int, std::vector<float>>);
            int GetElementSize(int type);
            GLuint CreateAndBindVertexArray();
            void FillIndexBuffer(std::vector<unsigned int>, int*);
            std::vector<unsigned int> VectorFloatToUnsignedInt(std::vector<float>);

            // VBOs related attributes
            std::vector<GLuint> vertex_buffers;
            unsigned int vbo_last_binded;
            unsigned int vbo_last_position;

            // IBO related attributes
            std::vector<GLuint> index_buffers;
            unsigned int ibo_last_binded;
            unsigned int ibo_last_position;
    };
}

#endif //GAME_CORE_SERVICE_BUFFER_HELPER_HPP

