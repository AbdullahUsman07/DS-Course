#pragma once

#include<iostream>

template<typename K, typename V>
struct mTNode {
	std::pair<K, V> data;
	mTNode<K, V>* left;
	mTNode<K, V>* parent;
	mTNode<K, V>* right;
	bool is_H;
	mTNode() {
		is_H = true;
	}
};

namespace cs211 {
	template<typename K, typename V>
	class map {
	private:
		mTNode<K, V>* H;
		int SIZE;

		void copyNode(mTNode<K, V>* node, mTNode<K, V>* parent_node) {

			if (node->is_H) {
				return;
			}

			mTNode<K, V>* new_node;
			new_node = new mTNode<K, V>;
			new_node->data = node->data;
			new_node->is_H = false;
			new_node->parent = parent_node;
			new_node->left = this->H;
			new_node->right = this->H;

			if (parent_node->is_H == false && (new_node->data < parent_node->data)) {
				parent_node->left = new_node;
			}
			else if (parent_node->is_H == false && (new_node->data > parent_node->data)) {
				parent_node->right = new_node;
			}
			else {
				// this means we are creating the root node
				parent_node->parent = new_node;
				parent_node->left = new_node;
				parent_node->right = new_node;
			}

			// update the values of D-Head (smallest and greatest)
			if (new_node->data < this->H->left->data) {
				this->H->left = new_node;
			}
			if (new_node->data > this->H->right->data) {
				this->H->right = new_node;
			}

			copyNode(node->left, new_node);
			copyNode(node->right, new_node);
		}


	public:
		map() {
			this->H = new mTNode<K, V>;
			this->H->parent = this->H;
			this->H->right = this->H;
			this->H->left = this->H;
			this->H->is_H = true;
			this->SIZE = 0;
		}



		map<K, V>& operator =(map<K, V>& other) {
			// this means the tree already contain some nodes
			// so we have to delete it first
			if (this->H->parent != this->H) {
				delmap(this->H->parent);
			}


			// now we will copy the nodes
			copyNode(other.get_root_node(), this->H);

			return *this;
		}

		void delmap(mTNode<K, V>* node) {
			if (node->is_H) {
				return;
			}

			delmap(node->left);
			delmap(node->right);

			delete node;
		}

		mTNode<K, V>* get_root_node()const {
			return this->H->parent;
		}

		~map() {
			if (this->H->parent != this->H) {
				delmap(this->H->parent);
			}

			delete this->H;
		}

		class iterator {
		private:
			mTNode<K, V>* ptr;
			friend map;

		public:

			iterator() :ptr(nullptr) {};

			bool operator ==(const iterator& other) {
				return this->ptr == other.ptr;
			}

			bool operator !=(const iterator& other) {
				return (this->ptr != other.ptr);
			}

			iterator operator ++() {
				mTNode<K, V>* ptr;
				ptr = this->ptr;

				if (ptr->right->is_H != true) {
					ptr = ptr->right;

					while (ptr->left->is_H != true) {
						ptr = ptr->left;
					}

					this->ptr = ptr;
					return *this;
				}

				else {
					mTNode<K, V>* parent;
					parent = ptr->parent;
					while (ptr == parent->right && ptr->parent->is_H != true) {

						ptr = parent;
						parent = ptr->parent;
					}
					this->ptr = parent;

					return *this;
				}
			}

			iterator operator ++(int) {
				iterator old;
				old.ptr = this->ptr;
				this->operator ++();
				return old;
			}

			iterator operator --() {

				mTNode<K, V>* ptr;
				mTNode<K, V>* parent;

				ptr = this->ptr;
				parent = ptr->parent;


				// if we are at the root node we need to move to its predecessor

				if (ptr->left->is_Head == false) {

					ptr = ptr->left;

					while (ptr->right->is_Head == false) {
						ptr = ptr->right;
					}

					this->ptr = ptr;
					return *this;
				}

				// if the node is at the right side of its parent node we need to move to its parent

				else if (ptr == parent->right) {

					ptr = parent;
					parent = ptr->parent;
					this->ptr = ptr;
					return *this;

				}

				else {

					while (ptr == parent->left && parent->is_Head == false)
					{
						ptr = parent;
						parent = ptr->parent;
					}

					this->ptr = parent;
					return *this;
				}
			}

			iterator operator --(int) {
				iterator old;
				old.ptr = this->ptr;
				this->operator --();
				return old;
			}

			std::pair<K, V>* operator ->() {
				return &ptr->data;
			}

			V& operator [](const K& key) {
				iterator it = this->find(key);
				if (it == this->end()) {
					insert({ key,V() });
				}
				else {
					return it->second;
				}
			}


		};

		iterator begin() {
			iterator temp;
			temp.ptr = this->H->left;
			return temp;
		}

		iterator end() {
			iterator temp;
			temp.ptr = this->H;
			return temp;
		}

		iterator rbegin() {
			iterator temp;
			temp.ptr = this->H->right;
			return temp;
		}

		iterator rend() {
			iterator temp;
			temp.ptr = this->H;
			return temp;
		}

		iterator find(const K& key) {

			iterator temp;
			temp.ptr = this->H->parent;

			while (temp.ptr != this->H) {

				if (temp.ptr->data.first == key) {
					return temp;
				}

				else if (temp.ptr->data.first < key) {
					temp.ptr = temp.ptr->right;
				}

				else {
					temp.ptr = temp.ptr->left;
				}
			}

			return temp;
		}

