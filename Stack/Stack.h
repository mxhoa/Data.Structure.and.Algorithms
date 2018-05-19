/************************************************************************************************************************* 
 * COURSE: DATA STRUCTURE and ALGORITHM
 *
 * TOPIC: STACK
 * DESCRIPTION: A stack is a basic data structure that organized items in last-in-first-out (LIFO) manner
 *              Last element inserted in a stack will be the first to be removed from it.
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

typedef char Stack_entry;

typedef enum
{
    ERR_NO_ERROR,       // SUCCESS
    ERR_OVERFLOW,       // Overflow
    ERR_UNDERFLOW       // Underflow
} ERROR_CODE;

const int MIN_STACK = 10;


class Stack
{
private:
    int count = 0;
    int capacity;
    Stack_entry *entry;
public:
    /**
     * @brief   Constructor Function 
     *          The Stack is initialized to be empty
     */
    Stack();

    /**
     * @brief   Constructor Function
     *          The stack will be initialized with capacity
     */
    Stack(int nCapacity);

    /**
     * @brief   If the Stack is not empty, the top of the Stack is  removed.
     * @return  UNDERFLOW   - If the Stack is empty, otherwise SUCCESS
     */
    ERROR_CODE pop();

    /**
     * @brief   The top of a non-empty Stack is copied to 'item'
     * @return  UNDERFLOW   - If the Stack is empty
     */
    ERROR_CODE top(Stack_entry &item) const;

    /**
     * @brief   If the Stack isn't full, item is added to the top of the Stack
     * @return  OVERFLOW    - If the Stack is full
     */
    ERROR_CODE push(const Stack_entry &item);

    /**
     * @brief Check if Stack is empry or not
     * @return TRUE if the Stack is empty, otherwise FALSE
     */
    bool empty() const;

    /**
     * @brief   Check the Stack is full or not
     * @return  TRUE - Full, otherwise FALSE
     */
    bool full() const; 

    /**
     * @brief   Get the number of entries in the stack
     * @return  The number of entries in the stack
     */
    int size() const;

    /**
     * @brief   Destructor
     */
    ~Stack();
};