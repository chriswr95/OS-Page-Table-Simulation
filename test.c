#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char* algs[4]; 	
	algs[0] = "lfu";
	algs[1] = "lru";
	algs[2] = "fifo";
	algs[3] = "random";
	int i, j;

	for(i = 0; i < 4; i++){
		for(j = 50; j <= 600; j = j + 50){
			//can I call fxn from here?
			//lookup sprintf(), make system(), or maybe execv? 
			printf("cat random.txt | ./example %s %d\n", algs[i], j); 	
		}
	}

	return 0;
}
