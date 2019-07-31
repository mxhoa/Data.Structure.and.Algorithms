/**
 * @brief 	[LOOP DETECTION]
 * @details Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the beginning of the loop.
 * 
 * DEFINITION: Circular linked list: A (corrupt) linked list in which a node's next pointer points to an earlier node, so as to make a loop in the linked list.
 * 
 * EXAMPLE
 * 		Input:  A - > B - > C - > D - > E - > C [the same C as earlier]
 * 		Output:	C
 * 		
 * BUILD: g++ findLoopDetection.cpp -std=c++11 -o findLoopDetection 
 * 
 */

#include <iostream>
#include <unordered_map>


class Node
{
public:
    int val;
    Node *next;

public:
    Node(int data)
    {
        this->val = data;
        this->next = nullptr;
    }
};

/**
 * SOLUTION1: Let slow and fast meet at some point after Floyd’s Cycle finding algorithm.
 * 		
 * _____m_____    ____________k___________[v]  
 * 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
 * 				  ^				 					  |
 * 				  |___________________________________|
 * 								 
 * 		Distance fast pointer = 2 x (Distance slow pointer)
 * 		
 * 				(m + n*x + k) = 2 * (m + n*y + k)
 * 				
 * 				<=>	  (m + k) = (x - 2y)*n
 * 				
 * 				=> 	  (m + k) is a multiple of n.
 * 	Where:			
 * 		n -> Length of cycle
 * 		m -> Distance of front node of cycle from head
 * 		k -> Distance of point where slow & fast meet
 * 		
 * 		x -> Number of complete cyclic rounds made by fast pointer before they meet first time.
 * 		y -> Number of complete cyclic rounds made by slow pointer before they meet first time
 * 		
 */
Node* findLoopDection1(Node *head)
{
	if (!head || !head->next) 
		return nullptr;

	Node *slow = head;
	Node *fast = head;
	bool isDetected = false;

	while (fast && fast->next && !isDetected)
	{
		slow = slow->next;
		fast = fast->next->next;
		isDetected = (slow == fast);
	}

	if (isDetected)
	{
		slow = head;
		while (slow != fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return fast;
	}
	else 
	{
		return nullptr;
	}
}

/**
 * SOLUTION2: Hash the address of the linked list nodes
 */
Node* findLoopDection2(Node *head)
{
	Node* curr = head;
	std::unordered_map<Node*, int> node_map;

	while (curr)
	{
		if (node_map.find(curr) != node_map.end())
			return curr;

		node_map[curr]++;
		curr = curr->next;
	}

	return nullptr;
}


int main()
{
	Node* head = new Node(50); 
    head->next = new Node(20); 
    head->next->next = new Node(15);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(10); 
    head->next->next->next->next->next = new Node(40); 
    head->next->next->next->next->next->next = head->next->next; 


    Node *beginLoop1 = findLoopDection1(head);
    Node *beginLoop2 = findLoopDection2(head);


    std::cout << "Value1 = " << beginLoop1->val << std::endl;
    std::cout << "Value2 = " << beginLoop2->val << std::endl;

    return 0;
}