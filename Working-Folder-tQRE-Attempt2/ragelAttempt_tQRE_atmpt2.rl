
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef MINIMAL
#define MINIMAL 1
#endif

#ifndef MINIMAL_2
#define MINIMAL_2 1
#endif

#ifndef DISPLAY_MAP
#define DISPLAY_MAP 1
#endif

const string NUM_REGEX = "[0-9]+";
const string FLOAT_REGEX = "[0-9]*\.?[0-9]+";

int is_faulty=0;
vector<string> faultReason;;

//Input Event Time
int eventTRE_perInstance = 2;
// int inputEventTime[2][2] = {{0,20},{2,5}};
// int inputQuantTime[1][2] = {{0,10}};
int inputEventTime[2][2] = {{0,100},{0,100}};
int inputQuantTime[1][2] = {{0,100}};

int processingEventTime[2][2] = {{0,0},{0,0}}; // This stores entry and exit for each TRE event scope

vector<string> inputEM_array, inputTime_array;
int tokenCounter = 0;
unordered_map<string, vector<vector<string> > > patternMap; //Global shared map between threads
int g_reserveSize = 1e+7; //Reserve space for new global unordered Map

int checkForFullAcceptance() {
	//Check time bounds within TREs
	for (int i=0; i<eventTRE_perInstance; i++) {
		for (int j=0; j<2; j++) {
			int time_diff = processingEventTime[i][1] - processingEventTime[i][0];
			if (! (inputEventTime[i][0] <= time_diff && time_diff <= inputEventTime[i][1]) ) {
            	if (DEBUG) {
					cout << "Time diff did not match for TRE"<<i<<endl;
				}
				return 0; // ERROR IN SCOPE
			}
		}
	}
	
	//Check time bounds among TREs
	for (int i=0; i<eventTRE_perInstance-1; i++) {
		for (int j=0; j<2; j++) {
			int time_diff = processingEventTime[i+1][0] - processingEventTime[i][1];
			if (! (inputQuantTime[i][0] <= time_diff && time_diff <= inputQuantTime[i][1]) ) {
				if (DEBUG) {
					cout << "Time diff did not match among TRE"<<i<< " and TRE"<<(i+1)<<endl;
				}
				return 0; // ERROR IN SCOPE
			}
		}
	}
	return 1;
}

int getEventTime(int tokenCounter) {
	/* cout << "tokenCounter " << tokenCounter << endl;
	cout << "inputTime_array.size " << inputTime_array.size() << endl;
	cout << "inputTime_array[tokenCounter] " << inputTime_array[tokenCounter] << endl;
	
	for (int i=0;i<inputTime_array.size();i++) {
		cout << "--"<<inputTime_array[i] << endl;
	} */
	
	return stoi(inputTime_array[tokenCounter]);
}

void insertIntoPatternList(unordered_map<string, vector < vector<string > > > &patternMap, string  &fullPattern, vector<string > *numberList) {

	auto itr = patternMap.find(fullPattern);
	const bool is_in = itr != patternMap.end();
	if (is_in) {
		if (!MINIMAL) {
			cout << "Found " << fullPattern << endl;
		}
		vector<vector<string > > *oldNumberList = &itr->second;
		oldNumberList->push_back(*numberList);
	} else {
		if (!MINIMAL) {
			cout << "Did not find " << fullPattern << " thus inserting new " << endl;
		}
		vector<vector<string> > *newNumberList = new vector<vector<string> >;

		// newNumberList->reserve(10000);
		newNumberList->push_back(*numberList);
		patternMap.emplace(fullPattern, *newNumberList);
	}

}

void displayPatternList_Internal(vector<vector<string> > &numberList) {
	for (int i =0; i < numberList.size(); i++) {
			printf("\tList %d : \n\t\t\t", i+1);
			for (int j=0;j<numberList[i].size(); j++) {
				cout << numberList[i][j];
			}
			printf("\n");
		}
}

