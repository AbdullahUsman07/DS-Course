#pragma once

#include<iostream>
#include<stdexcept>


template<typename T>
struct Node
{
	T data;
	Node<T>* next;
};

namespace cs211 {

	template<typename T>
	class forward_list
	{
	private:
		Node<T>* FRONT;
		int size;

	public:
		forward_list() :FRONT(nullptr), size(0) {};

		~forward_list()
		{
			while (this->FRONT != nullptr)
			{
				Node<T>* temp;
				temp = this->FRONT;
				this->FRONT = this->FRONT->next;
				delete temp;
			}
		}

		forward_list& operator =(const forward_list& f1)
		{

			if (this == &f1)
			{
				return *this;
			}
			// deleting the previous nodes in the list
			while (this->FRONT != nullptr)
			{
				Node<T>* temp;
				temp = this->FRONT;
				this->FRONT = this->FRONT->next;
				delete temp;
				this->size = 0;
			}

			// when the forward_list in parametre is also empty
			if (f1.FRONT == nullptr)
			{
				this->FRONT = nullptr;
			}

			// creating the first Node
			this->FRONT = new Node<T>;
			this->FRONT->data = f1.FRONT->data;
			this->FRONT->next= nullptr;

			Node<T>* rhs = this->FRONT;
			Node<T>* lhs = f1.FRONT->next;

			while (lhs != nullptr)
			{
				rhs->next = new Node<T>;
				rhs = rhs->next;
				rhs->data = lhs->data;
				rhs->next = nullptr;

				lhs = lhs->next;
				++this->size;
			}
			
			return *this;
		}

		void push_front(const T& val)
		{
			if (this->FRONT == nullptr)
			{
				this->FRONT = new Node<T>;
				this->FRONT->data = val;
				this->FRONT->next = nullptr;
				++this->size;
				return;
			}

			Node<T>* nn = new Node<T>;
			nn->data = val;
			nn->next = this->FRONT;
			this->FRONT = nn;
			++this->size;

			return;
		}

		void pop_front()
		{
			if (this->FRONT == nullptr)
			{
				return;
			}

			Node<T>* temp = this->FRONT;
			this->FRONT = this->FRONT->next;
			--this->size;
			delete temp;
		}


		T& front()const {
			return this->FRONT->data;
		}

		T& back()const {
			if (this->FRONT != nullptr) {

				Node<T>* temp= this->FRONT;
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}

				return temp->data;
			}
			
			throw std::runtime_error("Empty");
		}

		bool empty()
		{
			return this->FRONT == nullptr;
		}

		void clear()
		{
			while (this->FRONT != nullptr)
			{
				Node<T>* temp = this->FRONT;
				this->FRONT = this->FRONT->next;
				delete temp;
			}
		}


		
		


		class iterator {
		private:
			Node<T>* ptr;
			friend class forward_list;


		public:
			iterator() :ptr(nullptr) {};

			

			bool operator ==(const iterator& other) {
				return this->ptr == other.ptr;
			}

			bool operator !=(const iterator& other) {
				return !(this->ptr == other.ptr);
			}

			T operator *()
			{
				return this->ptr->data;
			}

			T* operator ->()
			{
				return &(this->ptr->data);
			}

			iterator operator ++(int) {
				iterator temp;
				temp.ptr = this->ptr;
				this->ptr = this->ptr->next;
				return temp;
			}

			iterator operator ++()
			{
				this->ptr = this->ptr->next;
				return *this;
			}
		};

		iterator begin()const {
			iterator temp;
			temp.ptr = this->FRONT;
			return temp;
		}

		iterator end()const {
			iterator temp;
			temp.ptr = nullptr;
			return temp;
		}

		iterator insert_after(const iterator pos, const T& val)
		{
			Node<T>* nn = new Node<T>;
			nn->next = pos.ptr->next;
			pos.ptr->next = nn;
			nn->data = val;

			iterator current;
			current.ptr = nn;
			++this->size;
			return current;

		}

		iterator erase_after(const iterator pos)
		{
			Node<T>* temp;
			temp = pos.ptr->next;
			pos.ptr->next = pos.ptr->next->next;

			delete temp;

			iterator iter;
			iter.ptr = pos.ptr->next;
			--this->size;

			return iter;
		}


		void splice_after(const iterator pos, forward_list<T> &other)
		{
			if (other.empty())
			{
				return;
			}
			Node<T>* temp = pos.ptr;
			Node<T>* temp_2 = pos.ptr->next;

			while (other.FRONT != nullptr)
			{
				temp->next = other.FRONT;

				temp = temp->next;
				other.FRONT = other.FRONT->next;
			}

			other.FRONT = nullptr;
		
			temp->next = temp_2;
		}
		
		void resize(int count,const T & val) {

			if (this->size == count) {
				return;
			}

			if (this->size < count) {

				while (this->size != count) {
					push_front(val);
				}
			}

			// size is greater than the count
			else {

				while (this->size != count) {
					pop_front();
				}
			}
		}

		void unique() {

			Node<T>* current = this->FRONT;

			// loop iterates untill we reach the last node
			while (current != nullptr && current->next != nullptr) {

				// this will traverse through whole forward_list
				Node<T>* dummy = current->next;
				Node<T>* prev = current;

				while (dummy != nullptr) {

					if (dummy->data == current->data) {
						Node<T>* temp = dummy;
						dummy = dummy->next;
						prev->next = dummy;
						delete temp;
					}
					else {
						prev = dummy;
						dummy = dummy->next;
					}
				}
				current = current->next;
			}
		}

		void reverse() {
			
			Node<T>* curr = this->FRONT;
			Node<T>* nxt = nullptr;
			Node<T>* prev = nullptr;

			while (curr != nullptr) {
				nxt = curr->next;
				curr->next = prev;

				prev = curr;
				curr = nxt;
			}
		}

		void sort() {

			Node<T>* current = this->FRONT;
			Node<T>* check = current->next;

			while (current != nullptr && current->next != nullptr) {

				bool swap = false;

				while (check != nullptr) {
					if (check->data > current->data) {
						std::swap(check, current);
						swap = true;
					}
					
				}

			}
		}

	};
}

// a recursive way to reverse the linked list

template<typename T>
void reverse(Node<T> *head) {

	if (head == nullptr || head->next = nullptr) {
		return;
	}

	Node<T>* newhead = reverse(head->next);
	head->next->next = head;
	head->next = nullptr;

	return newhead;
}