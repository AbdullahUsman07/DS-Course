#pragma once

template<typename T>
struct tNode {
	T data;
	tNode<T>* left;
	tNode<T>* right;
	tNode<T>* parent;
};

template<typename T>
class set {
private:
	tNode<T>* H;

public:
	set()
	{
		H = new tNode<T>;
		H->parent = H;
		H->left = H;
	}

	class iterator {
	private:
		tNode<T>* ptr;
		friend set;

	public:
		iterator() :ptr(nullptr) {};
	};

	void insert(const T& val) {

		// creating the new tNode
		tNode<T>* nn;
		nn = new tNode<T>;
		nn->data = val;
		nn->left = H;
		nn->right = H;

		tNode<T>* temp;
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

	iterator find(const T& val) {

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
};