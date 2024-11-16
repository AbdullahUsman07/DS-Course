#include<iostream>

template<typename T>
struct Node
{
	T data;
	Node* next;
};

template<typename T>
void del_list(Node<T> *head)
{
	Node<T>* temp;
	while (head!=nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename T>
Node<T>* create_Node(T data)
{
	Node<T>* new_node = new Node<T>;
	new_node->data = data;
	new_node->next = nullptr;

	return new_node;
}

template<typename T>
void travserse(Node<T>* head)
{
	Node<T>* temp;
	while (head != nullptr)
	{
		temp = head;
		std::cout << temp->data<<"  ->  ";
		head = head->next;
	}
	std::cout<<" NULL" << "\n";
}

template<typename T>
Node<T>* del_begin(Node<T>* head)
{ 
	if (head == nullptr)
	{
		return head;
	}
	Node<T>* temp = head;
	head = head->next;
	delete temp;
	return head;
}

template<typename T>
Node<T>* del_end(Node<T>* head)
{
	if (head == nullptr)
	{
		return head;
	}

	if (head->next == nullptr)
	{
		// this means there is only one node
		delete head;
		return nullptr;
	}
	Node<T>* temp = head;

	// traversing untill the second last Node
	while (temp->next!= nullptr && temp->next->next!=nullptr)
	{
		temp = temp->next;
	}

	delete temp->next;
	temp->next = nullptr;
	return head;
}

template<typename T>
Node<T>* del_Node(Node<T>* head,T data)
{
	if (head == nullptr)
	{
		return nullptr;
	}

	// if the value is found at first
	if (head->data == data)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		return head;
	}

	Node<T>* temp = head;
	Node<T>* prev=nullptr;

	

	while (temp!=nullptr && temp->data!=data)
	{
		prev = temp;
		temp = temp->next;
	}


	if (temp == nullptr)
	{
		//means value does not exist
		std::cout << " Value Does Not Exist!\n";
		return head;
	}
	
	prev->next = temp->next;
	delete temp;
	return head;
	
}

//------------------------------------------------------------\\
//--------Insertion Cases-------------------------------------\\

template<typename T>
Node<T>* insert_beg(Node<T>* head,T data)
{
	if (head == nullptr)
	{
		// means list is empty
		head = create_Node(data);
		head->next = nullptr;
		return head;
	}

	Node<T>* temp = create_Node(data);
	temp->next = head;
	head = temp;
    return head;
}

template<typename T>
Node<T>* insert_end(Node<T>* head, T data)
{
	if (head == nullptr)
	{
		// means list is empty
		head = create_Node(data);
		head->next = nullptr;
		return head;
	}

	Node<T>* temp = head;
	Node<T>* new_Node = create_Node(data);
	while (temp ->next != nullptr)
	{
		temp = temp->next;
	}
	new_Node->next = nullptr;
	temp->next = new_Node;

	return head;
}

template<typename T>
// this function will insert after the specified Node
Node<T>* insert_after(Node<T>* head, T node_data, T data)
{
	if (head == nullptr)
	{
		std::cout << " List is Empty!\n";
		return nullptr;
	}

	Node<T>* temp = head;
	Node<T>* nxt=nullptr;

	while (temp!=nullptr &&temp->data!=node_data)
	{
		temp = temp->next;
	}

	if (temp == nullptr)
	{
		std::cout << " Value Not Found!\n";
		return head;
	}

	Node<T>* new_node = create_Node(data);
	nxt = temp->next;
	temp->next = new_node;
	new_node->next = nxt;

	return head;
}

template<typename T>
Node<T>* insert_before(Node<T>* head, T node_data, T data)
{
	if (head == nullptr)
	{
		std::cout << " List is Empty";
		return head;
	}

	
	// if insertion happen in first Node
	if (head->data == node_data)
	{
		Node<T>* temp = create_Node(data);
		temp->next = head;
		head = temp;
		return head;
	}

	//Now we will start from second Node
	Node<T>* temp = head->next;
	Node<T>* prev = head;

	while (temp != nullptr && temp-> data != node_data)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == nullptr)
	{
		std::cout << " Value Does Not Found!\n";
		return head;
	}

	
	
	Node<T>* new_Node = create_Node(data);
	new_Node->next = temp;
	prev->next = new_Node;

	return head;

}

template<typename T>
Node<T>* reverse(Node<T>* head)
{
	if (head == nullptr)
	{
		std::cout << "List is Empty!\n";
	}

	Node<T>* prev = nullptr;
	Node<T>* curr = head;
	Node<T>* nxt = nullptr;

	while (curr != nullptr)
	{
		nxt = curr->next;
		curr->next = prev;

		prev = curr;
		curr = nxt;
	}

	return prev;
}

//int main()
//{
//	Node<char>* head = create_Node('A');
//	Node<char>* Node_1 = create_Node('B');
//	Node<char>* Node_2 = create_Node('C');
//	Node<char>* Node_3 = create_Node('D');
//	Node<char>* Node_4 = create_Node('E');
//
//	head->next = Node_1;
//	Node_1->next = Node_2;
//	Node_2->next = Node_3;
//	Node_3->next = Node_4;
//	Node_4->next = nullptr;
//
//	travserse(head);
//	head = del_Node(head, 'B');
//	travserse(head);
//	head = insert_beg(head, 'X');
//	travserse(head);
//	head = insert_end(head, 'Z');
//	travserse(head);
//	head = insert_after(head, 'X', 'G');
//	travserse(head);
//	head = insert_before(head, 'S', 'L');
//	travserse(head);
//	head=reverse(head);
//	travserse(head);
//	del_list(head);
//}