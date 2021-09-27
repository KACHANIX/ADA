#include "pch.h"
#include "../QuickSort/Sorts.h"

TEST(CorrectSorting, ArrayOfEvenSize)
{
	const int arr_len = 30;
	int a[arr_len] = { 9,8,7,6,1,2,3,4,5,11,13,15,17,19,12,14,16,20,18,23,21,25,29,27,22,24,26,28,30,10 };
	auto comp = [](int a, int b) { return a < b; };
	QSort(a, a + arr_len - 1, comp);
	bool is_array_sorted = true;
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (!comp(a[i], a[i + 1]))
			is_array_sorted = false;
	}
	ASSERT_EQ(true, is_array_sorted);
}

TEST(CorrectSorting, ArrayOfOddSize)
{
	const int arr_len = 29;
	int a[arr_len] = { 9,8,7,6,1,2,3,4,5,11,13,15,17,19,12,14,16,20,18,23,21,25,29,27,22,24,26,28,10 };
	auto comp = [](int a, int b) { return a > b; };
	QSort(a, a + arr_len - 1, comp);
	bool is_array_sorted = true;
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (!comp(a[i], a[i + 1]))
			is_array_sorted = false;
	}
	ASSERT_EQ(true, is_array_sorted);
}


TEST(CorrectSorting, ArrayOfNegatives)
{
	const int arr_len = 30;
	int a[arr_len] = { 0,-9,-8,-7,-6,-1,-2,-3,-4,-5,-11,-13,-15,-17,-19,-12,-14,-16,-20,-18,-23,-21,-25,-29,-27,-22,-24,-26,-28,-10 };
	auto comp = [](int a, int b) { return a < b; };
	QSort(a, a + arr_len - 1, comp);
	bool is_array_sorted = true;
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (!comp(a[i], a[i + 1]))
			is_array_sorted = false;
	}
	ASSERT_EQ(true, is_array_sorted);
}

TEST(CorrectSorting, ArrayOfStrings)
{
	const int arr_len = 10;
	std::string a[arr_len] = { "22", "1", "333", "7777777", "88888888", "4444", "999999999", "55555", "1010101010", "666666" };
	auto comp = [](const std::string& a, const std::string& b) { return a.length() < b.length(); };
	QSort(a, a + arr_len - 1, comp);
	bool is_array_sorted = true;
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (!comp(a[i], a[i + 1]))
			is_array_sorted = false;
	}
	ASSERT_EQ(true, is_array_sorted);
}



TEST(CorrectAlgorithm, ArrayOf1)
{ // check that algorithm won't crash on a single-element array
	const int arr_len = 1;
	int a[arr_len] = { 9 };
	auto comp = [](int a, int b) { return a < b; };
	EXPECT_NO_THROW({ QSort(a, a + arr_len - 1, comp); });
}


TEST(CorrectAlgorithm, ArrayOf2)
{ // check that so called "insertion sort" on 2 elements  work properly
	const int arr_len = 2;
	int a[arr_len] = { 9,0 };
	auto comp = [](int a, int b) { return a < b; };
	QSort(a, a + arr_len - 1, comp);
	bool is_array_sorted = true;
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (!comp(a[i], a[i + 1]))
			is_array_sorted = false;
	}
	ASSERT_EQ(true, is_array_sorted);
}

TEST(CorrectAlgorithm, ArrayOf3)
{ // check StartSort work properly
	const int arr_len = 3;
	int a[arr_len] = { 9,0 , -1 };
	auto comp = [](int a, int b) { return a < b; };
	QSort(a, a + arr_len - 1, comp);
	bool is_array_sorted = true;
	for (int i = 0; i < arr_len - 1; i++)
	{
		if (!comp(a[i], a[i + 1]))
			is_array_sorted = false;
	}
	ASSERT_EQ(true, is_array_sorted);
}
