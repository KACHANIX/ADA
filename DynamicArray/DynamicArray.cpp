#include <iostream>

template <typename T>
class Array final
{
private:
	int capacity_;
	int last_el_index_;
	T* arr_;
public:
	class Iterator
	{
	public:
		const T& Get() const
		{ // current value in array

		}

		void Set(const T& value)
		{ // set current value in array

		}

		void Next()
		{ // move to next element

		}

		bool hasNext() const
		{ // true if there is a next element

		}
	};

	Array()
	{
		capacity_ = 8;
		last_el_index_ = 0;
		arr_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
		for (int i = 0; i < capacity_; i++)
		{
			arr_[i] = NULL;
		}
	}

	Array(int capacity)
	{
		capacity_ = capacity;
		last_el_index_ = 0;
		arr_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
	}

	~Array()
	{

	}
	
	int Insert(T& value)
	{
		(arr_[last_el_index_++]) = value;
		return 1;
	}

	int Insert(int index, const T& value)
	{
		return 1;
	}

	void Remove(int index)
	{

	}

	T& operator[](int index)
	{
		return arr_[index]; 
	}

	int Size() const
	{

		return 1;
	}

	Iterator iterator()
	{

	}

	Iterator reverseIterator()
	{

	}
};

int main()
{
	Array<int> govno;

	{
		int a = 5;
		govno.Insert(a); a++;
		govno.Insert(a);
	}
	govno[2] = 3;
	 
	std::cout << govno[0] << std::endl;
	std::cout << govno[1] << std::endl;
	std::cout << govno[2] << std::endl;


}