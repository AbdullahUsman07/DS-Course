#pragma once

#include<iostream>
template<typename T>
class queue {
private:
	int front;
	int back;
	T* data=nullptr;
	int total_size;
	int n; //it will use to track no of elements in queue

public:
	queue(int size)
	{
		total_size = size+1;
		front = back = 0;
		data = new T[total_size];
		n = 0;
	}

	~queue()
	{
		if (data != nullptr) {
			delete[] data;
		}
	}

	bool isempty()const
	{
		return front == back;
	}

	bool isFull()const
	{
		return (back + 1)%total_size == front;
	}

	void push(T val)
	{
		if (isFull())
			throw "Queue Overflowed! Pop previous Elements First!";

		// 
		back = (back + 1) % total_size;
		data[back] = val;
		n++
	}

	void pop()
	{
		if (isempty())
			throw " Queue Underflow! Nothing to Pop!";

		front = (front + 1) % total_size;
		n--;
	}

	int SIZE()const
	{
		return this->n;
	}

	T Back()const
	{
		if (isempty())
			throw"Queue Underflow!";

		return data[back];
	}

	T Front()const
	{
		if (isempty())
			throw"Queue Underflow!";

		return data[(front+1)%total_size];
	}

	void traverse()
	{
		int i = this->front + 1;

		do
		{
			std::cout << this->data[i] << " ";
			i = (i + 1) % total_size;
		} while (i != (back + 1) % total_size);
		std::cout << std::endl;
	}

    queue& operator=(const queue& other)
	{

		if (this->data != nullptr)
		{
			delete[] this->data;
		}

		this->front = other.front;
		this->back = other.back;
		this->total_size = other.total_size;
		//allocating the memory again
		this->data = new T[total_size];


		for (int i = other.front+1; i != (other.back + 1) % other.total_size; i = (i + 1) % total_size)
		{
			this->data[i] = other.data[i];
		}

		return *this;
	}

	// Non Member Functions
	template<typename T>
	friend bool operator ==(const queue<T>&, const queue<T>&);
	template<typename T>
	friend bool operator !=(const queue<T>&, const queue<T>&);
	template<typename T>
	friend bool operator <(const queue<T>&, const queue<T>&);
	template<typename T>
	friend bool operator >(const queue<T>&, const queue<T>&);
	template<typename T>
	friend bool operator >=(const queue<T>&, const queue<T>&);
	template<typename T>
	friend bool operator <=(const queue<T>&, const queue<T>&);
};

template<typename T>
bool operator==(const queue<T>& lhs, const queue<T>& rhs)
{
	if (lhs.SIZE() != rhs.SIZE())
	{
		return false;
	}

	int i = (lhs.front + 1) % lhs.total_size;
	int j = (rhs.front + 1) % rhs.total_size;

	for (int k = 0; k < lhs.SIZE(); k++)
	{
		if (lhs.data[i] != rhs.data[j])
		{
			return false;
		}
		i = (i + 1) % lhs.total_size;
		j = (j + 1) % rhs.total_size;
	}

	return true;
}

template<typename T>
bool operator !=(const queue<T>& lhs, const queue<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator <(const queue<T>&lhs , const queue<T>& rhs)
{
	int min_size = (lhs.SIZE() < rhs.SIZE()) ? lhs.SIZE() : rhs.SIZE();
	
	int i = (lhs.front + 1) % lhs.total_size;
	int j = (rhs.front + 1) % rhs.total_size;

	for (int k = 0; k < min_size; k++)
	{
		if (lhs.data[i] < rhs.data[j])
			return true;

		if (lhs.data[i] > rhs.data[j])
			return fasle;

		i = (i + 1) % lhs.total_size;
		j = (j + 1) % rhs.total_size;
	}

	retrun(lhs.SIZE() < rhs.SIZE());

}

template<typename T>
bool operator >(const queue<T>& lhs, const queue<T>& rhs)
{
	return (rhs < lhs);
}

template<typename T>
bool operator >=(const queue<T> & lhs, const queue<T> & rhs)
{
	return !(lhs < rhs);
}

template<typename T>
bool operator <=(const queue <T>& lhs, const queue<T> & rhs)
{
	return !(rhs < lhs);
}
