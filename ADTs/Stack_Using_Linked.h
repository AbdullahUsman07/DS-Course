#pragma once

#include<iostream>

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
};

template<typename T>
class Stack {
private:
	int size;
	Node<T>* top;

public:
	Stack() :size(0), top(nullptr) {};

	bool isEmpty()
	{
		return size == 0;
	}

	void push(T data)
	{
		try {
			Node<T>* new_node;
			new_node = new Node<T>;
			new_node->data = data;
			new_node->next = top;
			top = new_node;
			size++;
		}
		catch (std::bad_alloc& e)
		{
			throw"Stack Overflowed! Memory cant be alloacted!";
		}
	}

	void pop()
	{
		if (isEmpty())
		{
			throw"Stack Underflow!";
		}
		Node<T>* temp = top;
		top = top->next;
		delete temp;
		size--;
	}
	
	~Stack()
	{
		while (!this->isEmpty())
		{
			pop();
		}
	}

	T TOP()
	{
		if (!this->isEmpty())
		{
			return this->top->data;
		}
	}

	int SIZE()
	{
		return this->size;
	}
	const Stack& operator =(const Stack& other)
	{
		//emptying the previous stack
		while (!isEmpty())
		{
			pop();
		}

		this->size = other.size;

		//create the first Node
		top = new Node<T>;
		top->data = other.top->data;
		Node<T>* curr = top;

		Node<T>* temp = other.top->next;

		while (temp != nullptr)
		{
			curr->next = new Node<T>;
			curr->next->data = temp->data;
			curr = curr->next;
			temp = temp->next;
		}
		curr ->next = nullptr;

		return *this;
	}

	void SWAP(Stack& other)
	{
		std::swap(this->size, other.size);
		std::swap(this->top, other.top);
	}

	void traverse()
	{
		Node<T>* temp = top;
		while (temp != nullptr)
		{
			std::cout << temp->data<<"  ";
			temp = temp->next;
		}
	}

	void revesrse()
	{
		Node<T>* prev = nullptr;
		Node<T>* curr = this->top;
		Node<T>* nxt = nullptr;

		while (curr != nullptr)
		{
			nxt = curr->next;
			curr->next = prev;

			prev = curr;
			curr = nxt;
		}
		this->top = prev;
	}

	template <typename T>
	friend bool operator ==(const Stack<T>&,const Stack<T>&);
	template <typename T>
	friend bool operator !=(const Stack<T>&, const Stack<T>&);
	template <typename T>
	friend bool operator <(const Stack<T>&, const Stack<T>&);
	template <typename T>
	friend bool operator >(const Stack<T>&, const Stack<T>&);
	template <typename T>
	friend bool operator <=(const Stack<T>&, const Stack<T>&);
	template <typename T>
	friend bool operator >=(const Stack<T>&, const Stack<T>&);


};

template <typename T>
bool operator ==(const Stack<T>& lhs, const Stack<T>& rhs)
{
	if (lhs.size != rhs.size)
	{
		return false;
	}

	Node<T>* Lp = lhs.top;
	Node<T>* Rp = rhs.top;

	while (Lp != nullptr && Rp !=nullptr)
	{
		if (Lp->data != Rp->data)
			return false;
		Lp = Lp->next;
		Rp = Rp->next;
	}

	return true;

}

template <typename T>
bool operator !=(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return !(lhs == rhs);
}


template <typename T>
bool operator <(const Stack<T>& lhs, const Stack<T>& rhs)
{
	Node<T>* Lp = lhs.top;
	Node<T>* Rp = rhs.top;

	while (Lp != nullptr && Rp != nullptr)
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

	return lhs.size< rhs.size;

}




template <typename T>
bool operator >(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return rhs < lhs;
}

template <typename T>
bool operator <=(const Stack<T>&lhs, const Stack<T>&rhs)
{
	return !(rhs < lhs);
}

template <typename T>
bool operator >=(const Stack<T>&lhs, const Stack<T>&rhs)
{
	return !(lhs < rhs);
}

bool bracket_balance(const std::string& input)
{
	Stack<char> stack;
	for (int i = 0; i < input.length(); i++)
	{
		char current = input[i];
		if (current== '(' || current== '[' || current== '{')
		{
			stack.push(input[i]);
		}

		else if (current==')' || current == ']' || current == '}')
		{
			 if (stack.isEmpty())
				return false;

			char top = stack.TOP();
			 if ((current==')' && top=='(')|| (current == ']' && top == '[') || (current == '}' && top == '{'))
			 {
				stack.pop();
			 }
			 else
			 {
				 return false;
			 }
		}
	}

	return stack.isEmpty();

}
