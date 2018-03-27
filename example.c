#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TABLE_SIZE 600

/* Impliment page table as array of pages as defined below.
 * Use page to keep track of the frequency and the last turn that a specific page was accessed. 
 * This aids with implementation of lfu and lru.
 */
struct page {
	int freq;
	int turnAccessed;
	int page;
};

/* parseArg1 checks to ensure the proper number of inputs, and 
 * returns the and integer corrisponding to the size of the page table
 */
int parseArg1(int argc, char*argv[]){
	if(argc == 3){
		return atoi(argv[2]);
	} else {
		fprintf(stderr, "Incorrect arguments \n");
		exit(-1);
	}
};


char* parseArg2(int argc, char*argv[]){
	if(argc == 3){
		return argv[2];
	} else {
		fprintf(stderr, "Incorrect arguments \n");
		exit(-1);
	}
};
/* isInMemory() will loop through the page table to check if a 
 * specific page is in memory. If the page is found, its index will
 * be returned. Otherwise -1 will be returned. 
 */
int isInMemory(int page, struct page *pageTable, int tableSize){
	int i;
	for(i = 0; i < tableSize; i++){
		if(pageTable[i].page == page){
			return i;
		}
	}

	return -1;
}

/* insertPage() will insert a page into the appropriate index in pageTable,
 * and initialize freq to 0, and turn accessed to the current number of requests
 */
void insertPage(struct page** pageTable, int pageTableIndex, int pageRequest, int requests){
	(*pageTable)[pageTableIndex].page = pageRequest;
	(*pageTable)[pageTableIndex].freq = 0;
	(*pageTable)[pageTableIndex].turnAccessed = requests;
}

/* updatePage() will update a page at the specified index by setting turnAccessed to the 
 * current number of requests, and incrementing freq. 
 */
void updatePage(struct page** pageTable, int index, int requests){
	(*pageTable)[index].turnAccessed = requests;
	(*pageTable)[index].freq++;

}

/* lru() impliments the least recently used page replacement algorithm and
 * returns the index of the page to be replaced.
 * See readme for in depth documentation.
 */ 
int lru(struct page** pageTable, int pageRequest, int tableSize){
	int i;
	int j = 0;
	
	for(i = 1; i < tableSize; i++){
		if((*pageTable)[i].turnAccessed < (*pageTable)[j].turnAccessed){
			j = i;
		}
	}
	return j;
	
}

/* fifo() impliments the first in first out page replacement algorithm and
 * returns the index of the page to be replaced.
 * See readme for in depth documentation.
 */ 
int fifo(int *qfront, int tableSize){
	int i = *qfront;	
	*qfront = (*qfront + 1) % (tableSize);
	return i;  
}

/* lfu() impliments the least frequently used page replacement algorithm and
 * returns the index of the page to be replaced. Note in the case of ties,
 * lfu returns the lowest index involved in the tie. 
 * See readme for in depth documentation.
 */ 
int lfu(struct page** pageTable, int pageRequest, int tableSize){
	int i;
	int j = 0;

	for(i = 1; i < tableSize; i++){
		if((*pageTable)[i].freq < (*pageTable)[j].turnAccessed){
			j = i;
		}
	}

	return j; 
}

/* random() returns a random index in page table.
 * See readme for in depth documentation
 */
int randomAlg(int tableSize){
	return rand() % tableSize;
}


int main(int argc, char* argv[]){
	//Declaration of Variables
	int pageTableSize = parseArg1(argc,argv);
	char* algorithm = argv[1];
	int pageTableIndex = 0, requests = 0, missRate = 0;
	struct page *pageTable = (struct page*) malloc(sizeof(struct page)*MAX_TABLE_SIZE);
	int pageRequest = 0;
	ssize_t bRead;
	size_t allocd = 0;
	char* input;
	int index;
	int qFront = 0;
	
	srand(time(NULL)); //seed rand() for use in the random algorithm

	while( (bRead = getline(&input, &allocd,stdin)) != EOF){ //stdin is routed to input
		requests++;
		pageRequest = atoi(input); //the string input is converted to an int
		if((index = isInMemory(pageRequest, pageTable, pageTableSize)) == -1){ //check to see whether the page table holds the page requested
			missRate++;

			if(pageTableIndex < pageTableSize){
				pageTable[pageTableIndex++].page = pageRequest;
			} else { //impliment page replacement algorithm
				if(strcmp(algorithm, "lru") == 0){
					index = lru(&pageTable, pageRequest, pageTableSize);
					insertPage(&pageTable, index, pageRequest, requests);
				} else if(strcmp(algorithm, "lfu") == 0){
					index = lfu(&pageTable, pageRequest, pageTableSize);
					insertPage(&pageTable, index, pageRequest, requests);
				} else if(strcmp(algorithm, "fifo") == 0){	
					index = fifo(&qFront, pageTableSize);
					insertPage(&pageTable, index, pageRequest, requests);
				} else if(strcmp(algorithm, "random") == 0){
					index = randomAlg(pageTableSize);
					insertPage(&pageTable, index, pageRequest, requests);
				} else { 
					printf("no alg used \n");
				}
			}

		} else {
//			printf("Page hit. Requests: %d, Page Request: %d, Index: %d, qfront: %d\n", requests, pageRequest, index, qFront);
			updatePage(&pageTable, index, requests);
		}
	}
	printf("Alg used: %s. Page Table Size: %d. Hit rate = %d\n", algorithm, pageTableSize, requests-missRate);
	
	free(input);
	free(pageTable);
	return 0;	
}

















