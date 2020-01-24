
#include <bits/stdc++.h>
using namespace std;
#define DEBUG 1

%% machine foo;
%% write data;

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	// char *p = (char *)malloc(INT_MAX * sizeof(char *));
	// if (argc >= 2) {
	// 	p = argv[1];
	// } else {
	// 	scanf("%s",p);
	// }
	cs = foo_start;
	totalLength = strlen(p);
	char *eof;
	printf("Input is %s \n",p);
	vector<int> temp_numbersInPattern;
	printf("cs is %d and foo_start is %d\n", cs, foo_start);

	%%{
		
		action CHUNK {
			cout << "Element -> " << (char) fc << endl;
			currentLength++;
		}	

		action A {
			res++;
			printf("ACTUAL Match happened.\n");
			if (DEBUG) {
				for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
					cout << temp_numbersInPattern[i] << " ~ ";
					numbersInPattern.push_back(temp_numbersInPattern[i]);
				}
				cout << endl;
				numberList.push_back(numbersInPattern);
				numbersInPattern.clear();
				temp_numbersInPattern.clear();
			}
			cs = foo_start;
			p--;
		}
		action NUM {
			// printf("fc =%c \n",fc);
			if (fc >= 48 && fc <= 57) {
				// printf("\tNum =%c \n",fc);
				temp_numbersInPattern.push_back( (char) (fc-48));
			}
		}
		action E {
			// res = 0;
			printf("Error happened.\n");
			cs = foo_start;
			printf("cs is %d and foo_start is %d\n", cs, foo_start);
			printf("currentLength is %d and totalLength is %d\n", currentLength, totalLength);

			temp_numbersInPattern.clear();
			if (currentLength >= totalLength) {
				// Force break... very bad practice
				cout << "Trying to break "<< endl;
				fbreak;
			}
			// fgoto main;
			
		}

		pattern1 = ((('ab'([0-9]+ $from(NUM))'cd')) $to(CHUNK) %to(A) $lerr(E));
		pattern2 = ((('ab'([0-9]+ $from(NUM))'ef')) $to(CHUNK) %to(A) $lerr(E));
		pattern3 = ((('cd'([0-9]+ $from(NUM))'ef')) $to(CHUNK) %to(A) $lerr(E));
		pat1 = ((('ab'([0-9]+)'cd') | ('cd'([0-9]+)'ef'))+) $to(CHUNK) %to(A) $lerr(E);
		#main := (pattern1 | pattern2 | pattern3)+;
		#main := ((('ab'([0-9]+ $from(NUM))'cd') | ('ab'([0-9]+ $from(NUM))'ef') | ('cd'([0-9]+ $from(NUM))'ef'))+) $to(CHUNK) %to(A) $lerr(E);
		main := ((('a'([0-9]+ $from(NUM))'a') | ('a'([0-9]+ $from(NUM))'b') | ('a'([0-9]+ $from(NUM))'c') | ('a'([0-9]+ $from(NUM))'d') | ('b'([0-9]+ $from(NUM))'a') | ('b'([0-9]+ $from(NUM))'b') | ('b'([0-9]+ $from(NUM))'c') | ('b'([0-9]+ $from(NUM))'d') | ('c'([0-9]+ $from(NUM))'a') | ('c'([0-9]+ $from(NUM))'b') | ('c'([0-9]+ $from(NUM))'c') | ('c'([0-9]+ $from(NUM))'d') | ('d'([0-9]+ $from(NUM))'a') | ('d'([0-9]+ $from(NUM))'b') | ('d'([0-9]+ $from(NUM))'c') | ('d'([0-9]+ $from(NUM))'d'))+)$to(CHUNK) %to(A) $lerr(E);
		#main := pat1;

	
		write init nocs;
		write exec noend;
	}%%

	cout << "Finished processing \n\n";
	


	printf("Pattern matched %d times\n", res);
	if (DEBUG) {
		cout << "Numbers in the list are " << endl;
		for (int i =0; i < numberList.size(); i++) {
			cout << "List " << i+1 << " : " << endl;
			for (int j=0;j<numberList[i].size(); j++) {
				cout << numberList[i][j] << " ";
			}
			cout << endl;
		}
	}

}


int main( int argc, char **argv )
{
	// char *inp;
	char *inp = (char *)malloc(INT_MAX * sizeof(char *));
	if (argc >= 2) {
		inp = argv[1];
	} else {
		scanf("%s",inp);
	}
	mine_pattern(inp);
	return 0;
}
