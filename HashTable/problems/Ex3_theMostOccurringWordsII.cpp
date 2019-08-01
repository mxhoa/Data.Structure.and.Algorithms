/*
 * Given a large string, find the most occurring words in the string
 * What if you are given whole work of OSCAR WILDE, most popular playwrights in the early 1890s.
 * 
 * 
 * Hint:-
 *      a. Who knows how many books are there, let’s assume there is a lot and we can’t put
 *          everything in memory. First, we need a Streaming Library so that we can read section by
 *          section in each document. Then we need a tokenizer that will give words to our program.
 *          And we need some sort of dictionary let’s say we will use HashTable.
 * 
 *      b. What you need is - 1. A streaming library tokenizer, 2. A tokenizer 3. A hashmap
 *          Method:
 *              1. Use streamers to find a stream of the given words
 *              2. Tokenize the input text
 *              3. If the stemmed word is in hash map, increment its frequency count 
 *                  else adds a word to hashmap with frequency 1
 * 
 * 
 *      c. We can improve the performance by looking into parallel computing. We can use the
 *          map-reduce to solve this problem. Multiple nodes will read and process multiple documents. 
 *          Once they are done with their processing, then we can use reduce to merge them.
 */