#pragma once

template<typename K>
struct tNode {
	K data;
	tNode<K>* left;
	tNode<K>* right;
	tNode<K>* parent;
};

template<typename K>
class set {
private:
	tNode<K>* H;

public:
	set()
	{
		H = new tNode<K>;
		H->parent = H;
		H->left = H;
	}

	class iterator {
	private:
		tNode<K>* ptr;
		friend set;

	public:
		iterator() :ptr(nullptr) {};
	};

	iterator begin() {
		iterator temp;
		temp.ptr = this->H->parent;
		return temp;
	}

	iterator end() {
		iterator temp;
		temp.ptr = this->H;
		return temp;
	}

	iterator find(const K& val) {

		iterator temp = this->H->parent;
		while (temp != this->H)
		{
			if (temp->data == val) {
				return temp;
			}
			else if (temp->data < val) {
				temp = temp->right;
			}
			else {
				temp = temp->left
			}
		}

		temp.ptr = nullptr;
		return temp;
	}

	tNode<K>* successor(const tNode<K>* ptr)
	{

		// to find the successor
		// first go to right
		// then go to left untill dummy head is found

		ptr = ptr->right;
		while (ptr->left != this->H) {
			ptr = ptr->left;
		}

	}

	tNode<K>* predecessor(const tNode<K>* ptr) {

		// to find the predecessor 
		// first go the left
		// go to right untill dummy head is found

		ptr = ptr->left;
		while (ptr->right != this->H) {
			ptr = ptr->right;
		}
	}



	bool erase(const K & key) {
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
				this->H->left = successor;
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
				this->H_ > right = pred;
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
			if (succ_parent == ptr) {
				
				// now we need to check if the node we want to delete is on
				// its right side of the parent or left
				if (ptr == parent->left) {
					parent->left = succ;
					succ->parent = parent;
					delete ptr;
					return true;
				}

				else {
					parent->right = succ;
					succ->parent = parent;
					delete ptr;
					return true;
				}
			}



		}
	}

	void insert(const K& val) {

		// creating the new tNode
		tNode<K>* nn;
		nn = new tNode<K>;
		nn->data = val;
		nn->left = H;
		nn->right = H;

		tNode<K>* temp;
		temp = this->H->parent;
		
		if (temp == this->H) { // this means it is the Root Node
			nn->parent = temp;
			this->H->parent = nn;
			this->H->left = nn;
			this->H->right = nn;
		}

		else {
			while (temp->left!=this->H && temp->right!=this->H)
			{
				if (nn->data < temp->data)
				{
					temp = temp->left;
				}
				else if (nn->data > temp->data)
				{
					temp = temp->right;
				}
				else
				{
					// this means the value is equal
					delete nn;
					return;
				}
			}

			// now we are at the leaf node
			if (nn->data < temp->data) {
				temp->left = nn;
				nn->parent = temp;
			}
			else {
				temp->right = nn;
				nn->parent = temp;
			}

			// now we have to check if the left and right of the Dnode needed update or not
			if (nn->data < this->H->left->data)
			{
				this->H->left = nn;
			}
			else if(nn->data >this->H->right->data){
				this->H->right = nn;
			}
		}
	}


	

	

	

};