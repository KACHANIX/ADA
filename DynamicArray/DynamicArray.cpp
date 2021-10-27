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
	private:
		int index = -1;
		bool is_forward_;
		Array<T>* parent_;
		bool last_element_ = false;
	public:
		Iterator(bool is_forward, Array<T>* parent)
		{
			parent_ = parent;
			is_forward_ = is_forward;
			if (is_forward)
			{
				for (int i = 0; i < parent_->capacity_; i++)
				{
					if (parent_->arr_[i] != NULL)
					{
						index = i;
						return;
					}
				}
			}
			else
			{
				for (int i = parent_->capacity_ - 1; i >= 0; --i)
				{
					if (parent_->arr_[i] != NULL)
					{
						index = i;
						return;
					}
				}
			}

		}

		const T& Get() const
		{ // current value in array
			if (index == -1)
			{
				return NULL;
			}
			return parent_->arr_[index];
		}

		void Set(const T& value)
		{ // set current value in array
			if (index == -1)
			{
				return;
			}
			parent_->arr_[index] = value;
		}

		void Next()
		{ // move to next element
			if (index == -1)
			{
				return;
			}
			if (is_forward_)
			{
				for (int i = index + 1; i < parent_->capacity_; i++)
				{
					if (parent_->arr_[i] != NULL)
					{
						index = i;
						return;
					}

				}
			}
			else
			{
				for (int i = index - 1; i >= 0; i--)
				{
					if (parent_->arr_[i] != NULL)
					{
						index = i;
						return;
					}
				}
			}
			last_element_ = true;
		}

		bool hasNext() const
		{ // true if there is a next element
			return !last_element_;
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
		if (index > last_el_index_ || index < 0 || arr_[index] == NULL)
		{
			return;
		}

		T previous_value = NULL;
		T tmp_value;
		for (int i = last_el_index_; i >= index; i--)
		{
			tmp_value = arr_[i];
			arr_[i] = previous_value;
			previous_value = tmp_value;
		}

		for (int i = last_el_index_ - 1; i >= 0; i--)
		{
			if (arr_[i] != NULL)
			{
				last_el_index_ = i;
				break;
			}
			if (i == 0 && arr_[i] == NULL)
			{
				last_el_index_ = -1;
			}
		}
		size--;
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
		return Iterator(true, this);
	}

	Iterator reverseIterator()
	{
		return Iterator(false, this);
	}
};


int main()
{
	Array<int> govno;
	int a = 0;
	govno.Insert(++a);
	govno.Insert(++a);
	govno.Insert(++a);
	govno.Insert(++a);
	govno.Insert(++a);
	govno.Insert(7, ++a);
	govno.Remove(4);


	for (auto it = govno.iterator(); it.hasNext(); it.Next())
	{
		it.Set(a);
		std::cout << it.Get() << std::endl;
	}


	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << govno[i] << std::endl;
	}

	int asd = 5;
	int* das = &asd;
	*das = 6;
	int** ddads = &das;
	**ddads = 7;
	 
	
	std::cout << "dermo";
	//Array<int> govno;
	//for (int i = 1; i < 15; i++)
	//{
	//	govno.Insert(i);
	//}
	//int a = 228;
	//govno.Insert(25, a);
	//govno.Insert(20, ++a);
	//govno.Insert(21, ++a);
	//govno.Insert(22, ++a);
	//govno.Insert(23, ++a);
	//govno.Insert(24, ++a);
	//govno.Insert(24, ++a);
	//govno.Insert(++a);
	//govno.Insert(27, ++a);
	//govno.Insert(127, ++a);
	//govno.Insert(++a);
	//for (int i = 0; i < 256; i++)
	//{
	//	std::cout << i << ": " << govno[i] << std::endl;
	//}
	//govno.Remove(20);
	//for (int i = 0; i < 256; i++)
	//{
	//	std::cout << i << ": " << govno[i] << std::endl;
	//}



}