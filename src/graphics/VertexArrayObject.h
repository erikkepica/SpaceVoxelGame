#pragma once
#include<glad/glad.h>
#include<vector>

#include"Logging.h"

class VertexBufferElement
{
public:
	unsigned int count;
	unsigned int type;
	bool normalized;
	unsigned int offset;

	static unsigned int GetSize(unsigned int type);
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;
public:
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(sizeof(T) == 0, "VERTEX BUFFER LAYOUT: unsupported type. Provide explicit specialization for Push<T>.");
	}

	void SetAttributes();
};


class VAO
{
private:
	unsigned int m_ID;
	VertexBufferLayout m_Attribs;
public:
	VAO();

	void DoAttribs(VertexBufferLayout attribs);

	~VAO();

	void Generate();

	void Bind();

	static void Unbind();
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
	m_Elements.push_back({ count, GL_FLOAT, GL_FALSE, m_Stride });
	m_Stride += count * VertexBufferElement::GetSize(GL_FLOAT);
}

