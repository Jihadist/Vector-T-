// VectorTemplate.cpp: определяет точку входа для приложения.
//

#include "VectorTemplate.h"

using namespace std;

template<typename T>
void print(T& arr)
{
	std::cout << "(" << typeid(T).name() << "):{";
	for (auto& i : arr)
		std::cout << "'" << i << "',";
	std::cout << "}" << std::endl;
}

int main()
{
	Vector<int> vec;
	vec.push_back(13);
	vec.push_back(1448);
	vec.push_back(15);
	print(vec);
	Vector<char> Str;
	Str.push_back('B');
	Str.push_back('A');
	Str.push_back('D');
	print(Str);
	cout << "Hello CMake." << endl;
	return 0;
}


template<typename T>
Vector<T>::Vector(const Vector& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::push_back(const T& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}



template<typename T>
std::pair<T*, T*> Vector<T>::alloc_n_copy(const T* b, const T* e)
{
	auto data = alloc.allocate(b - e);
	return { data,uninitialized_copy(b,e,data) };
}

template<typename T>
void Vector<T>::free()
{
	if(elements)
	{
		for (auto p = first_free; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

template<typename T>
void Vector<T>::reallocate()
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
