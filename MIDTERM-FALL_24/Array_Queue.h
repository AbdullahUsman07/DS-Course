#pragma once


template<typename T>
class queue {
private:
	int front;
	int back;
	T* data=nullptr;
	int n; // no of elements in the Queue

public:
	queue(int size)
	{
		front = back = 0;
		data = new T[size];
		n = 0;
	}

	~queue()
	{
		if (data != nullptr) {
			delete[] data;
		}
	}

	bool isempty()
	{
		return front == back;
	}

	T Front()const
	{
		
	}
};