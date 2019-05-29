/*
 * Design a number (ID) generator system that generate numbers between 0-99999999 (8-digits).
 *   The system should support two functions:
 *   a. int getNumber();
 *   b. int requestNumber();
 * 
 *   getNumber() function should find out a number that is not assigned, than marks it as
 *   assigned and return that number.
 * 
 *   requestNumber() function checks the number is assigned or not. If it is assigned returns 0,
 *   else marks it as assigned and return 1.
 * 
 *   HINT: You can keep a counter for assigning numbers. Whenever there is a getNumber() call
 *   you will check if that number is already assigned in a Hash-Table. If it is already assigned,
 *   then increase the counter and check again. If you find a number not in the Hash-Table then
 *   add it to Hashtable and increase the counter.
 *   requestNumber() will look in the Hash-Table if the number is already taken, then it will
 *   return 0 else it will return 1 and mark that number as taken inside the Hash-Table.

*/