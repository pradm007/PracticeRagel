
#line 1 "ragelAttempt1.rl"

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef MINIMAL
#define MINIMAL 0
#endif

#ifndef FILEINPUT
#define FILEINPUT 0
#endif

#ifndef MINIMAL_2
#define MINIMAL_2 0
#endif

#ifndef DISPLAY_MAP
#define DISPLAY_MAP 0
#endif

const string numberListPattern = "[0-9]+";
unordered_map<string, vector<vector<string> > > patternMap;

int g_reserveSize = 1e+7;
const int CHUNK_DELIMITER_SIZE = 1e+5;
int g_delimiterCount = 0;
int g_totalCombination = 10;
int THREAD_COUNT = 16;
const char delimiter = '|';
vector<string> inputStream_per_thread;
int eventRepresentationLength = 1;


void chunkDivider_singular(char *inp, int, int);
void showChunks();
void serialeExecution(char *);
void parallelExecution(char *);
void chunkDivider(char *, int , int);
void releaseMemory(vector<vector<string> > &);


#line 47 "ragelAttempt1.rl"

#line 52 "build/ragelAttemp1.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 2, 
	0, 1
};

static const char _foo_key_offsets[] = {
	0, 0, 1, 3, 6, 8, 11, 13, 
	16, 18, 21, 23, 26, 28, 31
};

static const char _foo_trans_keys[] = {
	97, 48, 57, 98, 48, 57, 48, 57, 
	99, 48, 57, 48, 57, 100, 48, 57, 
	48, 57, 101, 48, 57, 48, 57, 102, 
	48, 57, 48, 57, 103, 48, 57, 97, 
	0
};

static const char _foo_single_lengths[] = {
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 1
};

static const char _foo_range_lengths[] = {
	0, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 0
};

static const char _foo_index_offsets[] = {
	0, 0, 2, 4, 7, 9, 12, 14, 
	17, 19, 22, 24, 27, 29, 32
};

static const char _foo_indicies[] = {
	1, 0, 2, 0, 3, 2, 0, 4, 
	0, 5, 4, 0, 6, 0, 7, 6, 
	0, 8, 0, 9, 8, 0, 10, 0, 
	11, 10, 0, 12, 0, 13, 12, 0, 
	1, 0, 0
};

static const char _foo_trans_targs[] = {
	0, 2, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14
};