void displayPatternList(unordered_map<string, vector<vector<string> > > &patternMap) {
	for (auto itr = patternMap.begin(); itr != patternMap.end(); itr++) {
		
		string pattern = "" + (string) itr->first;
		cout << pattern << " :\n";
		vector<vector<string> > numberList = itr->second;	
		displayPatternList_Internal(numberList);
		cout << " " << endl;
	}
}

void mergeList(unordered_map<string, vector<vector<string> > > &patternMapInternal) {

	for (auto itr = patternMapInternal.begin(); itr != patternMapInternal.end(); itr++) {
		auto itr_global = patternMap.find((string) itr->first);
		const bool is_in = itr_global != patternMap.end();

		vector<vector<string> > pMapInternalValue = (vector<vector<string> >) itr->second;

		if (is_in) { //Existing pattern
			vector<vector<string> >  *oldNumberList = &itr_global->second;
			
			int oldSize = pMapInternalValue.size();

			for (int i=0; i<pMapInternalValue.size();i++) {
				oldNumberList->push_back(pMapInternalValue[i]);
			}

		} else { //Insert new pattern

			int reserveSize = g_reserveSize > pMapInternalValue.size() ? g_reserveSize : pMapInternalValue.size();
			vector<vector<string> >  *newNumberList = new vector<vector<string> >;
			newNumberList->reserve(reserveSize);

			// #pragma omp parallel for
			for (int i=0; i<pMapInternalValue.size(); i++) {
				newNumberList->push_back( pMapInternalValue.at(i) );
			}

			patternMap.emplace((string) itr->first,  *newNumberList);
		}

		// patternMapInternal.clear();
		// releaseMemory(pMapInternalValue);
		// free(pMapInternalValue);
	}
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
	if (DEBUG) {
		cout << "Processing Event Time --------" << endl;
		for (int i=0; i<eventTRE_perInstance; i++) {
			for (int j=0;j<2;j++) {
				cout << processingEventTime[i][j] << " ";
			}
			cout << endl;
		}
	}
}

%% machine foo;
%% write data;

