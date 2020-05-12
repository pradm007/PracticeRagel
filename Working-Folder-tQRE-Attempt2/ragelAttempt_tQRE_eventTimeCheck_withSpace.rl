
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

vector<string> inputEM_array, inputTime_array;
int tokenCounter = -1;

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

int getEventTime(int tokenCounter) {
	return stoi(inputTime_array[tokenCounter]);
}

/**
* @param input Input string to be splited
* @param isTimeOrEM Int value represent 1 for EM, 2 for Time , rest - Error
*/
void stringToStringArray(char *char_input, int isTimeOrEM=0) {
	string input(char_input);
	stringstream ssin(input);
    
    while(ssin.good()) {
		string _token;
        ssin >> _token;
		if (isTimeOrEM == 1) {
			inputEM_array.push_back(_token);
		} else if (isTimeOrEM == 2) {
			inputTime_array.push_back(_token);
		}
    }
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

void mine_pattern(char *inputEM, char *inputTime) {
	int cs, res = 0;
	char* p = inputEM;
	
	int totalLength = 0, currentLength = 0;

	cs = foo_start;
	totalLength = strlen(inputEM);
	
	char *eof;
	if (!MINIMAL) {
		printf("Input EM %s \n",inputEM);
		printf("Input Time %s \n",inputTime);
	}
	
	stringToStringArray(inputEM, 1);
	stringToStringArray(inputTime, 2);
	
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
			tokenCounter++; //Increase everytime there is an E/M
			
			_eventTime = getEventTime(tokenCounter);
			
			//Calculate and insertEventTime for this event
			if (_has_event_entered == 0) {
				processingEventTime[currentTRECount][0] = _eventTime;
				_has_event_entered++;
			}
			previousEventTime = _eventTime;
			
			_eventTime = 0;
        }
		
		action EVENT_EXIT {
			_eventTime = getEventTime(tokenCounter);
			
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
		
        action EVENT_IDENTITY {
			//Will only be invoked in case of events such as a01 or b02 where 01,02 would be the event identity
			printf("\tEvent Identity =%c \n",fc);
		}
		
		
		action DELIMITERS {
			//Invoked for every delimiter-character match
			printf("\tDelimiter-Character =%c \n",fc);
			
		}
		
        action NUM {
            if (fc >= 48 && fc <= 57) {
                printf("\tNum =%c \n",fc);
				tokenCounter++; //Increase everytime there is an E/M
				
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
		delimiters = space <to(DELIMITERS);
		subeventSection = ((delimiters)((lower) <to(EVENT) )([0-9]{0} <to(EVENT_IDENTITY)));
		
		eventSection = (subeventSection %from(EVENT_EXIT));
		numberSection = ((delimiters)(NUM <to(NUM)));
		
		
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
	char *inputEM = (char *)malloc(INT_MAX * sizeof(char *));
	char *inputTime = (char *)malloc(INT_MAX * sizeof(char *));
	// if (argc >= 2) { //Invalid for now due to the format we are taking input
	// 	inputEM = argv[1];
	// 	inputEM = argv[2];
	// } else {
		sprintf(inputEM, " a b c 4 5 b d 2 1 "); // 3-2event in TRE - WORKS with larger event identity
		// sprintf(inputEM, " a11 b32 c31 4 5 b11 d01 2 1 "); // 3-2event in TRE - WORKS
		sprintf(inputTime, " 1 15 19 20 23 27 30 45 51 "); // 3-2event in TRE - WORKS
	// }
	
	mine_pattern(inputEM, inputTime);
	return 0;
}
