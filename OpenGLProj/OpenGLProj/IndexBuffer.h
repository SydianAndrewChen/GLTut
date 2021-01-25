#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int count; // Used when invoking glDrawElements;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getCount() const {return count;}
};

#endif
