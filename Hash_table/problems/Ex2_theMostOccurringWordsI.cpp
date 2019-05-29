/*
 * 2. Given a large string, find the most occurring words in the string.
 * What is the Time Complexity of the above solution? 
 * 
 * Hint:-
 *      a. Create a Hashtable which will keep track of <word, frequency>
 *      b. Iterate through the string and keep track of word frequency by inserting into Hash-Table.
 *      c. When we have a new word, we will insert it into the Hashtable with frequency 
 *          1. For all repetition of the word, we will increase the frequency.
 *      d. We can keep track of the most occurring words whenever we are increasing the frequency we 
 *          can see if this is the most occurring word or not.
 *      e. The Time Complexity is O(n) where n is the number of words in the string and Space
 *          Complexity is the O(m) where m is the unique words in the string.
 */