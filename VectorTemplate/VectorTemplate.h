// VectorTemplate.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <memory>
template<typename T>
class Vector
{

public:
	Vector():elements(nullptr),first_free(nullptr),cap(nullptr){}
	Vector(std::initializer_list<T> s);
	Vector(const Vector&);
	Vector& operator=(const Vector&);
	~Vector();
	void push_back(const T&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }

	T* begin() const { return elements; }
	T* end() const { return first_free; }
private:
	std::allocator<T> alloc;
	void chk_n_alloc()
	{
		if(size()==capacity()) reallocate();
	}
	std::pair<T*, T*> alloc_n_copy (const T*, const T*);
	void free();
	void reallocate();
	T* elements;
	T* first_free;
	T* cap;
};


// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
