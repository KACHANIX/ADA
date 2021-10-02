#include <iostream>
#include "Sorts.h"


int main()
{
	const int arr_len = 6;
	int a[arr_len] = { 5,16,4,3,5,10 };
	//int a[4] = { 3,4, 2, 1 };

	//const int arr_len = 1;
	//int a[arr_len] = { 10 };
	QSort(a, a + arr_len - 1, [](int a, int b) { return a < b; });

	for (const auto& e : a)
	{
		std::cout << e << " ";
	}

	//std::cout << *a << "	" << *(a + 9);
	std::cout << "Hello World!\n";
}
