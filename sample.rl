
#include <bits/stdc++.h>
using namespace std;
// #include <stdio.h>
// #include <string.h>

%% machine foo;
%% write data;
int main( int argc, char **argv )
{
	int cs, res = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	if ( argc > 1 ) {
		char *p = argv[1];
		char *eof = p + strlen(p);
		printf("Input is %s \n",p);
		vector<int> temp_numbersInPattern;
		%%{
			action A {
				res++;
				// printf("Match happened.\n");
				for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
					// cout << temp_numbersInPattern[i] << " ~ ";
					numbersInPattern.push_back(temp_numbersInPattern[i]);
				}
				cout << endl;
				numberList.push_back(numbersInPattern);
				numbersInPattern.clear();
				temp_numbersInPattern.clear();
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
				// printf("Error happened.\n");
				cs = foo_start;
				temp_numbersInPattern.clear();
			}
			main := ('ab'([0-9]+ $from(NUM))'cd')+ %to(A) <^(E);
			write init;
			write exec noend;
		}%%
	}
	// printf("input is %s\n", argv[1]);
	printf("Pattern matched %d times\n", res);
	cout << "Numbers in the list are " << endl;
	for (int i =0; i < numberList.size(); i++) {
		cout << "List " << i+1 << " : " << endl;
		for (int j=0;j<numberList[i].size(); j++) {
			cout << numberList[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}