void mine_pattern(char *inputEM, char *inputTime) {
	int cs, matched = 0;
	char* p = inputEM;
	
	int totalLength = 0, currentLength = 0;
	vector<string > *numberList = new vector<string>;	
	string tempPatternList;
	tempPatternList.reserve(100);
	unordered_map<string, vector<vector<string> > > patternMapInternal;
	
	cs = foo_start;
	totalLength = strlen(inputEM);
	
	char *eof;
	if (!MINIMAL) {
		printf("Input EM %s \n",inputEM);
		printf("Input Time %s \n",inputTime);
	}
	
	stringToStringArray(inputEM, 1);
	stringToStringArray(inputTime, 2);
	
	if (DEBUG) {
		printf("cs is %d and foo_start is %d\n", cs, foo_start);
	}
	
	int previousEventTime=0;
	int _eventTime = 0;
	int _quantValue = 0;
	int currentTRECount = 0;
	int _has_event_entered = 0; // Determines if we enter an event stage in TRE. Gets reset immediately at M stage
	int _event_OR_quant_stage = 0; //Flips between 0 - unknown, 1 - Event, 2 - Quant
	int _event_OR_quant = 0;// Flips between 1 - Event, 2 - Quant
	

	%%{
		
		action CHUNK {
			//Invoked for each event
			// cout << "Element -> " << (char) fc << endl;
            currentLength++;
        }

        action EVENT {
			//Invoked for every event-character match
            if (DEBUG) {
				printf("\tEvent =%c \n",fc);
			}
			// tokenCounter++; //Increase everytime there is an E/M
			_event_OR_quant_stage = 1;
			
			//Get Event Time
			_eventTime = getEventTime(tokenCounter);
			
			//Calculate and insertEventTime for this event
			if (_has_event_entered == 0) {
				processingEventTime[currentTRECount][0] = _eventTime;
				_has_event_entered++;
			}
			previousEventTime = _eventTime;
			
			_eventTime = 0;
			
			//Insert into pattern list
			tempPatternList += (char) fc;
        }
		
		action EVENT_EXIT {
			_event_OR_quant_stage = 1;
			
			//Get Event Time
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
			
		}
		
        action EVENT_IDENTITY {
			//Will only be invoked in case of events such as a01 or b02 where 01,02 would be the event identity
            if (DEBUG) {
				printf("\tEvent Identity =%c \n",fc);
			}
			_event_OR_quant_stage = 1;
			
			
			//Insert into pattern list
			tempPatternList += (char) fc;
		}
		
		
		action DELIMITERS {
			//Invoked for every delimiter-character match
            if (DEBUG) {
				printf("\tDelimiter-Character =%c \n",fc);
			}
			tokenCounter++; //Increase everytime there is an E/M.. now is decided based on space
			
			if (_event_OR_quant_stage == 2) {
				//This would mean, the previous encounter was that of a Quant
				numberList->push_back("");
				numberList->push_back(to_string(_quantValue));
				_quantValue = 0;
			}
			
			if (_event_OR_quant_stage == 1) {
				//Insert into pattern list
				tempPatternList += '.';
			}
			
			if (_event_OR_quant_stage != 0) {
				_event_OR_quant = _event_OR_quant_stage;
				_event_OR_quant_stage = 0;
			}
		}
		
        action NUM {
            if (fc >= 48 && fc <= 57) {
            	if (DEBUG) {
                	printf("\tNum =%c \n",fc);
				}
				// tokenCounter++; //Increase everytime there is an E/M
				_event_OR_quant_stage = 2;
				
				_quantValue = _quantValue*10 + (fc - '0');
				
				if (_has_event_entered != 0) {
					currentTRECount++; //Increment TRE instance counter only if _has_event_entered was true. This takes care of multiple quant fields
					_has_event_entered = 0; //Reset
				}
				_eventTime = 0;
				
				if (_event_OR_quant != 2) {
					//Insert into pattern list
					tempPatternList += "M.";
					_event_OR_quant = 2; //Do only once
				}
            } else {
				is_faulty |= 1;
				faultReason.push_back("INVLD_NMBR");
			}
        }
		
		action ACCEPT {
			//Accepting state
            if (DEBUG) {
				printf("Partially accepted\n");
			}
            matched++;
			
			//Should have hit exit state [NOTE: NOT A GOOD PLACE TO KEEP EVENT EXIT]
			//Calculate and insertEventTime for this event
            if (DEBUG) {
				cout << "_eventTime " << _eventTime << " previousEventTime " << previousEventTime << endl;
			}
			if (_eventTime == 0) { // 
				processingEventTime[currentTRECount][1] = previousEventTime;
			} else {
				//This state should never actually occur.
				processingEventTime[currentTRECount][1] = _eventTime;
				previousEventTime = _eventTime;
			}
			
			printTimeEvent();
			
			//Reset all counters
			previousEventTime=0;
			_eventTime = 0;
			currentTRECount = 0;
			_has_event_entered = 0; // Determines if we enter an event stage in TRE. Gets reset immediately at M stage
			
			int isFullyAccepted = checkForFullAcceptance();
			if (isFullyAccepted) {
				printf("Finally accepted\n");
				//Prune the previous M.
				tempPatternList = tempPatternList.substr(0, tempPatternList.size()-1);
				
				// Insert into the pattern List
				insertIntoPatternList(patternMapInternal, tempPatternList, numberList);
			}

			//Reset more counters
			tempPatternList.clear();
			numberList = new vector<string>;
			
            cs = foo_start; // Move to start state
		}
		
        action ERR {
            if (DEBUG) {
				printf("Error happened.\n");
				printf("\tcurrent processing character =%c \n",fc);
			}
			
			//Reset all counters
			previousEventTime=0;
			_eventTime = 0;
			currentTRECount = 0;
			_has_event_entered = 0; // Determines if we enter an event stage in TRE. Gets reset immediately at M stage
			
			cs = foo_start; // Move to start state
            if (DEBUG) {
				printf("cs is %d and foo_start is %d\n", cs, foo_start);
				printf("Resetting state (and probably would check with first state)\n");
				// printf("Resetting state (and move forward)\n");
			}
			// p++;

			//Reset more counters
			tempPatternList.clear();
			numberList = new vector<string>;
			
            if (currentLength >= totalLength) {
                // Force break... very bad practice
            	if (DEBUG) {
					cout << "Trying to break "<< endl;
				}
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
		
		
		main := ((eventSection+ numberSection+ eventSection+ ' |') $to(CHUNK) %to(ACCEPT) $lerr(ERR));
		#main := ((eventSection eventSection numberSection eventSection eventSection) $to(CHUNK) %to(ACCEPT) $lerr(ERR));

		write init nocs;
		write exec noend;
	}%%

	if (!MINIMAL_2)	{
		cout << "Finished processing \n\n";
	}
	
	if (DEBUG || 0) {
		cout << "Displaying internal pattern map per thread" << endl;
		#pragma omp critical
		displayPatternList(patternMapInternal);
	}
	
	if (!MINIMAL_2) {
		printf("For Thread %d \t", omp_get_thread_num());
		printf("Pattern matched %d times\n", matched);
	}
	
	#pragma omp critical
	{
		if (DEBUG) {
			cout << "Merging internal and external list" << endl;
		}
		mergeList(patternMapInternal);
		if (DEBUG) {
			cout << "Merge finished for Thread " << omp_get_thread_num() << endl;
		}
	}

}

int isDigit(string digitChar_str) {
	
	char digitChar = digitChar_str[0];
	int val = digitChar - '0';
	return val >= 0 && val <= 9;
}

int isSpace(string spaceChar_str) {
	char spaceChar = spaceChar_str[0];
	return spaceChar == 32;
}

int isCharacter(string alphabetChar_str) {
	
	char alphabetChar = alphabetChar_str[0];
	return alphabetChar >= 'a' && alphabetChar <= 'z';
}

vector<string> inputEM_Stream_per_thread, inputTime_Stream_per_thread;
void chunkDivider(string inputEM, string inputTime) {
	int currentThreadIndex = 0;
	int leftPointer = 0, rightPointer = 0;
	inputEM_Stream_per_thread.push_back("");
	inputTime_Stream_per_thread.push_back("");
	
	int is_event_quant_stage = 0; // Flag : 0-space, 1-Event, 2-Quant
	
	int quantCount_perInstance = eventTRE_perInstance; // Taking 1 extra M just to be safe. This would could TRE M TRE as with 2 M so that we cut at TRE M TRE M
	
	int currentQuantCount_forInstance = 0;
	
	vector<string> _private_inputEM_array, _private_inputTime_array;
	stringstream ssinEM(inputEM);
    
    while(ssinEM.good()) {
		string _token;
        ssinEM >> _token;
		_private_inputEM_array.push_back(_token);
    }
	
	stringstream ssinTime(inputTime);
    
    while(ssinTime.good()) {
		string _token;
        ssinTime >> _token;
		_private_inputTime_array.push_back(_token);
    }
	
	cout << "_private_inputEM_array.size() " << _private_inputEM_array.size() << endl;
	cout << "_private_inputTime_array.size() " << _private_inputTime_array.size() << endl;
	
	while(rightPointer < _private_inputEM_array.size()) {
		
		// cout << _private_inputEM_array[rightPointer] << " rightPointer " << rightPointer << endl;
		
		if (isCharacter(_private_inputEM_array[rightPointer])) {
			is_event_quant_stage = 1;
		}
		
		if (rightPointer == (_private_inputEM_array.size()-2)) {
			//Flush the current state
			//We need to substring this chunk and add it to thread pool
			string inputEM_chunk = " " ,inputTime_chunk = " ";
			
			int _lfP = leftPointer;
			while(_lfP <= rightPointer) {
				inputEM_chunk += _private_inputEM_array[_lfP] + " ";
				inputTime_chunk += _private_inputTime_array[_lfP] + " ";
				_lfP++;
			}
			inputEM_chunk += "| "; //To append final delimiter
			inputTime_chunk += "0 "; //To append final delimiter
			
			inputEM_Stream_per_thread.push_back(inputEM_chunk);
			inputTime_Stream_per_thread.push_back(inputTime_chunk);
			
			cout << "Must break now " << endl;
			break;
		}
		
		if (isCharacter(_private_inputEM_array[rightPointer]) && isDigit(_private_inputEM_array[rightPointer + 1])) {
			if (is_event_quant_stage != 2) {
				currentQuantCount_forInstance++;
				is_event_quant_stage = 2;
			}
		}
		
		//Chunk this for a thread
		if (currentQuantCount_forInstance == quantCount_perInstance) {
			//We need to substring this chunk and add it to thread pool
			string inputEM_chunk = " " ,inputTime_chunk = " ";
			
			int _lfP = leftPointer;
			while(_lfP <= rightPointer) {
				inputEM_chunk += _private_inputEM_array[_lfP] + " ";
				inputTime_chunk += _private_inputTime_array[_lfP] + " ";
				_lfP++;
			}
			inputEM_chunk += "| "; //To append final delimiter
			inputTime_chunk += "0 "; //To append final delimiter
			
			inputEM_Stream_per_thread.push_back(inputEM_chunk);
			inputTime_Stream_per_thread.push_back(inputTime_chunk);
			
			//Move the left pointer right-size to the next quant value
			// int _lfP = leftPointer;

			while(leftPointer <= rightPointer) {
				if (isDigit(_private_inputEM_array[leftPointer]) && isCharacter(_private_inputEM_array[leftPointer + 1])) {
					leftPointer = leftPointer + 1; // At space
					currentQuantCount_forInstance--; // Decrement a quantCount
					break;
				}
				leftPointer++;
			}
		}
		
		rightPointer++;
	}
}

void showChunks() {
	for (int i=0;i<inputEM_Stream_per_thread.size();i++) {
		cout << "Chunk " << (i+1) << " ~~~ " << endl;
		cout << "\t\t>>" << inputEM_Stream_per_thread[i] << "<<" << endl;
		cout << "\t\t>>" << inputTime_Stream_per_thread[i] << "<<" << endl;
	}
}

int main( int argc, char **argv )
{
	//Works with 
	 // 3-2event in TRE - WORKS with larger event identity
	 // 3-2event in TRE - WORKS
	  
	string inputEM_string = " a b c 4 5 b d 2 1 e 2 a 2 3 c 2";
	string inputTime_string = " 1 15 19 20 23 27 30 45 51 52 53 54 55 56 58 60";
	
	chunkDivider(inputEM_string, inputTime_string);
	cout << "Showing chunk " << endl;
	if (DEBUG || 1) {
		showChunks();
	}
	
	#pragma omp parallel for num_threads(1) shared(patternMap, inputEM_Stream_per_thread, inputTime_Stream_per_thread) firstprivate(g_reserveSize, inputEM_array, inputTime_array, tokenCounter)
	for (int i=0;i<inputEM_Stream_per_thread.size();i++) {
		
		string _inputEM_string = inputEM_Stream_per_thread[i];
		string _inputTime_string = inputTime_Stream_per_thread[i];
		
		char *_inputEM_char = (char *)malloc(_inputEM_string.size()+1 * sizeof(char *));
		char *_inputTime_char = (char *)malloc(_inputTime_string.size()+1 * sizeof(char *));
		
		strcpy(_inputEM_char, _inputEM_string.c_str());
		strcpy(_inputTime_char, _inputTime_string.c_str());
		
		// cout << _inputEM_char << endl;
		// cout << _inputTime_char << endl;
		//Send char* to minePattern per thread
		mine_pattern(_inputEM_char, _inputTime_char);
	}
	
	cout << "Size of pattern Map " << patternMap.size() << endl;
	if (DISPLAY_MAP) {
		displayPatternList(patternMap);
	}
	
	return 0;
}
