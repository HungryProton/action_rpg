#include <algorithm>
#include "buffer_manager.hpp"
#include "tools/logger.hpp"

namespace game{

    BufferManager::BufferManager(){
        this->vertex_buffers_.clear();
        this->vbo_last_binded_ = -1;
        this->vbo_last_position_ = 0;

        this->index_buffers_.clear();
        this->ibo_last_binded_ = -1;
        this->ibo_last_position_ = 0;
    }

    BufferManager::~BufferManager(){

    }

    void BufferManager::ClearMemory(){
        int len = this->vertex_buffers_.size();
        for(int i = 0; i<len; i++){
            glDeleteBuffers(1, &vertex_buffers_[i]);
        }
        this->vertex_buffers_.clear();

        len = this->index_buffers_.size();
        for(int i = 0; i<len; i++){
            glDeleteBuffers(1, &index_buffers_[i]);
        }
        this->index_buffers_.clear(); 
    }

    GLuint BufferManager::Register(std::multimap<DataType, std::vector<float>> data,
                                  std::vector<unsigned int> indices,
                                  int* offset){
        if(!OpenGL::IsInitialized()){
            log(ERROR) << "Cannot register data for reason : No valid OpenGL context found." << std::endl;
        }
        
        GLuint vertexArray = CreateAndBindVertexArray();

            int data_total_size = CountDataToRegister(data)*sizeof(float);

            // Bind a buffer large enough to hold the data
            BindBuffer(GL_ARRAY_BUFFER, data_total_size);

            for(auto it = data.begin(); it != data.end(); it++){
                DataType type = it->first;
                std::vector<float> d = it->second;
                int d_size = d.size()*sizeof(float);

                // Fills the buffer
                glBufferSubData(GL_ARRAY_BUFFER, 
                                this->vbo_last_position_ % MAX_BUFFER_SIZE, 
                                d_size, &d[0]);

                glEnableVertexAttribArray(type);
                glVertexAttribPointer(type, 
                                      GetElementSize(type), 
                                      GL_FLOAT, 
                                      GL_FALSE, 
                                      0,
                                      BUFFER_OFFSET(this->vbo_last_position_));

                this->vbo_last_position_ += d_size;
            }

            FillIndexBuffer(indices, offset);

        glBindVertexArray(0);

        return vertexArray;
    }

    // ---------------------------------------------------------------
    // --- Utility methods
    // -------------------------------------------------------------

    GLuint BufferManager::CreateAndBindVertexArray(){
        GLuint vertexArray;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);
        return vertexArray;
    }

    void BufferManager::BindBuffer(GLuint type, int data_size){

        int* last_position;
        unsigned int* last_binded;
        std::vector<GLuint>* buffers;
        
        if(type == GL_ARRAY_BUFFER){
            last_position = &vbo_last_position_;
            last_binded = &vbo_last_binded_;
            buffers = &vertex_buffers_;

        } else if (type == GL_ELEMENT_ARRAY_BUFFER) {
            last_position = &ibo_last_position_;
            last_binded = &ibo_last_binded_;
            buffers = &index_buffers_;

        } else {
            return;
        }

        // Create a new Vertex buffer if the previous one don't
        // have enough space to store the new data.
        if( *last_position + data_size >= MAX_BUFFER_SIZE || *last_position == 0 ){
            
            GLuint buf;
            glGenBuffers(1, &buf);
            buffers->push_back(buf); 
            glBindBuffer(type, buffers->back());
            glBufferData(type, MAX_BUFFER_SIZE, NULL, GL_STREAM_DRAW);

            *last_position = (buffers->size()-1)*MAX_BUFFER_SIZE;

            log(INFO) << "New buffer created with ID " << buffers->back() << std::endl;
        }else if( *last_binded != buffers->back() ){
            glBindBuffer(type, buffers->back());
        }
    }

    int BufferManager::CountDataToRegister(std::multimap<DataType, std::vector<float> > data){
        // Get total data amount we will register
        int data_total_size = 0;
        for(auto it = data.begin(); it != data.end(); it++){
            data_total_size += it->second.size(); 
        }
        return data_total_size;
    }

    int BufferManager::GetElementSize(DataType type){
        switch(type){
            case VERTEX_ARRAY:
                return 3;
            case COLOR_ARRAY:
                return 3;
            case TEXTURE_COORDS:
                return 2;
            case INDEX_ARRAY:
                return -1; // TODO : Find the actual value supposed to be here
        }
        return 0;
    }

    void BufferManager::FillIndexBuffer(std::vector<unsigned int> indices, int* offset){

        int size = indices.size()*sizeof(unsigned int);

        BindBuffer(GL_ELEMENT_ARRAY_BUFFER, size);
        
        *offset = this->ibo_last_position_;

        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 
                        this->ibo_last_position_ % MAX_BUFFER_SIZE, 
                        size, &indices[0]);
        this->ibo_last_position_ += size;
    }

    int BufferManager::GetCurrentLoad(){
        int load = 0;

        int vbo_count = this->vertex_buffers_.size()-1;
        vbo_count = vbo_count > 0 ? vbo_count : 0;

        int ibo_count = this->index_buffers_.size()-1;
        ibo_count = ibo_count > 0 ? vbo_count : 0;

        load = vbo_count*MAX_BUFFER_SIZE*sizeof(float);
        load += vbo_last_position_;
        
        load += ibo_count*MAX_BUFFER_SIZE*sizeof(unsigned int);
        load += ibo_last_position_;

        return load;
    }

}
