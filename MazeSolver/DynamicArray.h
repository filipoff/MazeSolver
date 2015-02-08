#pragma once
#define NULL 0
template <class T>

class DynamicArray
{
private:
	T* data;
	size_t size;
	size_t capacity;

private:

	void copyFrom(const DynamicArray& other)
	{
		data = new T[other.capacity];

		for (size_t i = 0; i < other.size; i++)
		{
			data[i] = other.data[i];
		}

		capacity = other.capacity;
		size = other.size;
	}

	void resize()
	{
		size_t newCapacity = (capacity != 0 ? capacity * 2 : 2);

		T* temp = new T[newCapacity];

		for (size_t i = 0; i < capacity; i++)
		{
			temp[i] = data[i];
		}

		delete[] data;
		data = temp;
		capacity = newCapacity;
	}

public:
	DynamicArray() : data(NULL), size(0), capacity(0) {}

	DynamicArray(const DynamicArray<T> &other)
	{
		copyFrom(other);
	}

	DynamicArray(size_t capacity, T value)
	{
		data = new T[capacity];
		this->capacity = capacity;
		this->size = capacity;

		for (size_t i = 0; i < capacity; i++)
		{
			data[i] = value;
		}
	}
	DynamicArray& operator=(const DynamicArray<T> &other)
	{
		if (this != &other)
		{
			clear();
			copyFrom(other);
		}

		return *this;
	}
	~DynamicArray()
	{
		clear();
	}

public:
	void clear()
	{
		delete[] data;
		data = NULL;
		size = 0;
		capacity = 0;
	}

	void push(const T& element)
	{
		if (size >= capacity)
			resize();

		data[size++] = element;
	}

	size_t getSize() const
	{
		return size;
	}

	size_t getCapacity() const
	{
		return capacity;
	}

	bool isEmpty() const
	{
		return size == 0;
	}

	T operator[](size_t index) const
	{
		if (isEmpty())
		{
			throw "Array is empty! Cannot get element";
		}

		if (index >= size)
		{
			throw "Invalid index! Cannot get element";
		}

		return data[index];
	}

	T& operator[](size_t index)
	{
		if (isEmpty())
		{
			throw "Array is empty! Cannot set element";
		}

		if (index >= size)
		{
			throw "Invalid index! Cannot set element";
		}
		return data[index];
	}

	void removeAt(size_t index)
	{

		if (isEmpty())
		{
			throw "Array is empty! Cannot remove element";
		}


		if (index >= size)
		{
			throw "Invalid index! Cannot remove element";
		}

		for (size_t i = index; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}
};