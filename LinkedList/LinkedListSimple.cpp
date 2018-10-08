#include <iostream>
#include "LinkedListSimple.h"
using namespace std;


// class Node 
// {
// public:
// 	int data;
// 	Node *next;
// public:
// 	Node(int val) 
// 	{
// 		this->data = val;
// 		this->next = nullptr;
// 	}
// };

// class LinkedListSimple 
// {
// public:
// 	Node *head;
// 	Node *tail;

// public:
// 	LinkedListSimple();
// 	~LinkedListSimple();
	
// 	void insert_node(int val);

// 	void print_list();
	
// 	void free_list();
	
// };

LinkedListSimple::LinkedListSimple() 
{
	this->head = nullptr;
	this->tail = nullptr;
}

LinkedListSimple::~LinkedListSimple() 
{
	this->free_list();
	this->head = nullptr;
	this->tail = nullptr;
}

void LinkedListSimple::insert_node(int val)
{
	Node *new_node = new Node(val);

	if (this->head == nullptr)
		this->head = new_node;
	else
		this->tail->next = new_node;

	this->tail = new_node;
}

void LinkedListSimple::print_list()
{
	if (this->head == nullptr)
	{
		cout << "Print List :: Empty!" << endl;
		return;
	}
	Node *runner = this->head;
	while (runner)
	{
		cout << "->" << runner->data;
		runner = runner->next;
	}
	cout << "\nPrint List :: Successful!" << endl;
}


void LinkedListSimple::free_list()
{
	if (this->head == nullptr)
	{
		cout << "Free  List :: Empty!" << endl;
		return;
	}
	while (this->head)
	{
		Node *tmp = this->head;
		this->head = this->head->next;
		delete(tmp);
	}
	cout << "Free  List :: Successful!" << endl;
}



void print_list(Node *head)
{
	if (head == nullptr)
	{
		cout << "print_list :: Empty!" << endl;
		return;
	}

	while (head)
	{
		cout << "->" << head->data;
		head = head->next;
	}
	cout << "\nprint_list :: Completed!" << endl;
}

void free_list(Node* &head)
{
	if (head == nullptr)
	{
		cout << "free_list :: Empty!" << endl;
		return;
	}
	Node *tmp = head;
	while (head)
	{
		tmp = head->next;
		delete(head);
		head = tmp;
	}
	cout << "\nfree_list :: Completed!" << endl;
}

// int main()
// {
// 	LinkedListSimple *l = new LinkedListSimple();

// 	l->insert_node(1);
// 	l->insert_node(2);
// 	l->insert_node(3);
// 	l->insert_node(4);
// 	l->insert_node(5);

// 	l->print_list();
// 	// print_list(l->head);

// 	l->free_list();
// 	// free_list(l->head);

// 	// print_list(l->head);
// 	l->print_list();


// 	return 0;
// }