#pragma once
#include <glad/glad.h>
#include <vector>
#include <iostream>
#include <assert.h>

enum class DataType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Mat3, Mat4,
	Int, Int2, Int3, Int4,
	Bool
};

static constexpr uint32_t DataTypeSize(DataType type)
{
	switch (type)
	{
		case DataType::Float:		return 4;
		case DataType::Float2:		return 4 * 2;
		case DataType::Float3:		return 4 * 3;
		case DataType::Float4:		return 4 * 4;
		case DataType::Mat3:		return 4 * 3 * 3;
		case DataType::Mat4:		return 4 * 4 * 4;
		case DataType::Int:			return 4;
		case DataType::Int2:		return 4 * 2;
		case DataType::Int3:		return 4 * 3;
		case DataType::Int4:		return 4 * 4;
		case DataType::Bool:		return 1;
		default: 
		{
			assert(false);
			return 0;
		}
	}
}

static constexpr GLenum ToGLType(DataType type)
{
	switch (type)
	{
		case DataType::Float:		return GL_FLOAT;
		case DataType::Float2:		return GL_FLOAT;
		case DataType::Float3:		return GL_FLOAT;
		case DataType::Float4:		return GL_FLOAT;
		case DataType::Mat3:		return GL_FLOAT;
		case DataType::Mat4:		return GL_FLOAT;
		case DataType::Int:			return GL_INT;
		case DataType::Int2:		return GL_INT;
		case DataType::Int3:		return GL_INT;
		case DataType::Int4:		return GL_INT;
		case DataType::Bool:		return GL_BOOL;
		default:
		{
			assert(false);
			return 0;
		}
	}
}

struct BufferElement
{
	std::string name;
	DataType type;
	uint32_t size;
	uint32_t offset;
	bool normalized;

	BufferElement(std::string name, DataType type)
		: name{ std::move(name) }, type{ type }, size{ DataTypeSize(type) }, offset{ 0 }, normalized{ false } {}

	uint32_t GetElementCount() const
	{
		switch (type)
		{
			case DataType::Float:			return 1;
			case DataType::Float2:			return 2;
			case DataType::Float3:			return 3;
			case DataType::Float4:			return 4;
			case DataType::Mat3:			return 3 * 3;
			case DataType::Mat4:			return 4 * 4;
			case DataType::Int:				return 1;
			case DataType::Int2:			return 2;
			case DataType::Int3:			return 3;
			case DataType::Int4:			return 4;
			case DataType::Bool:			return 1;
			default:
			{
				assert(false);
				return 0;
			}
		}
	}
};

class BufferLayout
{
public:
	BufferLayout(std::initializer_list<BufferElement> elements)
		: elements_{ elements }
	{
		CalculateOffsetAndStride();
	}
	
	constexpr uint32_t GetStride() const { return stride_; }
	constexpr const std::vector<BufferElement>& GetElements() const { return elements_; }

	std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
	std::vector<BufferElement>::iterator end() { return elements_.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }

private:
	void CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		stride_ = 0;
		for (auto& element : elements_)
		{
			element.offset = offset;
			offset += element.size;
			stride_ += element.size;
		}
	}

private:
	std::vector<BufferElement> elements_;
	uint32_t stride_ = 0;
};

class VertexBuffer
{
public:
	
	VertexBuffer(float* vertices, uint32_t size, BufferLayout layout)
		: layout_{layout}
	{
		glCreateBuffers(1, &id_);
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	~VertexBuffer()
	{
		glDeleteBuffers(1, &id_);
	}

	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id_);
	}
	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& GetLayout() const { return layout_; }

private:
	uint32_t id_;
	BufferLayout layout_;
};

class IndexBuffer
{
public:
	IndexBuffer(uint32_t* indicies, uint32_t count)
		: count_{count}
	{
		glCreateBuffers(1, &id_);
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	~IndexBuffer()
	{
		glDeleteBuffers(1, &id_);
	}

	void Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	}

	void Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

private:
	uint32_t id_;
	uint32_t count_;
};