#include <bits/stdc++.h>
using namespace std;

int main() {
    // string ss = "abcdef";

    // const char *c = ss.c_str();
    // printf("Is %s \n", c);

	char input[] = ",a1,a2,1,a4,";
    char gfg[100] = " 1997 Ford E350 ac 3000.00"; 
	int commanCounter = 0;
    // // const char by = ',';
	// char* splitted = strtok(input, ",");
	// cout << splitted << endl;
	// cout << splitted << endl;

    string input1 = "a1 a2 a3 1 a4";
    string splitInput[10];
    stringstream ssin(input1);
    int n = 0;
    
    while(ssin.good()) {
        ssin >> splitInput[n];
        n++;
    }
    
    for (int i=0;i<n;i++) {
        cout << splitInput[i] << endl;
    }

    return 0;
}