static const char _foo_trans_actions[] = {
	5, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const char _foo_to_state_actions[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 7
};

static const char _foo_from_state_actions[] = {
	0, 0, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 0
};

static const char _foo_eof_actions[] = {
	0, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 0
};

static const int foo_start = 1;
static const int foo_first_final = 14;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 48 "ragelAttempt1.rl"

void insertIntoTempPatternList(string  &tempPatternList, char element, int *flipperOnEvent, int *currentEventRepresentationLength, vector<string> *numberList) {
	
	// cout << "insertIntoTempPatternList for element " << (char)element << " currentEventRepresentationLength = " << *currentEventRepresentationLength << endl;
		
	if ((element >= 97 && element <= 122) || (element >= 48 && element <= 57 && *currentEventRepresentationLength < eventRepresentationLength)) { //its event or its a number bbut needs to be considered as event
	
		if (element >= 97 && element <= 122) { //Set the event length to 1. DO NOT do this before this as it would be only correct to start event length check after matching the first alphabetical event character
			*currentEventRepresentationLength = 0;
			numberList->push_back(","); //Add new vector for number tracing
		}

		tempPatternList += element;
		*flipperOnEvent = 1;
		(*currentEventRepresentationLength)++;
	} else { //its a number
		if ((char) tempPatternList[tempPatternList.size() - 1] != (char) numberListPattern[numberListPattern.size() - 1]) {
			tempPatternList += numberListPattern;
			// tempPatternList.push_back(numberListPattern);
		}
		*flipperOnEvent = 0;
	}
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

void resetPatternList(string &tempPatternList, int* currentEventRepresentationLength) {
	tempPatternList.clear();
	*currentEventRepresentationLength = 0;
}

string removeComma(string &input) {
	string output;
	for(int i=0;i<input.size();i++) {
		if (input[i] != ',') {
			output += input[i];
		}
	}

	return output;
}

void loopAndPresentData(string &patternKey, vector<vector<string> > &numberList, string &regexPattern) {
	vector<string> patternKeyMap;
	int currentIndex = 0, bracketStart = 0;

	if (DEBUG) {
		cout << " patternKey " << patternKey << endl;
	}

	//This breaks the pattern key into sub elements
	while(patternKey[currentIndex] != '\0') {
		if (patternKey[currentIndex] != '[' && bracketStart == 0) {
			if (patternKeyMap.empty()) {
				string element (1, patternKey.at(currentIndex));
				patternKeyMap.push_back(element);

			} else {
				int size = patternKeyMap.size();
				patternKeyMap[size-1] += (char) patternKey.at(currentIndex);
			}
		} else {
			//everything after the bracket for number mining starts
			if (patternKey[currentIndex] == '[') {
				bracketStart = 1;
				patternKeyMap.push_back("");
			} else if (patternKey[currentIndex] >= 97 && patternKey[currentIndex] <= 122) {
				bracketStart = 0;
				currentIndex--;
			}
		}
		currentIndex++;

	}

	if (DEBUG) {
		cout << "Partition done " << endl;
		for (int i=0;i<patternKeyMap.size();i++) {
			cout << patternKeyMap[i] << " ";
		}
		cout << endl;
	}
	
	try {
		vector<vector<double>> numberListInDouble;
		for (int i =0; i < numberList.size(); i++) {
				// printf("\tList %d : \n\t\t\t", i+1);
				int start = 0;
				string fullMatchedPattern;

				for (int j=0;j<numberList[i].size(); j++) {
					string numberIs = removeComma(numberList[i][j]);

					if ( numberIs.size() > 0) {

						if (start < patternKeyMap.size()) {
							fullMatchedPattern += patternKeyMap[start++];
						}
						fullMatchedPattern += numberIs;
					}
				}

				if (start < patternKeyMap.size()) { //flush the remainning, there should be only 1 pattern left at max
					fullMatchedPattern += patternKeyMap[start++];
				}

				if (regex_match(fullMatchedPattern, regex(regexPattern)) ) {
					if (DEBUG) {
						cout << "Matched with " << regexPattern << endl;
					}
					vector<double> *innerList = new vector<double>;
					for (int j=0;j<numberList[i].size(); j++) {
						string innerNumber = removeComma(numberList[i][j]);
						if (innerNumber.size() > 0) {
							cout << "innerNumber " << innerNumber << endl;
							innerList->push_back(stod(innerNumber));
						}
					}
					numberListInDouble.push_back(*innerList);
				} else {
					if (DEBUG) {
						cout << "Not matched with " << regexPattern << endl;
					}
				}

		}

		cout << "Inner pattern match completed. Total matches found : " << numberListInDouble.size() << endl;
		if (numberListInDouble.size() > 0) {
			int innerSize = numberListInDouble[0].size();
			for (int j=0;j<innerSize;j++) {
				long double MU = 0;
				long double VAR = 0;
				for (int i=0;i<numberListInDouble.size();i++) {
					MU += (numberListInDouble[i][j] / numberListInDouble.size());
				}

				for (int i=0;i<numberListInDouble.size();i++) {
					VAR += ( pow( (MU - numberListInDouble[i][j]) , 2) / numberListInDouble.size());
				}

				cout << "For placeholder at " << j+1 << " : " << endl;
				cout << "\t Mean " << MU << endl;
				cout << "\t Variance " << VAR << endl;
				cout << endl;
			}
		}

	} catch(exception& err) {
		cout << " a standard exception was caught, with message '" << err.what() << "'\n";
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
		/* for (int i =0; i < numberList.size(); i++) {
			printf("\tList %d : \n\t\t\t", i+1);
			for (int j=0;j<numberList[i].size(); j++) {
				cout << numberList[i][j];
			}
			printf("\n");
		} */
		displayPatternList_Internal(numberList);
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

	}
}

void releaseMemory(vector<vector<string> > &outVec) {
	vector<vector<string> >().swap(outVec);
}

void chunkDivider_singular(char *inp, int quantPlaceholderCount=1) {
	int currentIndex = 0, currentThreadIndex = inputStream_per_thread.size() - 1;
	int currentQuantCount = 0;
	int currentEventRepresentationLength = 0;
	int isNumber = 0;

	while (inp[currentIndex] != '\0') {
		// cout << "At currentIndex " << currentIndex << " currentEventRepresentationLength is " << currentEventRepresentationLength << endl;
		if (inp[currentIndex] >= 48 && inp[currentIndex] <= 57) { //is a number
			if (isNumber == 0 && currentEventRepresentationLength < eventRepresentationLength) {
				currentEventRepresentationLength++;
			} else if (isNumber == 0) { //Count quant only once for 
				currentQuantCount++;
				isNumber = 1;
				currentEventRepresentationLength = 0;
			} else {
				currentEventRepresentationLength = 0;
			}

			inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
		} else { //is event
			currentEventRepresentationLength++;

			if (isNumber == 1) { // need to start feed to different thread chunk
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];


				//when to apply delimited
				if (currentQuantCount == quantPlaceholderCount) {
					// cout << "About to add delimiter currentEventRepresentationLength " << currentEventRepresentationLength << endl;
					if (currentEventRepresentationLength < eventRepresentationLength) {
						//Go till the end of the event representation, then do a break.
						int innerCurrentIndex = currentIndex + 1;

						while(inp[innerCurrentIndex] != '\0' && currentEventRepresentationLength < eventRepresentationLength) {
							inputStream_per_thread[currentThreadIndex] += inp[innerCurrentIndex];
							currentEventRepresentationLength++;
							innerCurrentIndex++;
						}
						currentEventRepresentationLength= 0;//reset to zero for a new beginning
					}

					inputStream_per_thread[currentThreadIndex] += delimiter;
					g_delimiterCount++;

					if (g_delimiterCount == CHUNK_DELIMITER_SIZE) { // start division for next chunk
						currentThreadIndex = currentThreadIndex + 1;
						g_delimiterCount = 0;
						if (inp[currentIndex+1] != '\0') {
							inputStream_per_thread.push_back("");
						}
					}

					inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
					currentEventRepresentationLength++;//increment again for new count after the delimiter

					currentQuantCount = 0;
				}

			} else {
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
			}
			isNumber = 0;
		}
		// cout << "[END] At currentIndex " << currentIndex << " currentEventRepresentationLength is " << currentEventRepresentationLength << endl;
		currentIndex++;

	}

	//Chop off the excess... iterate from the back
	int last = inputStream_per_thread[currentThreadIndex].size() - 1;
	while ((char)inputStream_per_thread[currentThreadIndex][last] != delimiter) {
		last--;
	}
	inputStream_per_thread[currentThreadIndex] = inputStream_per_thread[currentThreadIndex].substr(0, last+1);
}

void chunkDivider(char *inp, int quantPlaceholderCount) {

	inputStream_per_thread.push_back("");

	for (int i=0;i<quantPlaceholderCount;i++) {
		//Identify starting marker
		char *startingMarker = inp;
		int currentEventCount = 0, isEvent = 0;
		int currentIndex = 0;

		while(startingMarker[currentIndex] != '\0') {
			if (startingMarker[currentIndex] >= 48 && startingMarker[currentIndex] <= 57) { //is a number
				if (isEvent == 1) {
					isEvent = 0;
				}
			} else {
				if (isEvent == 0) {
					isEvent = 1;
					currentEventCount++;
				}
			}

			if (currentEventCount == (i+1) ) {
				break;//Use the current marker 
			}

			currentIndex++;
		}

		chunkDivider_singular(&startingMarker[currentIndex], quantPlaceholderCount);
	}
}


void showChunks() {
	for (int i=0;i<inputStream_per_thread.size();i++) {
		cout << "Chunk " << (i+1) << " ~~~ " << inputStream_per_thread[i] <<endl;
	}
}

void writeToCSV(unordered_map<string, vector<vector<string> > > &patternMap) {
	ofstream csvFile;
	csvFile.open("./build/mine-map.csv");
	csvFile << "Pattern,Numbers\n";
	for (auto itr = patternMap.begin(); itr != patternMap.end(); itr++) {
		string pattern = "" + (string) itr->first;


		vector<vector<string> > numberList = itr->second;	
		csvFile<<pattern<<endl;
		for (int i =0; i < numberList.size(); i++) {
			string tracedNumber="";
			for (int j=0;j<numberList[i].size(); j++) {
				tracedNumber += numberList[i][j];
				// stringstream checkLine(tracedNumber);

				// string newRepresentation = " ";
				// string smallerChunk;
				// while(getline(checkLine, smallerChunk, ' '))
				// {
				// 	if (!newRepresentation.empty()) {
				// 		newRepresentation += ",";
				// 	}
				// 	newRepresentation += smallerChunk;
				// }
				// newRepresentation += "\n";
				// csvFile << newRepresentation;
			}
			if (!tracedNumber.empty()) {
				tracedNumber += "\n";
				csvFile << tracedNumber;
			}
		}
	}
}

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	string numbersInPattern;
	vector<string > *numberList = new vector<string>;	
	string tempPatternList;
	tempPatternList.reserve(5);

	int currentEventRepresentationLength = 0;
	int flipperOnEvent = 1; // flips to 0 in case of number

	unordered_map<string, vector<vector<string> > > patternMapInternal;

	cs = foo_start;
	totalLength = strlen(p);
	char *eof;
	if (!MINIMAL) {
		printf("Input is %s \n",p);
	}

	if (!MINIMAL) {
		printf("cs is %d and foo_start is %d\n", cs, foo_start);
	}

	
#line 544 "build/ragelAttemp1.cpp"
	{
	}

#line 548 "build/ragelAttemp1.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _foo_actions + _foo_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 2:
#line 494 "ragelAttempt1.rl"
	{
            if ((*p) >= 48 && (*p) <= 57) {
				// if (flipperOnEvent == 1) { //Flipper added just to be safe
				// 	//Add new vector for number tracing
				// 	numberList->push_back(" ");
				// 	flipperOnEvent = 0;
				// }
				if (numberList->empty()) {
					numberList->push_back(",");
				}

				numberList->at(numberList->size() - 1) = numberList->at(numberList->size() - 1) + (char) (*p);
            }
        }
	break;
#line 580 "build/ragelAttemp1.cpp"
		}
	}

	_keys = _foo_trans_keys + _foo_key_offsets[cs];
	_trans = _foo_index_offsets[cs];

	_klen = _foo_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _foo_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _foo_indicies[_trans];
	cs = _foo_trans_targs[_trans];

	if ( _foo_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _foo_actions + _foo_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 3:
#line 515 "ragelAttempt1.rl"
	{
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

			numberList = new vector<string>;
			resetPatternList(tempPatternList, &currentEventRepresentationLength);

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                {p++; goto _out; }
            }
        }
	break;
