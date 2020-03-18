
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

const string numberListPattern = "[0-9]+";
unordered_map<string, vector<vector<string> > > patternMap;

int g_reserveSize = 1e+4;
int g_totalCombination = 4;


#line 28 "ragelAttempt1.rl"

#line 33 "build/ragelAttemp1.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 2, 
	0, 1
};

static const char _foo_key_offsets[] = {
	0, 0, 1, 3, 7
};

static const char _foo_trans_keys[] = {
	97, 48, 57, 48, 57, 97, 100, 97, 
	0
};

static const char _foo_single_lengths[] = {
	0, 1, 0, 0, 1
};

static const char _foo_range_lengths[] = {
	0, 0, 1, 2, 0
};

static const char _foo_index_offsets[] = {
	0, 0, 2, 4, 7
};

static const char _foo_indicies[] = {
	1, 0, 2, 0, 2, 3, 0, 1, 
	0, 0
};

static const char _foo_trans_targs[] = {
	0, 2, 3, 4
};

static const char _foo_trans_actions[] = {
	5, 0, 0, 0
};

static const char _foo_to_state_actions[] = {
	0, 1, 1, 1, 7
};

static const char _foo_from_state_actions[] = {
	0, 0, 3, 3, 0
};

static const char _foo_eof_actions[] = {
	0, 5, 5, 5, 0
};

static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 29 "ragelAttempt1.rl"

string getString(char ch) { 
	string temp = "";
    return "" + ch;    
} 

void insertIntoTempPatternList(string  &tempPatternList, char element, int *flipperOnEvent, vector<string> *numberList) {
	if ((element >= 97 && element <= 122) ) { //its event
		tempPatternList += element;
		*flipperOnEvent = 1;
	} else { //its a number
		if ((char) tempPatternList[tempPatternList.size() - 1] != (char) numberListPattern[numberListPattern.size() - 1]) {
			tempPatternList += numberListPattern;
		}
		if (*flipperOnEvent == 1) {
			//Add new vector for number tracing
			numberList->push_back("");
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

		newNumberList->reserve(10000);
		newNumberList->push_back(*numberList);
		patternMap.emplace(fullPattern, *newNumberList);
	}

}

void resetPatternList(string &tempPatternList) {
	tempPatternList.clear();
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
			// oldNumberList.reserve(10000);
			// *oldNumberList.reserve(10000);

			for (int i=0; i<pMapInternalValue.size();i++) {
				oldNumberList->push_back(pMapInternalValue[i]);
			}
			// cout << "---------" << endl;
			// displayPatternList_Internal(oldNumberList);
			// cout << "---------" << endl;

		} else { //Insert new pattern

			// vector<vector<string> >  newNumberList;// = new vector<vector<string> >;
			int reserveSize = g_reserveSize > pMapInternalValue.size() ? g_reserveSize : pMapInternalValue.size();
			vector<vector<string> >  *newNumberList = new vector<vector<string> >;
			newNumberList->reserve(reserveSize);

			// #pragma omp parallel for
			for (int i=0; i<pMapInternalValue.size(); i++) {
				// newNumberList.push_back( pMapInternalValue.at(i) );
				newNumberList->push_back( pMapInternalValue.at(i) );
			}

			// patternMap.emplace((string) itr->first,  newNumberList);
			patternMap.emplace((string) itr->first,  *newNumberList);
		}

		// free(pMapInternalValue);
	}
}

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	string numbersInPattern;
	vector<string > *numberList = new vector<string>(10);	
	string tempPatternList;

	int flipperOnEvent = 1; // flips to 0 in case of number

	unordered_map<string, vector<vector<string> > > patternMapInternal;

	cs = foo_start;
	totalLength = strlen(p);
	char *eof;
	if (!MINIMAL) {
		printf("Input is %s \n",p);
	}
	// numberList.reserve(100);

	if (!MINIMAL) {
		printf("cs is %d and foo_start is %d\n", cs, foo_start);
	}

	
#line 236 "build/ragelAttemp1.cpp"
	{
	}

#line 240 "build/ragelAttemp1.cpp"
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
#line 202 "ragelAttempt1.rl"
	{
            if ((*p) >= 48 && (*p) <= 57) {
				if (flipperOnEvent == 1) { //Flipper added just to be safe
					//Add new vector for number tracing
					numberList->push_back("");
					flipperOnEvent = 0;
				}

				numberList->at(numberList->size() - 1) = numberList->at(numberList->size() - 1) + (char) (*p);
            }
        }
	break;
#line 269 "build/ragelAttemp1.cpp"
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
#line 220 "ragelAttempt1.rl"
	{
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

			// numberList.clear();
			numberList = new vector<string>(10);
			resetPatternList(tempPatternList);

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                {p++; goto _out; }
            }
        }
	break;
