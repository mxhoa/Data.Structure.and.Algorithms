#include "Binary_search_tree.h"

template <class Entry>
void print(Entry &e)
{
    cout << e << " ";
}

int tree_menu() 
{
    // •	insert one or several items into the tree, such items to be entered by the user at the keyboard
    cout << "1.insert one or several items into the tree" << endl;
    // •	do a tree traversal and write out the nodes as they are visited - user's choice of in-order, pre-order,  post-order, or level order
    cout << "2.do a tree traversal" << endl;
    // •	search the tree for a given item
    cout << "3.search the tree for a given item" << endl;
    // •	remove an item from the tree
    cout << "4.remove an item from the tree" << endl;
    // •	find the height of the tree
    cout << "5.find the height of the tree" << endl;
    // •	find the size of the tree
    cout << "6.find the size of the tree" << endl;
    // •	quit this tree
    cout << "0.quit this tree" << endl;
    int choice = -1;
    cin >> choice;
    while (choice < 0 || choice > 6)
    {
        cout << "Error: Invalid INPUT Try again" << endl;
        cin >> choice;
    }
    return choice;
}

int start_tree()
{
    cout << "Would You like a 1:Character Tree or 2:Integer Tree (1/2, -1 to Quit)" << endl;
    int choice = -1;
    while (!(cin >> choice))
    {
        cin.clear();
        cout << "Error: Invalid INPUT Try again" << endl;
        cin >> choice;
    }
    return choice;
}

template <class Entry>
void tree_loop(Binary_search_tree<Entry> *bst)
{
    int choice = tree_menu();
    while (choice != 0)
    {
        cout << choice << endl;
        switch (choice)
        {
        case 1:
            insert(bst);
            break;
        case 2:
            traversal(bst);
            break;
        case 3:
            search(bst);
            break;
        case 4:
            remove(bst);
            break;
        case 5:
            cout << "Height: " << bst->height() << endl;
            break;
        case 6:
            cout << "Size: " << bst->size() << endl;
            break;
        default:
            cout << "Error: Invalid INPUT" << endl;
            exit(1);
        }
        choice = tree_menu();
    }
}


void run()
{
    int tree;
    do {
        tree = start_tree();
        if (tree == 1)
        {
            Binary_search_tree<int>* bst = new Binary_search_tree<int>();
            tree_loop(bst);
            delete bst;
        }
        else if (tree == 2) 
        {
            Binary_search_tree<int>* bst = new Binary_search_tree<int>();
            tree_loop(bst);
            delete bst;
        }
        else
        {
            cout << "Exit" << endl;
            exit(1);
        }
        
    } while(true);
}

int trav_menu()
{
    cout << "Chose which way to print out the elements in the tree" << endl;
    cout << "1.In Order" << endl;
    cout << "2.Pre Order" << endl;
    cout << "3.Post Order" << endl;
    cout << "4.Level Order" << endl;
    int choice = -1;
    cin >> choice;
    while (choice < 0 || choice > 4)
    {
        cout << "Error: Invalid INPUT Try again" << endl;
        cin >> choice;
    }
    return choice;
}

template <class Entry>
void traversal(Binary_search_tree<Entry>* bst)
{
    int choice = trav_menu();
    
    switch (choice)
    {
        case 1:
            bst->inorder(print);
            break;
        case 2:
            bst->preorder(print);
            break;
        case 3:
            bst->postorder(print);
            break;
        case 4:
            bst->level_order(print);
            break;
        default:
            cout << "Error: Invalid INPUT" << endl;
            exit(1);
            break;
    }

    cout << endl;
}


template <class Entry>
void search(Binary_search_tree<Entry>* bst)
{
    Entry search;
    cout << "Enter A Search Term" << endl;
    while (!(cin >> search))
    {
        cin.clear();
        cout << "Error: Invalid INPUT Try again" << endl;
        cin >> search;
    }

    ERROR_CODE e = bst->tree_search(search);
    if (e == RES_NOT_PRESENT)
    {
        cout << "Search Term Was Not Found" << endl;
    }
    else
    {
        cout << "Search Term Was Found" << endl;
    }
    
}

template <class Entry>
void remove(Binary_search_tree<Entry>* bst)
{
    Entry remove;
    cout << "Entry A Term to Remove" << endl;
    while (!(cin >> remove))
    {
        cin.clear();
        cout << "Error: Invalid INPUT Try again" << endl;
        cin >> remove;
    }

    ERROR_CODE e = bst->remove(remove);

    if (e == RES_NOT_PRESENT)
    {
        cout << "Removal Was Not Completed" << endl;
    }
    else
    {
        cout << "Removal Completed" << endl;
    }
}

void insert(Binary_search_tree<int>* bst)
{
    cout << "Insert New Nodes (-1 to exit)" << endl;
    int e;
    while (cin >> e && e != -1)
    {
        bst->insert(e);
    }
}

void insert(Binary_search_tree<char>* bst)
{
    cout << "Insert New Nodes (Q to exit)" << endl;
    char e;
    char exit = *"Q";
    while (cin >> e && e != exit)
    {
        bst->insert(e);
    }
}

int main()
{
    run();
    return 0;
}