#line 669 "build/ragelAttemp1.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 466 "ragelAttempt1.rl"
	{
            if (DEBUG) {
                cout << "Element -> " << (char) (*p) << endl;
            }
			if (!MINIMAL) {
				cout << "Chunk called " << endl;
			}
            currentLength++;
			if (((*p) >= 97 && (*p) <= 122) || ((*p) >= 48 && (*p) <= 57)) {
				insertIntoTempPatternList(tempPatternList, (char) (*p), &flipperOnEvent, &currentEventRepresentationLength, numberList);
			}
        }
	break;
	case 1:
#line 479 "ragelAttempt1.rl"
	{
            res++;
			if (!MINIMAL) {
            	printf("Match happened.\n");
			}

			insertIntoPatternList(patternMapInternal, tempPatternList, numberList);

			resetPatternList(tempPatternList, &currentEventRepresentationLength);

			numberList = new vector<string>;

            cs = foo_start;
            p--;
        }
	break;
#line 711 "build/ragelAttemp1.cpp"
		}
	}

	if ( cs == 0 )
		goto _out;
	p += 1;
	goto _resume;
	if ( p == eof )
	{
	const char *__acts = _foo_actions + _foo_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 3:
#line 515 "ragelAttempt1.rl"
	{
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

			numberList = new vector<string>;
			resetPatternList(tempPatternList, &currentEventRepresentationLength);

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                {p++; goto _out; }
            }
        }
	break;
