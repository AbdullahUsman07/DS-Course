#pragma once

#include<iostream>

template<typename T>
struct dNode {
	T data;
	dNode<T>* next;
	dNode<T>* prev;
};


namespace cs211 {
	template <typename T>
	class list {
	private:

		dNode<T>* H;

	public:
		list()
		{
			H = new dNode<T>;
			H->next = H;
			H->prev = H;
		}

		void push_front(const T& val)
		{
			dNode<T>* nn;
			nn = new dNode<T>;
			nn->data = val;

			nn->next = this->H->next;
			(this->H->next)->prev = nn;
			nn->prev = this->H;
			this->H->next = nn;
		}

		void push_back(const T& val)
		{
			
			dNode<T>* nn;
			nn = new dNode<T>;
			nn->data = val;

			nn->prev = this->H->prev; // this->H->prev gives us the last Node
			nn->next = this->H;
			(this->H->prev)->next = nn;
			this->H->prev = nn;
		}

		void pop_front()
		{
			if (this->H->next == this->H)
			{
				return;
			}
			dNode<T>* temp;
			temp = this->H->next;

			// now the next of the H node start pointing to the second node
			this->H->next = (this->H->next)->next;
			(this->H->next)->prev = this->H;

			delete temp;
		}

		void pop_back()
		{
			if (this->H->prev == this->H)
			{
				return;
			}
			dNode<T>* temp;
			temp = this->H->prev;
			
			// now the previous of the H node start pointing to the second Last Node
			this->H -> prev = (this->H->prev)->prev;
			(this->H->prev)->next = this->H;

			delete temp;
		}

		list& operator =(const list<T>& rhs)
		{
			if (rhs.H->next == rhs.H)
			{
				return *this;
			}

			while (this->H->next != this->H)
			{
				pop_front();
			}

			// now all the previous data has been cleared out


			// we will start copying from the next to Next H node
			dNode<T>* r = rhs.H->next;
			dNode<T>* l;
			l = new dNode<T>;
			l->data = r->data;
			l->next = this->H;
			l->prev = this->H;
			this->H->prev = l;
			this->H->next = l;
			r = r->next;
			
			while (r!= rhs.H)
			{
				dNode<T>* nn;
				nn = new dNode<T>;
				nn->data = r->data;
				nn->next = l->next;
				nn->prev = l;
				l->next = nn;
				l = nn;
				r = r->next;
			}
			this->H->prev = l;

			return *this;
		}

		void display()
		{
			dNode<T>* temp = this -> H->next;
			while (temp != this->H)
			{
				std::cout << temp->data << " - > ";
				temp = temp->next;
			}
			std::cout << " nullptr\n";
		}

		T front()const
		{
			if (this->H->next != H)
			{
				return this->H->next->data;
			}
			throw "Empty list";
		}

		T back()const
		{
			if (this->H->prev != H)
			{
				return this->H->prev->data;
			}
			throw "Empty list";
		}


		~list()
		{
			while (this->H->next != this->H)
			{
				pop_front();
			}
			delete this->H;
		}

	};
}

