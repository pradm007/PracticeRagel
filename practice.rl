
#include <bits/stdc++.h>
using namespace std;
#define DEBUG 1

%% machine foo;
%% write data;

void mine_pattern(char *p) {
	int cs = foo_start;
	char *eof;
	
	%%{
		
		action A {
			printf("Match happened.\n");
        }
		
		action E {
			printf("Error happened.\n");
        }
		
		main := /ab*ab/ @A;
		#main := /abb* / @A;
		write init;
		write exec noend;
	}%%
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