#line 749 "build/ragelAttemp1.cpp"
		}
	}
	}

	_out: {}
	}

#line 544 "ragelAttempt1.rl"


	if (!MINIMAL_2)	{
		cout << "Finished processing \n\n";
	}
	
	if (DEBUG || 0) {
		cout << "Displaying internal pattern map per thread" << endl;
		// #pragma omp critical
		displayPatternList(patternMapInternal);
	}

	if (!MINIMAL_2) {
		printf("For Thread %d \t", omp_get_thread_num());
		printf("Pattern matched %d times\n", res);
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

int willingToQuit(string &input) {
	return input.length() == 1 && (char) input[0] == 'N';
}

/**
 * Function for parallel Execution
 **/
void parallelExecution(char *inp) {
	
	double t;

	if (DEBUG) {
		cout << "Initiating chunk division" << endl;
	}
	t = omp_get_wtime();
	eventRepresentationLength = 9;
	chunkDivider(inp,1);
	if (DEBUG) {
		printf("Finished chunk division in %.6f ms. \n", (1000 * (omp_get_wtime() - t)));
	}

	t = omp_get_wtime();
	if (DEBUG || 0) {
		showChunks();
	}

	#pragma omp parallel for num_threads(THREAD_COUNT) shared(patternMap, inputStream_per_thread) firstprivate(numberListPattern, g_reserveSize, g_totalCombination)
	for (int i=0;i<inputStream_per_thread.size();i++) {

		string chunkForThread = inputStream_per_thread[i];
		char *inpPerThChar = (char *) malloc(sizeof(char)*(chunkForThread.size() + 1)); 
		strcpy(inpPerThChar, chunkForThread.c_str());
		mine_pattern(inpPerThChar);
		free(inpPerThChar);
		chunkForThread.clear();
		chunkForThread.shrink_to_fit();
	}

	if (DISPLAY_MAP) {
		cout << "Size of pattern Map " << patternMap.size() << endl;
		displayPatternList(patternMap);
	}
	writeToCSV(patternMap);

	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished in %.6f ms using %d threads. \n", t, THREAD_COUNT);

	int quit = 0;
	string inputString = "";
	// while(!quit) {
	// 	cout << "Enter pattern that you are interested with specific event symbol (Enter N to quit) : ";
	// 	inputString = "a[0-9]+b";
	// 	// cin >> inputString;
	// 	if (willingToQuit(inputString)) {
	// 		cout << "Exiting..." << endl;
	// 		break;
	// 	}

	// 	auto itr = patternMap.find(inputString);
	// 	const bool is_in = itr != patternMap.end();
	// 	if (is_in) {
	// 		string inputString2 = "a[0-9]+b";
	// 		cout << "Enter interested regex (Enter N to quit) : " ;
	// 		// cin >> inputString2;
	// 		if (willingToQuit(inputString2)) {
	// 			cout << "Exiting..." << endl;
	// 			break;
	// 		}

	// 		vector<vector<string> > numberList = itr->second;
	// 		loopAndPresentData(inputString, numberList, inputString2);

	// 		cout << "Enter N to quit, anything else to continue : ";
	// 		cin >> inputString2;
	// 		if (willingToQuit(inputString2)) {
	// 			cout << "Exiting..." << endl;
	// 			break;
	// 		}
	// 	} else {
	// 		cout << "Pattern not found. Try again " << endl;
	// 	}
	// }

}

int main( int argc, char **argv )
{
	char *input;
	if (FILEINPUT) {
		// ifstream myfile("../Benchmark/Synthetic/trace7.txt");
		ifstream myfile("../DataSet/Arrythmia/arrhythmia_cleaned.data");
		string inp;
		if (myfile.is_open()) {
		while (getline(myfile, inp)) {
			// cout << line << '\n';
		}
		myfile.close();
		}
		input = (char *)malloc((inp.size() + 1) * sizeof(char *));
		g_reserveSize = (inp.size() + 1) / g_totalCombination;
		strcpy(input, inp.c_str());
	} else if (argc >= 2) {
		input = argv[1];
	} else {
		input = (char *)malloc(INT_MAX * sizeof(char *));
		scanf("%s",input);
	}

	patternMap.clear();

	cout << "For Parallel " << endl;
	parallelExecution(input);
	cout << endl;

	return 0;
}