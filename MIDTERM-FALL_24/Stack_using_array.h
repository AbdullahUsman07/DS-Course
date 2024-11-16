#pragma once

#include<iostream>

template <typename T>
class Stack {
private:
	int top;
	T* arr;
	int capacity;

public:
	Stack(int size)
	{
		top = -1;
		capacity = size;
		arr = new T[capacity];
	}

	bool isEmpty()
	{
		return top == -1;
	}

	bool isFull()
	{
		return top == capacity - 1;
	}

	T TOP()const
	{
		if (top == -1)
		{
			throw "Stack Underflow!";
		}
		return this->arr[this->top];

	}

	int SIZE()const
	{
		return this->top;
	}

	void push(T val)
	{
		if (isFull())
		{
			throw "Stack Overflowed!";
		}
		++top;
		arr[top] = val;
	}

	void pop()
	{
		if (isEmpty())
			throw "Stack Underflow!";
		top--;
	}

	const Stack& operator=(const Stack<T>& other)
	{

		if (this == &other)
		{
			return *this;
		}

		// clear the previous data
		if (this->arr != nullptr)
		{
			delete[]arr;
		}

		this->capacity = other.capacity;
		this->arr = new T[capacity];
		this->top = other.top;
		for (int i = 0; i < other.top; i++)
		{
			this->arr[i] = other.arr[i];
		}

		return *this;

	}

	~Stack()
	{
		if (!isEmpty())
			delete[]this->arr;
	}

	void SWAP(Stack& other)
	{
		std::swap(this->capacity, other.capacity);
		std::swap(this->top, other.top);
		std::swap(this->arr, other.arr);
	}

	template<typename T>
	friend bool operator ==(const Stack<T>&, const Stack<T>&);
	template<typename T>
	friend bool operator !=(const Stack<T>&, const Stack<T>&);
	template<typename T>
	friend bool operator <(const Stack<T>&, const Stack<T>&);
	template<typename T>
	friend bool operator >(const Stack<T>&, const Stack<T>&);
	template<typename T>
	friend bool operator <=(const Stack<T>&, const Stack<T>&);
	template<typename T>
	friend bool operator >=(const Stack<T>&, const Stack<T>&);

};

template<typename T>
bool operator ==(const Stack<T>&lhs, const Stack<T>& rhs)
{
	if (lhs.SIZE() != rhs.SIZE())
	{
		return false;
	}

	for (int i = 0; i < lhs.SIZE(); i++)
	{
		if (lhs.arr[i] != rhs.arr[i])
		{
			return false;
		}
	}

	return true;
}

template<typename T>
bool operator !=(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator <(const Stack<T>& lhs, const Stack<T>& rhs)
{
	int min_index = (lhs.SIZE() < rhs.SIZE()) ? lhs.SIZE() : rhs.SIZE();

	for (int i = 0; i < min_index; i++)
	{
		if (lhs.arr[i] < rhs.arr[i])
		{
			return true;
		}

		if (lhs.arr[i] > rhs.arr[i])
		{
			return false;
		}
	}

	return lhs.SIZE() < rhs.SIZE();
}

template<typename T>
bool operator >(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return (rhs < lhs);
}

template<typename T>
bool operator <=(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return !(rhs < lhs);
}

template<typename T>
bool operator >=(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return !(lhs < rhs);
}