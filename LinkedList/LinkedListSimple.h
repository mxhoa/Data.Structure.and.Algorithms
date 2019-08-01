#include <iostream>
using namespace std;


class Node 
{
public:
	int data;
	Node *next;
public:
	Node(int val) 
	{
		this->data = val;
		this->next = nullptr;
	}
};

class LinkedListSimple 
{
public:
	Node *head;
	Node *tail;

public:
	LinkedListSimple();
	~LinkedListSimple();
	
	void insert_node(int val);

	void print_list();
	
	void free_list();
	
};

// Temp
void print_list(Node *head);
void free_list(Node* &head);