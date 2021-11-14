#include <iostream>

//#include "Array.h"
#include "DynamicArray.h"

class A
{
public:

	int a_;
	A()
	{
		a_ = 5;
	}
	A(int asd)
	{
		a_ = asd;
	}
	~A()
	{
		std::cout << 'a';
	}
	A(A&&) = delete;
	A(const A&) = default;
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
	copied[0] = 456;
	std::cout << std::endl << std::endl;
	std::cout << arr[1] << " - " << copied[0];

	// Check move constructor
	Array<int> moved = std::move(copied);


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


	// Check A
	std::cout << std::endl;

	Array<A> A_arr;
	A a1(1);
	A a2(2);
	A_arr.Insert(a1);
	A_arr.Insert(0, a2);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	A_arr.Insert(a1);
	for (auto iterator = A_arr.iterator(); iterator.hasNext(); iterator.next())
	{
		std::cout << iterator.get().a_ << std::endl;
	}

	bool atmp = std::is_move_constructible_v<A>;
	bool atmp1 = std::is_copy_constructible_v<A>;
}