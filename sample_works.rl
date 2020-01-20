
#include <bits/stdc++.h>
using namespace std;
#define DEBUG 2

%% machine foo;
%% write data;
int main( int argc, char **argv )
{
	int cs, res = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	if ( argc > 1 ) {
		char *p = argv[1];
		cs = foo_start;
		char *eof;// = p + strlen(p);
		printf("Input is %s \n",p);
		vector<int> temp_numbersInPattern;
		printf("cs is %d and foo_start is %d\n", cs, foo_start);

		%%{
			action CHUNK1 {
				// printf("Match happened. for CHUNK1\n");
				cout << "Last match element was " << (char) fc << endl;
			}

			action CHUNK2 {
				// printf("Match happened. for CHUNK2\n");
				cout << "Last match element was " << (char) fc << endl;
			}

			action CHUNK {
				// printf("Match happened. for CHUNK2\n");
				cout << "Element -> " << (char) fc << endl;
			}

			action A {
				res++;
				printf("ACTUAL Match happened.\n");
				if (DEBUG == 2) {
					for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
						cout << temp_numbersInPattern[i] << " ~ ";
						numbersInPattern.push_back(temp_numbersInPattern[i]);
					}
					cout << endl;
					numberList.push_back(numbersInPattern);
					numbersInPattern.clear();
					temp_numbersInPattern.clear();
				}
			}
			action NUM {
				// printf("fc =%c \n",fc);
				if (fc >= 48 && fc <= 57) {
					// printf("\tNum =%c \n",fc);
					temp_numbersInPattern.push_back( (char) (fc-48));
				}
			}
			action E {
				res = 0;
				printf("Error happened.\n");
				cs = foo_start;
				// cs = fentry(main);
				printf("cs is %d and foo_start is %d\n", cs, foo_start);

				temp_numbersInPattern.clear();
				if (fc == 'X') {
					cout << "Trying to break "<< endl;
					fbreak;
				}
				// fhold;
				// fgoto line;
				// fgoto main;
				// return foo_start;
			}
			 # line := any* @{ fgoto main; };

			pattern = ((('ab'([0-9]+ $from(NUM))'cd')+) $to(CHUNK) %to(A) $lerr(E));
			main := pattern;
		
			#main := ((('ab'([1234]+ $from(NUM))'cd')+) $to(CHUNK) %to(A) <^(E));# %to(NUM) <^(E);
			 # main := /ab[0-9]cd/ %to(A);
			 # main := ( ('a'([0-9]+)'c')+ ) $to(CHUNK) %to(A);
			# main := ((('ab') ([0-9]+ $from(NUM)) ('cd'))+)* %to(A) <>^(E);
			# main := (((('a'+)'b')+)+) %to(A) <>^(E);
			write init nocs;
			write exec noend;
		}%%

		cout << "Finished processing \n\n";
		
	}


	// printf("input is %s\n", argv[1]);
	printf("Pattern matched %d times\n", res);
	if (DEBUG == 2) {
		cout << "Numbers in the list are " << endl;
		for (int i =0; i < numberList.size(); i++) {
			cout << "List " << i+1 << " : " << endl;
			for (int j=0;j<numberList[i].size(); j++) {
				cout << numberList[i][j] << " ";
			}
			cout << endl;
		}
	}


	return 0;
}
