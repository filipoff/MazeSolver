#pragma once
#include <iostream>
template <class T>

class Vector
{

private:
	T* data;
	size_t size;
	size_t capacity;

private:

	void copyFrom(const Vector& other);
	void resize();

public:

	Vector();
	Vector(const Vector<T> &other);
	Vector(size_t capacity, T value);
	Vector& operator=(const Vector<T> &other);
	~Vector();

public:

	void clear();
	void push(const T& element);
	size_t getSize() const;
	size_t getCapacity() const;
	bool isEmpty() const;
	bool contains(const T& element) const;
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	void removeAt(size_t index);
};

template <class T>
void Vector<T>::copyFrom(const Vector& other)
{
	data = new T[other.capacity];

	for (size_t i = 0; i < other.size; i++)
	{
		data[i] = other.data[i];
	}

	capacity = other.capacity;
	size = other.size;
}

template <class T>
void Vector<T>::resize()
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

template <class T>
Vector<T>::Vector() : data(NULL), size(0), capacity(0) {}

template <class T>
Vector<T>::Vector(const Vector<T> &other){ copyFrom(other); }

template <class T>
Vector<T>::Vector(size_t capacity, T value)
{
	data = new T[capacity];
	this->capacity = capacity;
	this->size = capacity;

	for (size_t i = 0; i < capacity; i++)
	{
		data[i] = value;
	}
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}
	return *this;
}

template <class T>
Vector<T>::~Vector()
{
	clear();
}

template <class T>
void Vector<T>::clear()
{
	delete[] data;
	data = NULL;
	size = 0;
	capacity = 0;
}

template <class T>
void Vector<T>::push(const T& element)
{
	if (size >= capacity)
		resize();

	data[size++] = element;
}

template <class T>
size_t Vector<T>::getSize() const
{
	return size;
}

template <class T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template <class T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

template <class T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Invalid index when called const operator[]");
	}

	return data[index];
}

template <class T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Invalid index when called non-const operator[]");
	}

	return data[index];
}

template <class T>
void Vector<T>::removeAt(size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Invalid index when called removeAt()");
	}

	for (size_t i = index; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
}

template <class T>
bool Vector<T>::contains(const T& element) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == element)
			return true;
	}
	return false;
}