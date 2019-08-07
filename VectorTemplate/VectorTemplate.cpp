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
	Vector<int> numbers = { 1,2,3,4,5,6 };
	print(numbers);
	Vector<char> letters = { 'a','b','c' };
	print(letters);
	cout << "Hello CMake." << endl;
	return 0;
}