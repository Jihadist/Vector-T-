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
	Vector(std::initializer_list<T> s) :
		elements(nullptr), first_free(nullptr), cap(nullptr)
	{
		for (auto& i : s)
		{
			chk_n_alloc();
			alloc.construct(first_free++, i);
		}
	}
	Vector(const Vector& s)
	{
		auto newdata = alloc_n_copy(s.begin(), s.end());
		elements = newdata.first;
		first_free = cap = newdata.second;
	}
	Vector& operator=(const Vector& rhs)
	{
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = cap = data.second;
		return *this;
	}
	~Vector() {
		free();
	}
	void push_back(const T& s)
	{
		chk_n_alloc();
		alloc.construct(first_free++, s);
	}
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
	std::pair<T*, T*> alloc_n_copy(const T* b, const T* e)
	{
		auto data = alloc.allocate(b - e);
		return { data,uninitialized_copy(b,e,data) };
	}
	void free()
	{
		if (elements)
		{
			for (auto p = first_free; p != elements; )
				alloc.destroy(--p);
			alloc.deallocate(elements, cap - elements);
		}
	}
	void reallocate()
	{
		auto newcapacity = size() ? 2 * size() : 1;
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}

	T* elements;
	T* first_free;
	T* cap;
};


// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
