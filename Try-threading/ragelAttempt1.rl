
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
int g_totalCombination = 4;

void releaseMemory(vector<vector<string> > &);

%% machine foo;
%% write data;

string getString(char ch) { 
	string temp = "";
    return "" + ch;    
} 

void insertIntoTempPatternList(string  &tempPatternList, char element, int *flipperOnEvent, vector<string> *numberList) {
	if ((element >= 97 && element <= 122) ) { //its event
		tempPatternList += element;
		// tempPatternList.push_back(element);
		*flipperOnEvent = 1;
	} else { //its a number
		if ((char) tempPatternList[tempPatternList.size() - 1] != (char) numberListPattern[numberListPattern.size() - 1]) {
			tempPatternList += numberListPattern;
			// tempPatternList.push_back(numberListPattern);
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

		// newNumberList->reserve(10000);
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

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	string numbersInPattern;
	vector<string > *numberList = new vector<string>;	
	string tempPatternList;
	tempPatternList.reserve(5);

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

	%%{
		
		action CHUNK {
            if (DEBUG) {
                cout << "Element -> " << (char) fc << endl;
            }
			if (!MINIMAL) {
				cout << "Chunk called " << endl;
			}
            currentLength++;
			if ((fc >= 97 && fc <= 122) || (fc >= 48 && fc <= 57)) {
				insertIntoTempPatternList(tempPatternList, (char) fc, &flipperOnEvent, numberList);
			}
        }

        action A {
            res++;
			if (!MINIMAL) {
            	printf("Match happened.\n");
			}

			insertIntoPatternList(patternMapInternal, tempPatternList, numberList);

			resetPatternList(tempPatternList);

			numberList = new vector<string>;

            cs = foo_start;
            p--;
        }
        action NUM {
            if (fc >= 48 && fc <= 57) {
				if (flipperOnEvent == 1) { //Flipper added just to be safe
					//Add new vector for number tracing
					numberList->push_back("");
					flipperOnEvent = 0;
				}

				numberList->at(numberList->size() - 1) = numberList->at(numberList->size() - 1) + (char) fc;
            }
        }
		action NUM_NOTRACK {
            if (fc >= 48 && fc <= 57) {
                // printf("Skipping Num =%c \n",fc);
                // temp_numbersInPattern.push_back( (char) (fc-48));
				// _tempPatternListIndex = 1;
            }
        }
        action E {
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

			numberList = new vector<string>;
			resetPatternList(tempPatternList);

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                fbreak;
            }
        }
    

		main := ((('a'([0-9]+ $from(NUM))'a') | ('a'([0-9]+ $from(NUM))'b') | ('a'([0-9]+ $from(NUM))'c') | ('a'([0-9]+ $from(NUM))'d'))+)$to(CHUNK) %to(A) $lerr(E);

		write init nocs;
		write exec noend;
	}%%

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

void releaseMemory(vector<vector<string> > &outVec) {
	vector<vector<string> >().swap(outVec);
}


int THREAD_COUNT = 4;
const char delimiter = '|';
vector<string> inputStream_per_thread;
void chunkDivider(char *inp);
void showChunks();
void serialeExecution(char *);
void parallelExecution(char *);
void chunkDivider(char *, int );

int main( int argc, char **argv )
{
	char *input;
	if (FILEINPUT) {
		ifstream myfile("../Benchmark/Synthetic/trace4.txt");
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

void chunkDivider_singular(char *inp, int quantPlaceholderCount=1) {
	int currentIndex = 0, currentThreadIndex = inputStream_per_thread.size() - 1;
	int currentQuantCount = 0;
	int isNumber = 0;
	// initializeInputStreamPerThread();
	cout << inp << endl;

	while (inp[currentIndex] != '\0') {
		if (inp[currentIndex] >= 48 && inp[currentIndex] <= 57) { //is a number
			if (isNumber == 0) { //Count quant only once for 
				currentQuantCount++;
			}

			isNumber = 1;
			inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
		} else { //is event
			if (isNumber == 1) { // need to start feed to different thread chunk
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];

				//when to apply delimited
				if (currentQuantCount == quantPlaceholderCount) {
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

					currentQuantCount = 0;
				}

			} else {
				inputStream_per_thread[currentThreadIndex] += inp[currentIndex];
			}
			isNumber = 0;
		}
		currentIndex++;
	}

	//Chop off the excess... iterate from the back
	int last = inputStream_per_thread[currentThreadIndex].size() - 1;
	while ((char)inputStream_per_thread[currentThreadIndex][last] != delimiter) {
		printf("%c ", inputStream_per_thread[currentThreadIndex][last]);
		last--;
	}
	inputStream_per_thread[currentThreadIndex] = inputStream_per_thread[currentThreadIndex].substr(0, last+1);
}

void chunkDivider(char *inp, int quantPlaceholderCount) {
	// int currentIndex = 0, currentThreadIndex = 0;
	// int startingMarker = 0;

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

/**
 * Function for serial execution
 **/
void serialeExecution(char *inp) {

  	double t = omp_get_wtime();
	#pragma omp parallel num_threads(1)
	{
		mine_pattern(inp);
	}

	cout << "Size of pattern Map " << patternMap.size() << endl;
	if (DISPLAY_MAP) {
		displayPatternList(patternMap);
	}

	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished in %.6f ms. \n", t);
}

/**
 * Function for parallel Execution
 **/
void parallelExecution(char *inp) {
	
	double t;

	cout << "Initiating chunk division" << endl;
	t = omp_get_wtime();
	chunkDivider(inp,2);
	printf("Finished chunk division in %.6f ms. \n", (1000 * (omp_get_wtime() - t)));

	t = omp_get_wtime();
	if (DEBUG || 1) {
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

	cout << "Size of pattern Map " << patternMap.size() << endl;
	if (DISPLAY_MAP) {
		displayPatternList(patternMap);
	}

	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished in %.6f ms. \n", t);
}
