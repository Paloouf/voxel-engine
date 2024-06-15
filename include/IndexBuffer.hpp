#pragma once
#include "main.hpp"

class IndexBuffer {
	private:
		GLuint ibo;
		unsigned int m_count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();
		void Bind() const;
		void Unbind() const;
		unsigned int GetCount() const;
};