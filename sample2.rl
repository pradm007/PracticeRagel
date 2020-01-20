
#include <bits/stdc++.h>
using namespace std;

%% machine foo;
%% write data;
int main( int argc, char **argv )
{
	int cs, res = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	if ( argc > 1 ) {
		printf("\tInside actual mining. Mining starts now for pattern lookup.\n");
		char* p = argv[1];//"a12b43a321b";

		vector<int> numbersInPattern;
		vector<vector<int> > numberList;	
		int cs, res = 0;
		char *eof = p + strlen(p);
		printf("Input is %s \n",p);
		
		vector<int> temp_numbersInPattern;

		%%{

			action A {
				res++;
				printf("Match happened.\n");
				for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
					cout << temp_numbersInPattern[i] << " ~ ";
					numbersInPattern.push_back(temp_numbersInPattern[i]);
				}
				printf("\n");
				numberList.push_back(numbersInPattern);
				numbersInPattern.clear();
				temp_numbersInPattern.clear();
			}
			action NUM {
				printf("fc =%c \n",fc);
				if (fc >= 48 && fc <= 57) {
					// printf("	Num =%c \n",fc);
					temp_numbersInPattern.push_back( (char) (fc-48));
				}
			}
			action E {
				res = 0;
				printf("Error happened.\n");
				cs = foo_start;
				temp_numbersInPattern.clear();
			}
			
			main := ('a'([0-9]+ $from(NUM))'b')+ %to(A) <^(E);
			write init;
			write exec noend;
		}%%

		printf("Pattern matched %d times\n", res);
		if (res > 0) {
			printf("Numbers in the list are \n");
			for (int i =0; i < numberList.size(); i++) {
				printf("List %d : \n", i+1);
				for (int j=0;j<numberList[i].size(); j++) {
					printf("%d ",numberList[i][j]);
				}
				printf("\n");
			}
		}
		
	}


	// // printf("input is %s\n", argv[1]);
	// printf("Pattern matched %d times\n", res);
	// cout << "Numbers in the list are " << endl;
	// for (int i =0; i < numberList.size(); i++) {
	// 	cout << "List " << i+1 << " : " << endl;
	// 	for (int j=0;j<numberList[i].size(); j++) {
	// 		cout << numberList[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }


	return 0;
}
