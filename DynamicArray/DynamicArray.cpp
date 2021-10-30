#include <iostream>

template <typename T>
class Array final
{
private:
	int capacity_ = 8;
	int last_el_index_ = -1;
	int size_ = 0;
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

	Array(const Array& obj)
	{
		capacity_ = obj.capacity_;
		last_el_index_ = obj.last_el_index_;
		size_ = obj.size_;
		arr_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
		for (int i = 0; i < capacity_; i++)
		{
			arr_[i] = obj.arr_[i];
		}
	}

	Array(Array&& obj) noexcept
	{
		capacity_ = obj.capacity_;
		last_el_index_ = obj.last_el_index_;
		size_ = obj.size_;
		arr_ = obj.arr_;

		obj.capacity_ = 0;
		obj.last_el_index_ = 0;;
		obj.size_ = 0;
		obj.arr_ = nullptr;
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

	int Insert(const T& value)
	{
		if (last_el_index_ == capacity_ - 1)
		{
			Resize(true, last_el_index_ + 1);
		}
		arr_[++last_el_index_] = value;
		size_++;
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
		size_++;
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
		size_--;
	}

	T& operator[](int index)
	{
		return arr_[index];
	}

	int Size() const
	{
		return size_;
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
	Array<int> tmpar;
	tmpar[0] = 1;
	tmpar[1] = 2;
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << tmpar[i] << std::endl;
	}



	Array<int> arr1;
	int a = 0;
	arr1.Insert(++a);
	arr1.Insert(++a);
	arr1.Insert(++a);
	arr1.Insert(++a);
	arr1.Insert(++a);
	arr1.Insert(7, ++a);
	arr1.Remove(4);
	for (auto it = arr1.iterator(); it.hasNext(); it.Next())
	{
		it.Set(a);
		std::cout << it.Get() << std::endl;
	}

	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << arr1[i] << std::endl;
	}

	Array<int> arr2 = arr1;
	arr2[0] = 5;
	arr2[1] = 5;
	arr2[2] = 5;
	arr2[3] = 5;
	arr2[4] = 5;
	std::cout << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << arr1[i] << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << arr2[i] << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	arr1.~Array();
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << arr1[i] << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << ": " << arr2[i] << std::endl;
	}
	 
	Array<int> adsdd = std::move(arr2);
	arr2.~Array(); 
}