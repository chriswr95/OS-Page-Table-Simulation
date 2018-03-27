Christopher Wright
COEN 177L Lab4

My Implimentation: 

My implimentation of the page replacement algorithms can be found in example.c. Pages are represented as a struct called a page. Each page contains three integers representing the frequency, turn accessed, and the actual page number. The page table is represented as an array of pages. The bulk of the function takes place in main(). Main uses a while loop to recieve page requests as inputs through the geline function. It will then check to see whether the page is in memory. If the page is in memory than updatePage() is called which will update the freq, and turnAccessed variables of the specific page. If the page is not in memory than main() attempts to insert the page at the end of the page table. If the page table is full than main uses one of the four page replacement algorithms in order to figure out which page to replace. They are described in detail below: 

lru(): lru stands for least recently used. This algorithm replaces the page that has been least recently accessed with the new page to be inserted. In order to do this lru() loops through the page table and records the index of the page with the smallest turnAccessed. It then returns this index. 

lfu(): lfu stands for least frequently used. This algorithm replaces the page that is least frequently used with the new page to be inserted. In order to do this lru loops through each page in the page table and returns the index of the page with the minimum freq. Note that freq is an int initialized to 0, and incremented by one every time the page is accessed.  

fifo(): fifo stands for first in first out. This algorithm keeps track of the oldest page in the page table, and replaces it with the new page to be inserted. In practice the oldest page in the page table is recorded by a pointer to the index of the array where the oldest page is stored qfront. qfront is initialized to 0. When a page fault occurs, fifo() returns the current value of qfront (the index of the oldest page in the array), and increments qfront by one. 

random(): random simply replaces a random page in the page table with the new page. This is implimented using the rand() function. rand() is seeded in main using srand(time(NULL)). The page replacement algorithm random() then returns a random integer from 0 to tableSize (an input from the user). 

My Results:


SCAN 10:

For all inputs and all algorithms, page table sizes of 500 or more yielded a hit rate of 4500. This is because the page table was large enough to accomodate each page. As a result after each page had been inserted into the page table, it remained in the page table for the duration of the program. No page replacement algorithms needed to be used.
 
The algorithm that showed the best performance for this file was LFU. This is because my LFU algorithm broke a tie in frequency by overwriting the earliest index in the tie. So when scanning through 1 to 500, LFU constantly overwrote the page at index 0, leaving the other pages in the page table intact. This lead to a liniar increase in the hit rate as the page table size increased. Until the page tablesize was greater than or equal to 500. At this point the page table can accomadate all requests and thus every time a page was requested after the first time the hit rate increased. 

The second best algorithm was random, which showed a linear increase in hitrate as the page table size increased.

The worst two algorithms for SCAN 10 were FIFO and LRU, this is becauses both of these algorithms were constantly overwriting the entire page table, so no page was ever stored in the page table when it was requested again. 

SCAN:

All algorithms showed a 0 hit rate for all page table sizes for this file. This is because each page was only requested one time. A page will always cause a miss the first time it is requested, as it is not in the page table.

RANDOM:

Every algorithm showed a liniar increase in hit rate compared to page table size for the Random file. Notably the hitrates varied little from algorithm to algorithm for a specific table size. This suggests that for a random input, specific algorithms such as FIFO, LFU, and LRU are no better than a random page replacement algorithm. 

Once again for table sizes of 500 or more, all algorithms showed a 4500 hit rate, because once each page had been requested a single time it remained in the table for the rest of the program. For page tables of this size no page replacement algorithm needed to be used as the table never filled up. 

Improvements:
FIFO: One way to improve fifo might be to impliment FIFO as a priority queue (as opposed to a regular queue). Such that pages with a lower priority are always closer to the front of the queue than pages with a higher priority. This would cause lower proirity pages to be removed before any higher priority pages are. 
 
