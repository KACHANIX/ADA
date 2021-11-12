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

	Array<int> copied = arr;
	copied.Remove(0);
	std::cout << std::endl << std::endl;
	std::cout << arr[0] << " - " << copied[0];

	int dsa = 5;
	//Array<int> arr1;
	//int a = 0;
	//for (int i = 0; i < 32; i++)
	//{
	//	arr1.Insert(++a);
	//}
	//arr1.Insert(7, ++a);
	//for (auto it = arr1.iterator(); it.hasNext(); it.Next())
	//{
	//	//it.Set(++a);
	//	std::cout << it.Get() << std::endl;
	//}
	//arr1.Remove(7);
	//for (auto it = arr1.iterator(); it.hasNext(); it.Next())
	//{
	//	it.Set(it.Get() * 2);
	//	std::cout << it.Get() << std::endl;
	//}



	//Array<std::string> arrs;
	//for (int i = 0; i < 30; i++)
	//{
	//	arrs.Insert("asdd"/*std::string(i+1, 'a')*/);
	//}
	//arrs.Insert("asdd");
	//arrs[0] = "456123";
	//for (auto it = arrs.iterator(); it.hasNext(); it.Next())
	//{
	//	std::cout << it.Get() << std::endl;
	//}
	//std::cout << arrs.Size() << std::endl;



	//Array<A> aarr;
	//for (int i = 0; i < 8; i++)
	//{
	//	A aa;
	//	aarr.Insert(aa);
	//}
	//A aa;
	//aarr.Insert(aa);
	//std::cout << aarr.Size() << std::endl;
	//for (auto it = aarr.iterator(); it.hasNext(); it.Next())
	//{
	//	std::cout << it.Get().a << std::endl;
	//} 
}