#line 359 "build/ragelAttemp1.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 173 "ragelAttempt1.rl"
	{
            if (DEBUG) {
                cout << "Element -> " << (char) (*p) << endl;
            }
			if (!MINIMAL) {
				cout << "Chunk called " << endl;
			}
            currentLength++;
			if (((*p) >= 97 && (*p) <= 122) || ((*p) >= 48 && (*p) <= 57)) {
				insertIntoTempPatternList(tempPatternList, (char) (*p), &flipperOnEvent, numberList);
			}
        }
	break;
	case 1:
#line 186 "ragelAttempt1.rl"
	{
            res++;
			if (!MINIMAL) {
            	printf("Match happened.\n");
			}

			insertIntoPatternList(patternMapInternal, tempPatternList, numberList);

			resetPatternList(tempPatternList);

			// numberList.clear();
			numberList = new vector<string>(10);

            cs = foo_start;
            p--;
        }
	break;
#line 402 "build/ragelAttemp1.cpp"
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
#line 220 "ragelAttempt1.rl"
	{
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

			// numberList.clear();
			numberList = new vector<string>(10);
			resetPatternList(tempPatternList);

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                {p++; goto _out; }
            }
        }
	break;
#line 441 "build/ragelAttemp1.cpp"
		}
	}
	}

	_out: {}
	}

#line 248 "ragelAttempt1.rl"


	if (!MINIMAL_2)	{
		cout << "Finished processing \n\n";
	}
	
	if (DEBUG || 0) {
		cout << "Displaying internal pattern map per thread" << endl;
		// #pragma omp critical
		// displayPatternList(patternMapInternal);
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

int THREAD_COUNT = 4;
const char delimiter = '|';
vector<string> inputStream_per_thread;
void chunkDivider(char *inp);
void initializeInputStreamPerThread();
void serialeExecution(char *);
void parallelExecution(char *);

int main( int argc, char **argv )
{
	char *input;
	if (FILEINPUT) {
		ifstream myfile("../Benchmark/Synthetic/trace3.txt");
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

	// cout << "For Serial " << endl;
	// serialeExecution(input);
	// cout << endl;

	patternMap.clear();

	cout << "For Parallel " << endl;
	parallelExecution(input);
	cout << endl;

	return 0;
}

void chunkDivider(char *inp) {
	int currentIndex = 0, currentThreadIndex = 0;
	int isNumber = 0;
	initializeInputStreamPerThread();
	while (inp[currentIndex] != '\0') {
		if (inp[currentIndex] >= 48 && inp[currentIndex] <= 57) { //is a number
			isNumber = 1;
			inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
		} else { //is event
			if (isNumber == 1) { // need to start feed to different thread chunk
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
				inputStream_per_thread[currentThreadIndex] += delimiter;

				currentThreadIndex = (currentThreadIndex + 1) % THREAD_COUNT;
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
			} else {
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
			}
			isNumber = 0;
		}
		currentIndex++;
	}
}

void initializeInputStreamPerThread() {
	for (int i=0;i<THREAD_COUNT;i++) {
		string inpPerTh = "";
		inputStream_per_thread.push_back(inpPerTh);
	}
}

void serialeExecution(char *inp) {

  	double t = omp_get_wtime();
	#pragma omp parallel num_threads(1)
	{
		mine_pattern(inp);
	}

	cout << "Size of pattern Map " << patternMap.size() << endl;
	// displayPatternList(patternMap);

	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished in %.6f ms. \n", t);
}

void parallelExecution(char *inp) {
	
	double t;

	cout << "Initiating chunk division" << endl;
	t = omp_get_wtime();
	chunkDivider(inp);
	printf("Finished chunk division in %.6f ms. \n", (1000 * (omp_get_wtime() - t)));

	t = omp_get_wtime();
	#pragma omp parallel for num_threads(THREAD_COUNT) shared(patternMap, inputStream_per_thread) firstprivate(numberListPattern, g_reserveSize, g_totalCombination)
	for (int i=0;i<THREAD_COUNT;i++) {
		// cout << "Thread " << i << endl << "initiatng ... " << endl;
		// cout << "Input is " << inputStream_per_thread[i].c_str() << endl;
		// char inpPerThChar[inputStream_per_thread[i].size() + 1]; 
		char *inpPerThChar = (char *) malloc(sizeof(char)*(inputStream_per_thread[i].size() + 1)); 
		strcpy(inpPerThChar, inputStream_per_thread[i].c_str());
		mine_pattern(inpPerThChar);
	}

	cout << "Size of pattern Map " << patternMap.size() << endl;
	// displayPatternList(patternMap);

	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished in %.6f ms. \n", t);
}
