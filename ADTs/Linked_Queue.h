#pragma once
#include<iostream>

template<typename T>
struct Node
{
	T data;
	Node* next;
};


template<typename T>
class Queue
{
private:
	Node <T>* front;
	Node <T>* back;
	int size;

public:

	// Constructor
	Queue()
	{
		front = nullptr;
		back = nullptr;
		size = 0;
	}

	// Copy Constructor
	/*Queue(const Queue& rhs)
	{
		this->operator=(rhs);
	}*/

	T Front()const
	{
		if (isEmpty())
		{
			
		throw "Queue UnderFlow";
		}
		return front->data;
	}

	T Back()const
	{
		if (!isEmpty())
		{
			return this->back->data;
		}
		throw "Queue UnderFlow";
	}

	bool isEmpty()
	{
		return size == 0;
	}

	void push(T data)
	{

		if (front == nullptr)
		{
           // it means that we are pushing the first element in the queue
			front = new Node<T>;
			front->data = data;
			back = front;
			back->next = nullptr;
			size++;
			return;
		}

		back->next = new Node<T>;
		back = back->next;
		back->data = data;
		back->next = nullptr;
		size++;
	}

	void pop()
	{
		if (isEmpty())
		{
			throw "Queue UnderFlow";
		}
		Node <T>* temp = front;
		front = front->next;
		delete temp;
		size--;

		// it means that queue is now empty
		if (front == nullptr)
			back = nullptr;
	}

	int SIZE()const
	{
		return this->size;
	}

	~Queue()
	{
		while (!isEmpty())
			pop();
	}

	void traverse()
	{
		Node <T>* temp = this->front;
		while (temp != nullptr)
		{
			std::cout << temp->data << "  ";
			temp = temp->next;
		}
	}


	const Queue& operator=(const Queue& rhs)
	{


		if (this->front != nullptr)
		{
			// empty the previous queue
			while (!isEmpty())
			{
				pop();
			}
		}


		// creating the first Node
		this->front = new Node<T>;
		this->front->data = rhs.front->data;
		this->front->next = nullptr;
		this->back = this->front;
		

		Node <T>* temp = rhs.front->next;
		while (temp!=nullptr)
		{
			this->back->next = new Node<T>;
			this->back = back->next;
			this->back->data = temp->data;
			this->back->next = nullptr;
			temp = temp->next;
		}
		this->size = rhs.size;

		return *this;
	}

	void SWAP(Queue& rhs)
	{
		std::swap(this->size, rhs.size);
		std::swap(this->front, rhs.front);
		std::swap(this->back, rhs.back);
	}

	// Reverse Function without using and additional Data Structure
	void Reverse()
	{
		// We will take 3 Pointers
		Node<T>* prev = nullptr;
		Node<T>* curr = this->front;
		Node<T>* nxt = nullptr;

		while (curr != nullptr)
		{
			nxt = curr->next;
			curr->next = prev;

			prev = curr;
			curr = nxt;
		}

		this->front = prev;
	}

	template<typename T>
	friend bool operator==(const Queue<T>&, const Queue<T>&);
	template<typename T>
	friend bool operator!=(const Queue<T>&, const Queue<T>&);
	template<typename T>
	friend bool operator<(const Queue<T>&, const Queue<T>&);
	template<typename T>
	friend bool operator>(const Queue<T>&, const Queue<T>&);
	template<typename T>
	friend bool operator<=(const Queue<T>&, const Queue<T>&);
	template<typename T>
	friend bool operator>=(const Queue<T>&, const Queue<T>&);
	

};


template<typename T>
 bool operator==(const Queue<T>& lhs, const Queue<T>& rhs)
{
	if (lhs.SIZE() != rhs.SIZE())
	{
		return false;
	}

	Node<T>* Lp = lhs.front;
	Node<T>* Rp = rhs.front;
	//comparing the first elements
	while (Lp != nullptr && Rp != nullptr)
	{
		if (Lp->data != Rp->data)
		{
			return false;
		}
		Lp = Lp->next;
		Rp = Rp->next;

	}
	return true;
}

 template<typename T>
 bool operator!=(const Queue<T>& lhs, const Queue<T>& rhs)
 {
	 return !(lhs == rhs);
 }


 template<typename T>
 bool operator<(const Queue<T>& lhs, const Queue<T>& rhs)
 {
	 

	 Node <T>* Rp = rhs.front;
	 Node<T>* Lp = lhs.front;
	 
	 while(Lp!=nullptr&& Rp!=nullptr)
	 {
		 if (Lp->data < Rp->data)
		 {
			 return true;
		 }
		 if (Lp->data > Rp->data)
		 {
			 return false;
		 }
		 Lp = Lp->next;
		 Rp = Rp->next;
	 }
	 return lhs.SIZE() < rhs.SIZE();
 }

 template<typename T>
 bool operator>(const Queue<T>& lhs, const Queue<T>& rhs)
 {
	 return (rhs < lhs);
 }

 template<typename T>
 bool operator <=(const Queue<T>& lhs, const Queue<T>& rhs)
 {
	 return !(rhs < lhs);
 }

 template<typename T>
 bool operator>=(const Queue<T>& lhs, const Queue<T>& rhs)
 {
	 return !(lhs < rhs);
 }