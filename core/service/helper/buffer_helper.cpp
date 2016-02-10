#include <iostream>
#include "buffer_helper.hpp"

namespace game{

	BufferHelper::BufferHelper(){
		this->vertex_buffers.clear();
		this->vbo_last_binded = -1;
		this->vbo_last_position = 0;

		this->index_buffers.clear();
		this->ibo_last_binded = -1;
		this->ibo_last_position = 0;
	}

	BufferHelper::~BufferHelper(){
		this->ClearMemory();
	}

	void BufferHelper::ClearMemory(){
		int len = vertex_buffers.size();
		for(int i = 0; i<len; i++){
			glDeleteBuffers(1, &vertex_buffers[i]);
		}
		vertex_buffers.clear();
		this->vbo_last_binded = -1;
		this->vbo_last_position = 0;

		len = index_buffers.size();
		for(int i = 0; i<len; i++){
			glDeleteBuffers(1, &index_buffers[i]);
		}
		index_buffers.clear();
		this->ibo_last_binded = -1;
		this->ibo_last_position = 0;
	}


	GLuint BufferHelper::RegisterData(std::multimap<int, std::vector<float> > data, std::vector<unsigned int> indices, int* offset){
		GLuint vertexArray = CreateAndBindVertexArray();
		int data_total_size = CountDataToRegister(data)*sizeof(float);

		// Bind a buffer large enough to hold the data
		BindBuffer(GL_ARRAY_BUFFER, data_total_size);

		for(auto it = data.begin(); it != data.end(); it++){
			int type = it->first;
			std::vector<float> d = it->second;
			int d_size = d.size()*sizeof(float);

			// Fills the buffer
			glBufferSubData(GL_ARRAY_BUFFER, vbo_last_position % MAX_BUFFER_SIZE,
							d_size, &d[0]);

			glEnableVertexAttribArray(type);
			glVertexAttribPointer(type,
									GetElementSize(type),
									GL_FLOAT,
									GL_FALSE,
									0,
									BUFFER_OFFSET(vbo_last_position));

			vbo_last_position += d_size;
		}

		FillIndexBuffer(indices, offset);

		glBindVertexArray(0);

		return vertexArray;
	}

	// ---------------------------------------------------------------
	// --- Utility methods
	// -------------------------------------------------------------

	GLuint BufferHelper::CreateAndBindVertexArray(){
		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		return vertexArray;
	}

	void BufferHelper::BindBuffer(GLuint type, int data_size){
		unsigned int* last_position;
		unsigned int* last_binded;
		std::vector<GLuint>* buffers;

		if(type == GL_ARRAY_BUFFER){
			last_position = &vbo_last_position;
			last_binded = &vbo_last_binded;
			buffers = &vertex_buffers;

		} else if (type == GL_ELEMENT_ARRAY_BUFFER) {
			last_position = &ibo_last_position;
			last_binded = &ibo_last_binded;
			buffers = &index_buffers;

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

			std::cout << "New buffer created with ID " << buffers->back() << std::endl;
		}else if( *last_binded != buffers->back() ){
			glBindBuffer(type, buffers->back());
		}
	}

	int BufferHelper::CountDataToRegister(std::multimap<int, std::vector<float> > data){
		// Get total data amount we will register
		int data_total_size = 0;
		for(auto it = data.begin(); it != data.end(); it++){
			data_total_size += it->second.size();
		}
		return data_total_size;
	}

	int BufferHelper::GetElementSize(int type){
		switch(type){
			case VERTEX_ARRAY:
				return 3;
			case COLOR_ARRAY:
				return 3;
			case TEXTURE_COORDS:
				return 2;
			case INDEX_ARRAY:
				return 3;
			case NORMAL_ARRAY:
				return 3;
		}
		return 0;
	}

	void BufferHelper::FillIndexBuffer(std::vector<unsigned int> indices, int* offset){

		int size = indices.size()*sizeof(unsigned int);

		BindBuffer(GL_ELEMENT_ARRAY_BUFFER, size);

		*offset = ibo_last_position;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, ibo_last_position % MAX_BUFFER_SIZE,
						size, &indices[0]);
		ibo_last_position += size;
	}

	std::vector<unsigned int> BufferHelper::VectorFloatToUnsignedInt(std::vector<float> array){
		std::vector<unsigned int> result;
		for(auto it = array.begin(); it != array.end(); it++){
			result.push_back( (unsigned int)(*it) );
		}
		return result;
	}
}








