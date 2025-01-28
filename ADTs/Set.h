#pragma once

template<typename K>
struct tNode {
	K data;
	tNode<K>* left;
	tNode<K>* right;
	tNode<K>* parent;
	bool is_Head;
	tNode() {
		is_Head = true;
	}
};

namespace cs211 {
	template<typename K>
	class set {
	private:
		tNode<K>* H;
		int SIZE;
	public:
		set()
		{
			this->H = new tNode<K>;
			this->H->parent = this->H;
			this->H->left = this->H;
			this->H->right = this->H;
			this->H->is_Head = true;
			this->SIZE = 0;
		}

		void delset(tNode<K>* node) {

			if (node->is_Head) {
				return;
			}

			delset(node->left);
			delset(node->right);

			delete node;
		}

		~set() {
			if (this->H->parent != this->H) {
				delset(this->H->parent);
			}

			delete this->H;
		}

		class iterator {
		private:
			tNode<K>* ptr;
			friend set;

		public:
			iterator() :ptr(nullptr) {};

			K operator *() {
				return this->ptr->data;
			}

			bool operator ==(const iterator& other) {
				return this->ptr == other.ptr;
			}

			bool operator !=(const iterator& other) {
				return (this->ptr != other.ptr);
			}

			iterator operator ++() {

				tNode<K>* ptr;
				ptr = this->ptr;

				if (ptr->right->is_Head != true) {
					ptr = ptr->right;

					while (ptr->left->is_Head != true) {
						ptr = ptr->left;
					}

					this->ptr = ptr;
					return *this;
				}

				else {
					tNode<K>* _parent;
					_parent = ptr->parent;

					while (ptr == _parent->right && ptr->parent->is_Head != true) {
						ptr = _parent;
						_parent = ptr->parent;
					}

					this->ptr = _parent;
					return *this;
				}
			}

			iterator operator++(int) {
				iterator old;
				old.ptr = this->ptr;
				this->operator ++();
				return old;
			}

			iterator operator --() {

				tNode<K>* ptr;
				tNode<K>* parent;
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
				this->operator--();
				return old;
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

		iterator find(const K& val) {

			iterator temp;
			temp.ptr = this->H->parent;

			while (temp.ptr != this->H) {

				if (temp.ptr->data == val) {
					return temp;
				}

				else if (temp.ptr->data < val) {
					temp.ptr = temp.ptr->right;
				}

				else {
					temp.ptr = temp.ptr->left;
				}
			}

			return temp;
		}

		tNode<K>* successor(const tNode<K>* ptr)
		{

			// to find the successor
			// first go to right
			// then go to left untill dummy head is found

		   tNode<K> *temp = ptr->right;
			while (temp->left != this->H) {
				temp = temp->left;
			}
			return temp;

		}

		tNode<K>* predecessor(const tNode<K>* ptr) {

			// to find the predecessor 
			// first go the left
			// go to right untill dummy head is found

			tNode<K> *temp = ptr->left;
			while (temp->right != this->H) {
				temp = temp->right;
			}
			return temp;
		}



		bool erase(const K& key) {
			iterator pos = find(key);
			if (pos.ptr == this->H) {
				return false;
			}


			tNode<K>* ptr = pos.ptr;
			tNode<K>* parent = ptr->parent;
			tNode<K>* succ = successor(ptr);
			tNode<K>* parent_succ = succ->parent;
			tNode<K>* pred = predecessor(ptr);

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
					// special case if sucessor is present on the right of the root node
					if (succ == ptr->right)
					{
						succ->left = ptr->left;
						ptr->left->parent = succ;
						succ->parent = ptr->parent;
						ptr->parent->parent = succ;
						delete ptr;
						return true;
					}
					else
					{
						succ->right = ptr->right;
						ptr->right->parent = succ;
						succ->left = ptr->left;
						ptr->left->parent = succ;
						succ->parent = parent;
						this->H->parent = succ;
						delete ptr;
						return true;
					}
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

		int size()const {
			return this->SIZE;
		}

		bool contains(const K& key) {

			iterator temp = find(key);
			return temp.ptr != this->H;
		}

		void insert(const K& val) {

			// creating the new tNode
			tNode<K>* nn;
			nn = new tNode<K>;
			nn->data = val;
			nn->left = this->H;
			nn->right = this->H;
			nn->is_Head = false;
			this->SIZE++;

			tNode<K>* temp;
			temp = this->H->parent;

			if (temp == this->H) { // this means it is the Root Node
				nn->parent = temp;
				this->H->parent = nn;
				this->H->left = nn;
				this->H->right = nn;
			}

			else {
				while (true)
				{
					if (nn->data < temp->data)
					{
						if (temp->left == this->H) {
							nn->parent = temp;
							temp->left = nn;
							break;
						}
						temp = temp->left;
					}
					else if (nn->data > temp->data)
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
						// this means the value is equal
						delete nn;
						this->SIZE--;
						return;
					}
				}

				// now we have to check if the left and right of the Dnode needed update or not
				if (nn->data < this->H->left->data)
				{
					this->H->left = nn;
				}
				else if (nn->data > this->H->right->data) {
					this->H->right = nn;
				}
			}
		}
	};
}
