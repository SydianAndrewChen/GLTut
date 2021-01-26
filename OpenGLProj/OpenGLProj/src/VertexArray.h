#pragma once

#include "VertexBuffer.h"
class VertexBufferLayout;
class VertexArray
{
private:
	unsigned int rendererID;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind();
	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

