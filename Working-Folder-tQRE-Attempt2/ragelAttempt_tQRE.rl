
#include <bits/stdc++.h>
using namespace std;
#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef MINIMAL
#define MINIMAL 0
#endif


const string NUM_REGEX = "[0-9]+";
const string FLOAT_REGEX = "[0-9]*\.?[0-9]+";

int _tempPatternListIndex = 0;

%% machine foo;
%% write data;

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;

	cs = foo_start;
	totalLength = strlen(p);
	
	char *eof;
	if (!MINIMAL) {
		printf("Input is %s \n",p);
	}
	vector<int> temp_numbersInPattern;
	printf("cs is %d and foo_start is %d\n", cs, foo_start);

	%%{
		
		action CHUNK {
			//Invoked for each event
			// cout << "Element -> " << (char) fc << endl;
            currentLength++;
        }

        action EVENT {
			//Invoked for every event-character match
			printf("\tEvent =%c \n",fc);
			
        }
		
		action TRACK_EVENT_TIME {
			//Invoked for every time-character match and which needs to be tracked
			printf("\tTime-Character =%c \n",fc);
			
		}
		
		action IGNORE_TRACK_EVENT_TIME {
			//Invoked for every time-character match and which need NOT to be tracked
			printf("\tNon-Tracking Time-Character =%c \n",fc);
			
		}
		
		action DELIMITERS {
			//Invoked for every delimiter-character match
			printf("\tDelimiter-Character =%c \n",fc);
		}
		
        action NUM {
            // if (fc >= 48 && fc <= 57) {
                printf("\tNum =%c \n",fc);
            // }
        }
		
		action ACCEPT {
			//Accepting state
			printf("Finally accepted\n");
			
            cs = foo_start; // Move to start state
			
		}
		
        action ERR {
			printf("Error happened.\n");
			printf("\tcurrent processing character =%c \n",fc);
			
			cs = foo_start; // Move to start state
			printf("cs is %d and foo_start is %d\n", cs, foo_start);
			printf("Resetting state (and probably would check with first state)\n");
			// printf("Resetting state (and move forward)\n");
			// p++;

            if (currentLength >= totalLength) {
                // Force break... very bad practice
				cout << "Trying to break "<< endl;
                fbreak;
            }
        }
    
		FLOAT_REGEX = /[0-9]*\.?[0-9]+/;
		NUM = [0-9]+;
		EVENTREP = [a-z]+;
		delimiters = [,|] <to(DELIMITERS);
		eventSection = ((delimiters)(NUM <to(TRACK_EVENT_TIME))(delimiters)(lower <to(EVENT)));
		numberSection = ((delimiters)(NUM <to(IGNORE_TRACK_EVENT_TIME))(delimiters)(NUM <to(NUM)));
		
		main := ((eventSection numberSection eventSection) $to(CHUNK) %to(ACCEPT) $lerr(ERR));

		write init nocs;
		write exec noend;
	}%%

	cout << "Finished processing \n\n";
}


int main( int argc, char **argv )
{
	// char *inp;
	char *inp = (char *)malloc(INT_MAX * sizeof(char *));
	if (argc >= 2) {
		inp = argv[1];
	} else {
		// scanf("%s",inp);
		// sprintf(inp, "1,a|1.5,b|2,4|4,7|7,b|10,d|");
		sprintf(inp, "|1,a|2,4|7,b|10,8|4,7|15,b|8,9|32,c|");
		// sprintf(inp, "1,a|1.5,b|2,4|4,7|7,b|10,d|");
		// sprintf(inp, "1,a|2,4|");
	}
	
	mine_pattern(inp);
	return 0;
}

/*Input 
1,a|1.5,b|2,4|4,7|7,b|10,d|
*/
