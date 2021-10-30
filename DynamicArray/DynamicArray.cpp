#include <iostream>

#include "Array.h"


class A
{
public:

	int a;
	A()
	{
		a = 5;
	}
};

int main()
{
	Array<int> arr1;
	int a = 0;
	for (int i = 0; i < 32; i++)
	{
		arr1.Insert(++a);
	}
	arr1.Insert(7, ++a);
	for (auto it = arr1.iterator(); it.hasNext(); it.Next())
	{
		//it.Set(++a);
		std::cout << it.Get() << std::endl;
	}
	arr1.Remove(7);
	for (auto it = arr1.iterator(); it.hasNext(); it.Next())
	{
		it.Set(it.Get() * 2);
		std::cout << it.Get() << std::endl;
	}




	Array<std::string> arrs;
	for (int i = 0; i < 30; i++)
	{
		arrs.Insert("asdd"/*std::string(i+1, 'a')*/);
	}
	arrs.Insert("asdd");
	arrs[0] = "456123";
	for (auto it = arrs.iterator(); it.hasNext(); it.Next())
	{
		std::cout << it.Get() << std::endl;
	}
	std::cout << arrs.Size() << std::endl;





	Array<A> aarr;
	for (int i = 0; i < 8; i++)
	{
		A aa;
		aarr.Insert(aa);
	}
	A aa;
	aarr.Insert(aa);
	std::cout << aarr.Size() << std::endl;
	for (auto it = aarr.iterator(); it.hasNext(); it.Next())
	{
		std::cout << it.Get().a << std::endl;
	} 
}