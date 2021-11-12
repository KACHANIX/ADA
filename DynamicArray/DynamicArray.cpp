#include <iostream>

//#include "Array.h"
#include "DynamicArray.h"

class A
{
public:

	int a;
	A()
	{
		a = 5;
	}
	~A()
	{
		std::cout << 'a';
	}
};

int main()
{
	Array<int> arr;
	int a = 0;
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Insert(++a);
	arr.Remove(2);

	for (auto iterator = arr.reversedIterator(); iterator.hasNext(); iterator.next())
	{
		std::cout << iterator.get() << std::endl;
	}
	std::cout << std::endl;
	for (auto iterator = arr.reversedIterator(); iterator.hasNext(); iterator.next())
	{
		iterator.set(iterator.get() * 2);
		std::cout << iterator.get() << std::endl;
	} 
	std::cout << arr[0] << std::endl;
	std::cout << arr[1] << std::endl;
	std::cout << arr[2] << std::endl;
	std::cout << arr[3] << std::endl;
	std::cout << arr[4] << std::endl;
	std::cout << arr[5] << std::endl;
	std::cout << arr[6] << std::endl;
	std::cout << arr[7] << std::endl;
	std::cout << arr[8] << std::endl;
	std::cout << arr[9] << std::endl;
	std::cout << arr[10] << std::endl;
	std::cout << arr[11] << std::endl;
	std::cout << std::endl << arr.size() << std::endl;


	// Check copy constructor
	Array<int> copied = arr;
	copied.Remove(0);
	std::cout << std::endl << std::endl;
	std::cout << arr[0] << " - " << copied[0];



	// Strings array
	std::cout << std::endl << std::endl << std::endl;
	Array<std::string> str_arr;
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	str_arr.Insert("a");
	for (auto iterator = str_arr.reversedIterator(); iterator.hasNext(); iterator.next())
	{
		std::cout << iterator.get() << std::endl;
	} 
}