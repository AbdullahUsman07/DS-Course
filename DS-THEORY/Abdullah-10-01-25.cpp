//
//
//#include"map.h"
//
//// ---------------------------Asignment Operator overload--------------------------
//
//// this fucntion will copy
//template<typename K,typename V>
//struct mTNode {
//	std::pair<K, V> data;
//	mTNode<K, V>* left;
//	mTNode<K, V>* parent;
//	mTNode<K, V>* right;
//	bool is_H;
//	mTNode() {
//		is_H = true;
//	}
//};
//
//
//template<typename K, typename V>
//class map {
//	void copyNode(mTNode<K, V>* node, mTNode<K, V>* parent_node) {
//
//		if (node->is_H) {
//			return;
//		}
//
//		mTNode<K, V>* new_node;
//		new_node = new mTNode<K, V>;
//		new_node->data = node->data;
//		new_node->is_H = false;
//		new_node->parent = parent_node;
//		new_node->left = this->H;
//		new_node->right = this->H;
//
//		if (parent_node->is_H == false && (new_node->data < parent_node->data)) {
//			parent_node->left = new_node;
//		}
//		else if (parent_node->is_H == false && (new_node->data > parent_node->data)) {
//			parent_node->right = new_node;
//		}
//		else {
//			// this means we are creating the root node
//			parent_node->parent = new_node;
//			parent_node->left = new_node;
//			parent_node->right = new_node;
//		}
//
//		// update the values of D-Head (smallest and greatest)
//		if (new_node->data < this->H->left->data) {
//			this->H->left = new_node;
//		}
//		if (new_node->data > this->H->right->data) {
//			this->H->right = new_node;
//		}
//
//		copyNode(node->left, new_node);
//		copyNode(node->right, new_node);
//	}
//
//	// getter for root node
//	mTNode<K, V>* get_root_node()const {
//		return this->H->parent;
//	}
//
//	// i am calling this fucntion in = operator
//
//	map<K, V>& operator =(map<K, V>& other) {
//		// this means the tree already contain some nodes
//		// so we have to delete it first
//		if (this->H->parent != this->H) {
//			delmap(this->H->parent);
//		}
//
//
//		// now we will copy the nodes
//		copyNode(other.get_root_node(), this->H);
//
//		return *this;
//	}
//
//
//
//	// --------------------Destructor-----------------------
//	void delmap(mTNode<K, V>* node) {
//		if (node->is_H) {
//			return;
//		}
//
//		delmap(node->left);
//		delmap(node->right);
//
//		delete node;
//	}
//
//	~map() {
//		if (this->H->parent != this->H) {
//			delmap(this->H->parent);
//		}
//
//		delete this->H;
//	}
//	  
//	
//};  
