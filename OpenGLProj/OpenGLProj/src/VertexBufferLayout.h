#pragma once
#include <vector>
#include <glad/glad.h>
#include "Renderer.h"

struct VertexBufferElement 
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type) 
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:   return 4;
			case GL_UNSIGNED_BYTE:  return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	template<typename T>
	void push(unsigned int count) 
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count) 
	{
		elements.push_back({ count, GL_FLOAT, GL_FALSE});
		stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count) 
	{
		elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE});
		stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return elements; };
	inline unsigned int GetStride() const { return stride; };
};

