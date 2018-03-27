#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
	int randNum;
	srand(time(NULL));	

	ofstream myfile ("scan.txt");
	if(myfile.is_open()){
		for(int i = 1; i <= 500; i++){
			myfile << i << endl;
		}
	}	
	myfile.close();

	ofstream scan ("10scan.txt");
	if(scan.is_open()){
		for(int i = 1; i <= 5000; i++){
			scan << (i % 500) + 1 << endl;
		}
	}
	scan.close();

	ofstream ran ("rand.txt");
	if(ran.is_open()){
		for(int i = 1; i <= 5000; i++){
			randNum = (rand() % 500) + 1;
			ran << randNum << endl;	
		}
	}
	ran.close();

	return 0;
}
