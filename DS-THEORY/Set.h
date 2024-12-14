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
			while (temp->left != this->H && temp->right != H)
			{
				if (val < temp->val)
				{
					temp = temp->left;
				}
				else if (val > temp->right)
				{
					temp = temp->right;
				}
				else
				{
					// this means the value is equal
					return;
				}
			}

		}

		

	}
};