		mTNode<K, V>* sucessor(const mTNode<K, V>* ptr) {

			// to find the successor
			// first go to right
			// then go to left untill dummy head is found

			mTNode<K, V>* temp = ptr->right;
			while (temp->left != this->H) {
				temp = temp->left;
			}
			return temp;

		}

		mTNode<K, V>* predecessor(const mTNode<K, V>* ptr) {

			// to find the predecessor 
			// first go the left
			// go to right untill dummy head is found

			mTNode<K, V>* temp = ptr->left;
			while (temp->right != this->H) {
				temp = temp->right;
			}
			return temp;
		}

		int size()const {
			return this->SIZE;
		}

		bool contains(const K& key) {

			iterator temp = find(key);
			return temp.ptr != this->H;
		}

		void insert(const std::pair<K, V> data) {

			mTNode<K, V>* nn;
			mTNode<K, V>* temp;

			temp = this->H->parent;
			nn = new mTNode<K, V>;
			nn->data = data;
			nn->is_H = false;
			nn->left = this->H;
			nn->right = this->H;
			this->SIZE++;

			if (temp == this->H) { // this means it is the Root Node
				nn->parent = temp;
				this->H->parent = nn;
				this->H->left = nn;
				this->H->right = nn;
			}

			else {
				while (true)
				{
					if (nn->data.first < temp->data.first)
					{
						if (temp->left == this->H) {
							nn->parent = temp;
							temp->left = nn;
							break;
						}
						temp = temp->left;
					}
					else if (nn->data.first > temp->data.first)
					{
						if (temp->right == this->H) {
							nn->parent = temp;
							temp->right = nn;
							break;
						}
						temp = temp->right;
					}
					else
					{
						// this means the keys are equal
						delete nn;
						this->SIZE++;
						return;
					}
				}

				// now we have to check if the left and right of the Dnode needed update or not
				if (nn->data.first < this->H->left->data.first)
				{
					this->H->left = nn;
				}
				else if (nn->data.first > this->H->right->data.first) {
					this->H->right = nn;
				}
			}
		}

		bool erase(const K& key) {
			iterator pos = find(key);
			if (pos.ptr == this->H) {
				return false;
			}


			mTNode<K, V>* ptr = pos.ptr;
			mTNode<K, V>* parent = ptr->parent;
			mTNode<K, V>* succ = successor(ptr);
			mTNode<K, V>* parent_succ = succ->parent;
			mTNode<K, V>* pred = predecessor(ptr);

			// there is a case we have to deal
			// case A if the node we want to delete is the smallest Node
			// then the left of H must be updated

			// if a node contains the smallest value and it is a leaf node
			// then its parent must have the second smallest val

			if (ptr == this->H->left) {

				if (ptr->right == this->H && ptr->left == this->H) {
					this->H->left = parent;
				}
				else
				{
					// the second smallest can be found be getting the sucessor
					this->H->left = succ;
				}
			}

			// case B the node we want to delete is the greatest node

			if (ptr == this->H->right) {

				if (ptr->right == this->H && ptr->left == this->H) {
					// node is the leaf node
					this->H->right = parent;
				}
				else {

					// the second greatest node can be found be using the predecessor function
					this->H->right = pred;
				}
			}



			// case no 1 if node is a Leaf Node
			if (ptr->right == this->H && ptr->left == this->H) {

				// now to check if the node we want to delete is on its
				// right side of its parent or left

				if (ptr == parent->right) {
					parent->right = this->H;
					delete ptr;
					return true;
				}

				else {
					parent->left = this->H;
					delete ptr;
					return true;
				}
			}

			// case no 2 if node has only one child
			// case no 2(a) if node has only left child

			else if (ptr->right == this->H && ptr->left != this->H) {

				// check again that if node on its right side of its parent or left

				if (ptr == parent->right) {
					parent->right = ptr->left;
					delete ptr;
					return true;
				}

				else {
					parent->right = ptr->left;
					delete ptr;
					return true;
				}
			}

			// case no 2(b) if node has only right child

			else if (ptr->right != this->H && ptr->left == this->H) {

				// check again that if node on its right side of its parent or left
				if (ptr == parent->right) {
					parent->right = ptr->right;
					delete ptr;
					return true;
				}

				else {
					parent->left = ptr->right;
					delete ptr;
					return true;
				}
			}

			// case no 3 if node has both childs
			// we can replace the node with its sucessor

			else {

				// This case will check if the succesor is the leaf node
				if (parent_succ == ptr) {

					// now we need to check if the node we want to delete is on
					// its right side of the parent or left
					if (ptr == parent->left) {
						parent->left = succ;
						succ->parent = parent;
						succ->right = ptr->right;
						ptr->right->parent = succ;
						delete ptr;
						return true;
					}

					else {
						parent->right = succ;
						succ->parent = parent;
						succ->right = ptr->right;
						ptr->right->parent = succ;
						delete ptr;
						return true;
					}
				}

				// we are deleting the root node

				else if (parent == this->H) {
					succ->right = ptr->right;
					ptr->right->parent = succ;
					succ->left = ptr->left;
					ptr->left->parent = succ;
					succ->parent = parent;
					this->H->parent = succ;
					delete ptr;
					return true;
				}

				else {

					// check if the node is on right side or left
					if (parent->right == ptr) {
						parent->right = succ;
						parent_succ->left = this->H;
						parent_succ->parent = succ;
					}

					else {
						parent->left = succ;
						parent_succ->parent = succ;
						parent_succ->right = this->H;
					}

					succ->right = parent_succ;
					succ->parent = parent;
					succ->left = ptr->left;
					ptr->left->parent = succ;
					delete ptr;
					return true;
				}

			}
		}
	}