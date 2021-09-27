#include <iostream>
#include "Sorts.h"


int main()
{
	const int arr_len = 29;
	int a[arr_len] = { 9,8,7,6,1,2,3,4,5 ,11,13,15,17,19,12,14,16,20,18,23,21,25,29,27,22,24,26,28,30 };
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
