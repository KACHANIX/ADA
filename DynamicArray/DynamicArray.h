#pragma once
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <type_traits>

template <typename T>
class Array final
{

private:
	int capacity_;
	int size_;
	T* arr_;
public:
	Array() :Array(8) {}

	Array(int capacity) :capacity_(capacity)
	{
		assert(capacity > 0 && "Capacity has to be a natural number");
		arr_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
		size_ = 0;
	}

	// Desctructor
	~Array()
	{
		FreeArray();
	}

	// Free memory
	void FreeArray()
	{
		for (int i = 0; i < size_; i++)
		{
			arr_[i].~T();
		}
		//size_ = 0;
		//capacity_ = 0;
		free(arr_);
	}

	// Copy constructor
	Array(const Array& arr) : Array(arr.capacity_)
	{
		for (int i = 0; i < arr.size_; i++)
		{
			new (arr_ + i) T((arr[i])); // ref
			size_++;
		}
	}

	// Move constructor
	Array(Array&& arr) : Array(arr.capacity_)
	{
		if (std::is_move_constructible_v<T>)
		{
			for (int i = 0; i < arr.size_; i++)
			{
				new (arr_ + i) T(std::move(arr[i]));
				size_++;
			}
		}
		else
		{
			for (int i = 0; i < arr.size_; i++)
			{
				new (arr_ + i) T(std::ref(arr[i])); // ref
				size_++;
			}
		}
		arr.FreeArray();
	}

	// Upsize twice
	void Upsize()
	{
		capacity_ *= 2;
		T* tmp = static_cast<T*>(malloc(sizeof(T) * capacity_));

		if (std::is_move_constructible_v<T>)
		{
			for (int i = 0; i < size_; i++)
			{
				new (tmp + i) T(std::move(arr_[i]));
			}
		}
		else
		{
			for (int i = 0; i < size_; i++)
			{
				new (tmp + i) T(std::ref(arr_[i])); // ref
			}
		}
		FreeArray();
		arr_ = tmp;
	}

	// Insert after last
	int Insert(const T& value)
	{
		if (size_ == capacity_)
		{
			Upsize();
		}
		new (arr_ + size_) T(value);
		size_++;
		return size_ - 1;
	}

	// Insert in indexed position and move right
	int Insert(int index, const T& value)
	{
		if (index > size_ || index < 0)
		{
			throw std::out_of_range("Target index is outside of existing elements");
		}

		if (size_ == capacity_)
		{
			Upsize();
		}

		if (std::is_move_constructible_v<T>)
		{
			for (int i = size_; i > index; i--)
			{
				new (arr_ + i) T(std::move(arr_[i - 1]));
				arr_[i - 1].~T();
			}
		}
		else
		{
			for (int i = size_; i > index; i--)
			{
				new (arr_ + i) T(std::ref(arr_[i - 1])); // ref
				arr_[i - 1].~T();
			}
		}
		new(arr_ + index) T(value);
		size_++;
		return index;
	}

	// Remove from indexed position
	void Remove(int index)
	{
		if (index > size_ || index < 0)
		{
			throw std::out_of_range("Target index is outside of existing elements");
		}

		arr_[index].~T();
		auto asd = arr_[index];
		if (std::is_move_constructible_v<T>)
		{
			for (int i = index; i < size_ - 1; i++)
			{
				new (arr_ + i) T(std::move(arr_[i + 1]));
				arr_[i + 1].~T();
			}
		}
		else
		{
			for (int i = index; i < size_ - 1; i++)
			{
				new (arr_ + i) T(std::ref(arr_[i + 1]));
				arr_[i + 1].~T();
			}
		}

		size_--;
	}


	T& operator[](int index)
	{
		return arr_[index];
	}

	const T& operator[](int index) const
	{
		return arr_[index];
	}

	int size() const
	{
		return size_;
	}

	//////// ITERATORS

	class Iterator
	{
	private:
		Array<T>* parent_;
		int current_index_;
		bool is_forward_;
		bool is_last_;
	public:
		Iterator(Array<T>* parent, bool is_forward)
		{
			parent_ = parent;
			is_forward_ = is_forward;
			is_last_ = parent_->size_ > 0 ? false : true;
			if (is_forward_)
			{
				current_index_ = 0;
			}
			else
			{
				current_index_ = parent->size_ - 1;
			}
		}
		const T& get() const
		{
			return parent_->arr_[current_index_];
		}

		void set(const T& value)
		{
			parent_->arr_[current_index_] = value;
		}

		void next()
		{
			if (is_last_)
				return;

			if (is_forward_)
			{
				current_index_++;
				if (current_index_ == parent_->size_)
					is_last_ = true;
			}
			else
			{
				current_index_--;
				if (current_index_ ==-1)
					is_last_ = true;
			}
		}

		bool hasNext() const
		{
			return !is_last_;
		}
	};

	class ConstIterator
	{
	private:
		Array<T>* parent_;
		int current_index_;
		bool is_forward_;
		bool is_last_;
	public:
		ConstIterator(Array<T>* parent, bool is_forward)
		{
			parent_ = parent;
			is_forward_ = is_forward;
			is_last_ = parent_->size_ > 0 ? false : true;
			if (is_forward_)
			{
				current_index_ = 0;
			}
			else
			{
				current_index_ = parent->size_ - 1;
			}
		}
		const T& get() const
		{
			return parent_->arr_[current_index_];
		}

		void next()
		{
			if (is_last_)
				return;

			if (is_forward_)
			{
				current_index_++;
				if (current_index_ == parent_->size_)
					is_last_ = true;
			}
			else
			{
				current_index_--;
				if (current_index_ == 0)
					is_last_ = true;
			}
		}

		bool hasNext() const
		{
			return is_last_;
		}
	};

	Iterator iterator()
	{
		Iterator iterator(this, true);
		return iterator;
	}

	const ConstIterator iterator() const
	{
		ConstIterator iterator(this, true);
		return iterator;
	}

	Iterator reversedIterator()
	{
		Iterator iterator(this, false);
		return iterator;
	}
	const ConstIterator reversedIterator() const
	{
		ConstIterator iterator(this, false);
		return iterator;
	}
};
