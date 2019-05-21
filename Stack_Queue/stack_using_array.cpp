
#include <iostream>

class Stack
{
private:
    static const int MIN_CAPACITY = 10;
    int* data;
    int stack_top = -1;
    int capacity;

public:
    Stack();
    Stack(int capacity);
    ~Stack();
    virtual int size();
    virtual bool isEmpty();
    virtual int top();
    virtual void push(int value);
    virtual int pop();
    virtual void print();
};

Stack::Stack() : Stack(MIN_CAPACITY)
{
}

Stack::Stack(int MaxCapacity)
{
    data = new int[MaxCapacity];
    capacity = MaxCapacity;
}

Stack::~Stack()
{
    delete[] data;
}

bool Stack::isEmpty()
{
    return (stack_top == -1);
}

int Stack::size()
{
    return (stack_top + 1);
}

void Stack::print()
{
    for (int i = stack_top; i > -1; i--)
    {
        std::cout << " " << data[i];
    }
}

void Stack::push(int value)
{
    if (size() == capacity)
    {
        throw std::exception("StackOvarflowException");
    }
    stack_top++;
    data[stack_top] = value;
}

int Stack::pop()
{
    if (isEmpty())
    {
        throw std::exception("StackEmptyException");
    }
    int topVal = data[stack_top];
    stack_top--;
    return topVal;
}

int Stack::top()
{
    if (isEmpty())
    {
        throw std::exception("StackEmptyException");
    }
    return data[stack_top];
}

int main()
{
    Stack s(1000);
    for (int i = 1; i <= 100; i++)
    {
        s.push(i);
    }

    for (int i = 1; i <= 50; i++)
    {
        s.pop();
    }

    s.print();

    return 0;
}
