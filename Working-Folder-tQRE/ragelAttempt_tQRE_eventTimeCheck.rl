
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

int is_faulty=0;
vector<string> faultReason;;

//Input Event Time
int eventTRE_perInstance = 2;
int inputEventTime[2][2] = {{0,20},{2,5}};
int inputQuantTime[1][2] = {{0,10}};

int processingEventTime[2][2] = {{0,0},{0,0}}; // This stores entry and exit for each TRE event scope

int checkForFullAcceptance() {
	//Check time bounds within TREs
	for (int i=0; i<eventTRE_perInstance; i++) {
		for (int j=0; j<2; j++) {
			int time_diff = processingEventTime[i][1] - processingEventTime[i][0];
			if (! (inputEventTime[i][0] <= time_diff && time_diff <= inputEventTime[i][1]) ) {
				cout << "Time diff did not match for TRE"<<i<<endl;
				return 0; // ERROR IN SCOPE
			}
		}
	}
	
	//Check time bounds among TREs
	for (int i=0; i<eventTRE_perInstance-1; i++) {
		for (int j=0; j<2; j++) {
			int time_diff = processingEventTime[i+1][0] - processingEventTime[i][1];
			if (! (inputQuantTime[i][0] <= time_diff && time_diff <= inputQuantTime[i][1]) ) {
				cout << "Time diff did not match among TRE"<<i<< " and TRE"<<(i+1)<<endl;
				return 0; // ERROR IN SCOPE
			}
		}
	}
	return 1;
}

void printTimeEvent() {
	
	cout << "Processing Event Time --------" << endl;
	for (int i=0; i<eventTRE_perInstance; i++) {
		for (int j=0;j<2;j++) {
			cout << processingEventTime[i][j] << " ";
		}
		cout << endl;
	}
}

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
	printf("cs is %d and foo_start is %d\n", cs, foo_start);
	
	int previousEventTime=0;
	int _eventTime = 0;
	int currentTRECount = 0;
	int _has_event_entered = 0; // Determines if we enter an event stage in TRE. Gets reset immediately at M stage
	

	%%{
		
		action CHUNK {
			//Invoked for each event
			// cout << "Element -> " << (char) fc << endl;
            currentLength++;
        }

        action EVENT {
			//Invoked for every event-character match
			printf("\tEvent =%c \n",fc);
			
			//Calculate and insertEventTime for this event
			if (_has_event_entered == 0) {
				processingEventTime[currentTRECount][0] = _eventTime;
				_has_event_entered++;
			}
			previousEventTime = _eventTime;
			
			_eventTime = 0;
        }
		
		action EVENT_ENTRY {
			//Kind of unnecessary
			//Calculate and insertEventTime for this event
			previousEventTime = _eventTime;
			processingEventTime[currentTRECount][0] = _eventTime;
			
			_eventTime = 0;
		}
		
		action EVENT_EXIT {
			//Can only be understood if it enters a quantitative state BUT problem with last TRE instance as there would not be any quantitative state following
			//Calculate and insertEventTime for this event
			if (_eventTime == 0) { // 
				processingEventTime[currentTRECount][1] = previousEventTime;
			} else {
				//This state should never actually occur.
				processingEventTime[currentTRECount][1] = _eventTime;
				previousEventTime = _eventTime;
			}
			
			_eventTime = 0;
			
			// currentTRECount++; //Increment TRE instance counter
		}
		
		action TRACK_EVENT_TIME {
			//Invoked for every time-character match and which needs to be tracked
			printf("\tTime-Character =%c \n",fc);
			
			//Track event time
			if (fc >= 48 && fc <= 57) {
				_eventTime = _eventTime*10 + (fc - '0');
				cout << "_eventTime " << _eventTime << endl;
			} else {
				is_faulty |= 1;
				faultReason.push_back("INVLD_TIME");
			}
			
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
            if (fc >= 48 && fc <= 57) {
                printf("\tNum =%c \n",fc);
				
				/* //Can only be understood if it enters a quantitative state
				//Calculate and insertEventTime for this event
				previousEventTime = _eventTime;
				processingEventTime[currentTRECount][1] = _eventTime;
				_eventTime = 0;
				
				currentTRECount++; //Increment TRE instance counter */
				
				if (_has_event_entered != 0) {
					currentTRECount++; //Increment TRE instance counter only if _has_event_entered was true. This takes care of multiple quant fields
					_has_event_entered = 0; //Reset
				}
				_eventTime = 0;
				
            } else {
				is_faulty |= 1;
				faultReason.push_back("INVLD_NMBR");
			}
        }
		
		action ACCEPT {
			//Accepting state
			printf("Partially accepted\n");
			
			//Should have hit exit state [NOTE: NOT A GOOD PLACE TO KEEP EVENT EXIT]
			//Calculate and insertEventTime for this event
			cout << "_eventTime " << _eventTime << " previousEventTime " << previousEventTime << endl;
			if (_eventTime == 0) { // 
				processingEventTime[currentTRECount][1] = previousEventTime;
			} else {
				//This state should never actually occur.
				processingEventTime[currentTRECount][1] = _eventTime;
				previousEventTime = _eventTime;
			}
			
            cs = foo_start; // Move to start state
			printTimeEvent();
			
			//Reset all counters
			previousEventTime=0;
			_eventTime = 0;
			currentTRECount = 0;
			_has_event_entered = 0; // Determines if we enter an event stage in TRE. Gets reset immediately at M stage
			
			int isFullyAccepted = checkForFullAcceptance();
			if (isFullyAccepted) {
				printf("Finally accepted\n");
			}
		}
		
        action ERR {
			printf("Error happened.\n");
			printf("\tcurrent processing character =%c \n",fc);
			
			//Reset all counters
			previousEventTime=0;
			_eventTime = 0;
			currentTRECount = 0;
			_has_event_entered = 0; // Determines if we enter an event stage in TRE. Gets reset immediately at M stage
			
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
		subeventSection = ((delimiters)(NUM <to(TRACK_EVENT_TIME))(delimiters)(lower <to(EVENT) ));
		
		eventSection = (subeventSection %from(EVENT_EXIT));
		numberSection = ((delimiters)(NUM <to(IGNORE_TRACK_EVENT_TIME))(delimiters)(NUM <to(NUM)));
		
		
		main := ((eventSection+ numberSection+ eventSection+ numberSection) $to(CHUNK) %to(ACCEPT) $lerr(ERR));
		#main := ((eventSection eventSection numberSection eventSection eventSection) $to(CHUNK) %to(ACCEPT) $lerr(ERR));

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
		// sprintf(inp, "|1,a|1.5,b|2,4|4,7|7,b|10,d|");
		// sprintf(inp, "|1,a|2,4|7,b|10,8|4,7|15,b|8,9|32,c|");
		// sprintf(inp, "|1,a|1.5,b|2,4|4,7|7,b|10,d|");
		// sprintf(inp, "|1,a|15,b|2,4|7,b|10,d|");
		// sprintf(inp, "|1,a|15,b|2,4|7,b|10,d|1,1|"); //2event in TRE
		sprintf(inp, "|1,a|15,b|19,c|20,4|23,5|27,b|30,d|45,2|51,1|"); // 3-2event in TRE - WORKS
		// sprintf(inp, "|1,a|15,b|19,c|2,4|3,5|7,b|10,d|15,c|1,1|"); // 3-3event in TRE = WORKS
		// sprintf(inp, "|1,a|2,4|");
	}
	
	mine_pattern(inp);
	return 0;
}

/*Input 
1,a|1.5,b|2,4|4,7|7,b|10,d|
*/
