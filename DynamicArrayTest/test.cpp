#include "pch.h"
#include "../DynamicArray/Array.h"

TEST(CorrectPlacement, SimpleInsertion) {
	Array<int> arr;
	int intarr[] = { 0,1,2,3,4,5,6,7 };
	for (int& i : intarr)
	{
		arr.Insert(i);
	}

	for (int i = 0; i < 8; i++)
	{
		ASSERT_EQ(intarr[i], arr[i]);
	}
}
TEST(CorrectPlacement, InsertionByIndex)
{
	Array<int> arr;
	for (int i = 0; i < 8; ++i)
	{
		arr.Insert(0, 8 - i);
	}


	int test_var = arr[0];
	for (auto it = arr.iterator(); it.hasNext(); it.Next())
	{
		ASSERT_LE(test_var, it.Get());
		test_var = it.Get();
	}
}

TEST(CorrectIterator, ForwardIterator)
{
	Array<int> arr;
	int a = 0;
	for (int i = 0; i < 8; i++)
	{
		arr.Insert(++a);
	}

	int test_var = 0;
	for (auto it = arr.iterator(); it.hasNext(); it.Next())
	{
		ASSERT_LT(test_var, it.Get());
		test_var = it.Get();
	}
}
TEST(CorrectIterator, ReverseIterator)
{
	Array<int> arr;
	int a = 0;
	for (int i = 0; i < 8; i++)
	{
		arr.Insert(++a);
	}

	int test_var = 9;
	for (auto it = arr.reverseIterator(); it.hasNext(); it.Next())
	{
		ASSERT_GT(test_var, it.Get());
		test_var = it.Get();
	}
}
TEST(CorrectIterator, SetThroughIterator)
{
	Array<int> arr;
	int a = 0;
	for (int i = 0; i < 8; i++)
	{
		arr.Insert(++a);
	}

	int set_six = 6;
	for (auto it = arr.iterator(); it.hasNext(); it.Next())
	{
		it.Set(set_six);
	}

	for (auto it = arr.iterator(); it.hasNext(); it.Next())
	{
		ASSERT_EQ(set_six, it.Get());
	}
}

TEST(CorrectResize, Upsize)
{
	int init_capacity = 8;
	Array<int> arr(init_capacity);
	int a = 0;
	for (int i = 0; i < init_capacity; i++)
	{
		arr.Insert(++a);
	}
	arr.Insert(++a);

	ASSERT_EQ(init_capacity + 1, arr.Size());
}

TEST(CorrectRemove, RemoveAffectSize)
{
	Array<int> arr;
	int a = 0;
	for (int i = 0; i < 8; i++)
	{
		arr.Insert(++a);
	}
	int old_size = arr.Size();
	arr.Remove(7);
	int new_size = arr.Size();

	ASSERT_NE(old_size, new_size);
}
TEST(CorrectRemove, RemoveExecutesMoveleft)
{
	Array<int> arr;
	int a = 0;
	for (int i = 0; i < 8; i++)
	{
		arr.Insert(++a);
	}
	arr.Remove(6);
	ASSERT_EQ(arr[6], 8);
}