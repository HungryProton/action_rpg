#ifndef GAME_CORE_BUFFER_HELPER_HPP
#define GAME_CORE_BUFFER_HELPER_HPP

#include <map>
#include <vector>
#include "tools/opengl.hpp"

namespace game{

    enum DataType{VERTEX_ARRAY, COLOR_ARRAY, TEXTURE_COORDS, INDEX_ARRAY};
    const int MAX_BUFFER_SIZE = 1048576;

    class BufferManager{
        public: 
            BufferManager();
            ~BufferManager();
            void ClearMemory();
            int GetCurrentLoad();
            GLuint Register(std::multimap<DataType, std::vector<float>>,
                            std::vector<unsigned int>, 
                            int*);

        private:
            // Helper methods
            GLuint CreateAndBindVertexArray();
            void BindBuffer(GLuint, int); 
            int CountDataToRegister(std::multimap<DataType, std::vector<float>>);
            void FillIndexBuffer(std::vector<unsigned int>, int*);
            int GetElementSize(DataType);

            // VBOs related attributes
            std::vector<GLuint> vertex_buffers_;
            unsigned int vbo_last_binded_;
            int vbo_last_position_;

            // IBO related attributes
            std::vector<GLuint> index_buffers_;
            unsigned int ibo_last_binded_;
            int ibo_last_position_;
    };
}

#endif //GAME_CORE_BUFFER_HELPER_HPP
