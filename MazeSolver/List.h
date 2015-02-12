#pragma once
#include <iostream>


template <class T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>* previous;
	Node();
	Node(const T& element);
	Node(const Node<T>& other);
	Node& operator=(const Node<T>& other);
	~Node() {};
};

template <class T>
Node<T>::Node() : next(NULL), previous(NULL) {}

template <class T>
Node<T>::Node(const T& element) : data(element), previous(NULL), next(NULL) {}

template <class T>
Node<T>::Node(const Node<T>& other)
{
	data = other.data;
	next = previous = NULL;
}

template <class T>
Node<T>& Node<T>::operator=(const Node<T>& other)
{
	if (this != &other)
	{
		data = other.data;
		previous = next = NULL;
	}
	return *this;
}







template <class T>
class List
{

private:

	Node<T>* first;
	Node<T>* last;
	size_t size;

private:
	void copyFrom(const List<T>& other);


public:
	List();
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	~List();

public:

	class Iterator
	{

	private:
		Node<T>* element;
		Iterator(Node<T>* element);
		friend class List < T > ;
	public:
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		typename const List<T>::Iterator& operator++() const;
		typename List<T>::Iterator& operator++();
		typename const List<T>::Iterator& operator--() const;
		typename List<T>::Iterator& operator--();
		const T& operator*() const;
		T& operator*();
	};

public:
	bool isEmpty() const;
	void push_back(const T& element);
	void push_front(const T& element);
	T pop_back();
	T pop_front();
	T peek_front() const;
	T peek_back() const;
	size_t getSize() const { return size; }
	void clear();
	void removeAt(Iterator& iter);
	void remove(const T& element);
	Iterator begin();
	Iterator end();
};


template <class T>
bool List<T>::isEmpty() const
{
	return size == 0;
}

template <class T>
void List<T>::copyFrom(const List<T>& other)
{
	if (!other.isEmpty())
	{
		first = last = new Node<T>(other.first->data);
		size++;
		Node<T>* pointer = other.first;
		while (pointer->next)
		{
			pointer = pointer->next;
			push_back(pointer->data);
		}
	}
}


template <class T>
List<T>::List()
{
	first = last = NULL;
	size = 0;
}

template <class T>
List<T>::List(const List<T>& other)
{
	first = last = NULL;
	size = 0;
	copyFrom(other);
}

template <class T>
List<T>::~List()
{
	clear();
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{ 
		clear();
		copyFrom(other);
	}
	return *this;
}

template <class T>
void List<T>::push_back(const T& element)
{
	if (isEmpty())
	{
		first = last = new Node<T>(element);
	}
	else
	{
		last->next = new Node <T>(element);
		last->next->previous = last;
		last = last->next;
	}
	size++;
}

template <class T>
void List<T>::push_front(const T& element)
{
	if (isEmpty())
	{
		first = last = new Node<T>(element);
	}
	else
	{
		first->previous = new Node<T>(element);
		first->previous->next = first;
		first = first->previous;
	}
	size++;
}

template <class T>
T List<T>::pop_back()
{
	if (isEmpty())
	{
		throw std::out_of_range("Popped empty list!");
	}
	T data = last->data;
	Node<T>* toPop = last;

	if (size == 1)
	{
		first = last = NULL;
		delete toPop;
		size--;
		return data;
	}

	last->previous->next = NULL;
	last = last->previous;
	delete toPop;
	size--;
	return data;
}

template <class T>
T List<T>::peek_front() const
{
	if (isEmpty())
	{
		throw std::out_of_range("Peeked empty list!");
	}
	T data = first->data;
	return data;
}

template <class T>
T List<T>::peek_back() const
{
	if (isEmpty())
	{
		throw std::out_of_range("Peeked empty list!");
	}
	T data = last->data;
	return data;
}

template <class T>
T List<T>::pop_front()
{
	if (isEmpty())
	{
		throw std::out_of_range("Popped empty list!");
	}

	T data = first->data;
	Node<T>* toPop = first;

	if (size == 1)
	{
		first = last = NULL;
		delete toPop;
		size--;
		return data;
	}

	first->next->previous = NULL;
	first = first->next;
	delete toPop;
	size--;
	return data;
}


// more info about pop_back and pop_front

template <class T>
void List<T>::removeAt(Iterator& iter)
{
	if (isEmpty())
	{
		throw std::out_of_range("called removeAt when list is empty!");
	}
	if (iter.element == first)
	{
		++iter;
		pop_front();
	}
	else if (iter.element == last)
	{
		--iter;
		pop_back();
		++iter;
	}
	else
	{
		Node<T>* pointer = iter.element;
		++iter;
		pointer->next->previous = pointer->previous;
		pointer->previous->next = pointer->next;
		pointer->next = pointer->previous = NULL;
		delete pointer;
		size--;
	}
}

template <class T>
void List<T>::remove(const T& element)
{
	if (isEmpty())
	{
		throw std::out_of_range("called remove when list is empty!");
	}

	/*
	if (first == last)
	{
		if (first->data == element)
			pop_back();
	}
	else
	{
		Iterator it = begin();

		while (it != end())
		{
			if (*it == element)
			{
				removeAt(it);
			}
			++it;
		}
	}
	*/

	for (Iterator it = begin(); it != end();)
	{
		if ((*it) == element)
			removeAt(it);
		else
			++it;
	}
}


template <class T>
void List<T>::clear()
{
	while (!isEmpty())
	{
		pop_back();
	}
}

template <class T>
List<T>::Iterator::Iterator(Node<T>* element) : element(element) {}

template <class T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
	return element == other.element;
}

template <class T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
	return element != other.element;
}

template <class T>
typename const List<T>::Iterator& List<T>::Iterator::operator++() const
{
	if (element)
		element = element->next;
	return *this;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
	if (element)
		element = element->next;
	return *this;
}

template <class T>
typename const List<T>::Iterator& List<T>::Iterator::operator--() const
{
	if (element)
		element = element->previous;
	return *this;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator--()
{
	if (element)
		element = element->previous;
	return *this;
}

template <class T>
const T& List<T>::Iterator::operator*() const
{
	return element->data;
}

template <class T>
T& List<T>::Iterator::operator*()
{
	return element->data;
}

template <class T>
typename List<T>::Iterator List<T>::begin()
{
	return Iterator(first);
}

template <class T>
typename List<T>::Iterator List<T>::end()
{
	if (!last)
		return  Iterator(NULL);
	return Iterator(last->next);
}



