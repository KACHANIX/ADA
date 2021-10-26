#include <iostream>

template <typename T>
class Array final
{
private:
	int capacity_ = 8;
	int last_el_index_ = -1;
	int size = 0;
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
		arr_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
		for (int i = 0; i < capacity_; i++)
		{
			arr_[i] = NULL;
		}
	}

	Array(int capacity)
	{
		capacity_ = capacity;
		arr_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
		for (int i = 0; i < capacity_; i++)
		{
			arr_[i] = NULL;
		}
	}

	~Array()
	{
		FreeArray();
	}

	void FreeArray()
	{
		for (int i = 0; i < capacity_; i++)
		{
			arr_[i].~T();
			/*if (arr_[i] != NULL)
			{
				arr_[i].~T();
			}*/
		}
		free(arr_);
	}


	void Resize(bool is_upsize, int target_index)
	{
		int tmp_capacity;

		if (is_upsize)
		{
			tmp_capacity = capacity_ * 2;
			while (tmp_capacity - 1 < target_index)
			{
				tmp_capacity *= 2;
			}
		}
		else
		{
			tmp_capacity = capacity_ / 2;
		}

		T* tmp = static_cast<T*>(malloc(sizeof(T) * tmp_capacity));

		int border_index = is_upsize ? capacity_ : tmp_capacity;
		for (int i = 0; i < border_index; i++)
		{
			tmp[i] = arr_[i];
		}

		for (int i = border_index; i < tmp_capacity; i++)
		{
			tmp[i] = NULL;
		}

		FreeArray();
		arr_ = tmp;
		capacity_ = tmp_capacity;
	}

	int Insert(T& value)
	{
		if (last_el_index_ == capacity_ - 1)
		{
			Resize(true, last_el_index_ + 1);
		}
		arr_[++last_el_index_] = value;
		size++;
		return last_el_index_;
	}


	int Insert(int index, const T& value)
	{
		if (index < 0) return -1; // if index incorrect

		bool no_nulls_after_index = true;
		int first_null_index = 0;
		for (int i = index; i < capacity_; i++)
		{
			if (arr_[i] == NULL)
			{
				no_nulls_after_index = false;
				first_null_index = i;
				break;
			}
		}

		if (index > capacity_)
		{
			Resize(true, index); 
			first_null_index = index;
		}
		else if (no_nulls_after_index)
		{
			Resize(true, index);
			first_null_index = last_el_index_ + 1;
		}


		T previous_value = value;
		T tmp_value;
		for (int i = index; i <= first_null_index; i++)
		{
			tmp_value = arr_[i];
			arr_[i] = previous_value;
			previous_value = tmp_value;
		}
		last_el_index_ = first_null_index;
		//arr_[index] = value;
		size++;
		return index;
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
		return size;
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

	for (int i = 1; i < 15; i++)
	{
		govno.Insert(i);
	}
	int a = 228;
	govno.Insert(25, a);
	govno.Insert(20, ++a);
	govno.Insert(21, ++a);
	govno.Insert(22, ++a);
	govno.Insert(23, ++a);
	govno.Insert(24, ++a);
	govno.Insert(24, ++a);
	govno.Insert(++a);

	govno.Insert(27, ++a);


	for (int i = 0; i < 32; i++)
	{
		std::cout << i << ": " << govno[i] << std::endl;
	}
	 
	std::cout << govno.Size();

}