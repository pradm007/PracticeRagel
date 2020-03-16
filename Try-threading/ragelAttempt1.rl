
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

const string numberListPattern = "[0-9]+";
unordered_map<string, vector<vector<int> > > patternMap;

%% machine foo;
%% write data;

string getString(char ch) { 
	string temp = "";
    return "" + ch;    
} 

void insertIntoTempPatternList(vector<string>  &tempPatternList, char element, int where) {
	switch(where) {
		case 0:
			if (tempPatternList.empty()) { //completely empty. This happens in the first match
				string temp = "";
				temp.push_back((char) element);
				tempPatternList.push_back(temp);
			} else {
				tempPatternList[where].push_back((char) element);
			}

		break;
		case 1:
			if (tempPatternList.size() == where) { //no new element in the 2nd index
				string temp = "";
				temp.push_back((char) element);
				tempPatternList.push_back(temp);
			} else {
				tempPatternList[where].push_back((char) element);
			}

		break;
	};
}

void insertIntoPatternList(unordered_map<string, vector<vector<int> > > &patternMap, vector<string>  &tempPatternList, vector<vector<int> > &numberList) {
	string fullPattern = "";

	for (int i=0;i<tempPatternList.size();i++) {
		fullPattern += tempPatternList[i];
		if (tempPatternList.size()-1 > i) {
			fullPattern += numberListPattern;
		}
	}

	vector<vector<int> >  newNumberList = numberList;

	const bool is_in = patternMap.find(fullPattern) != patternMap.end();
	if (is_in) {
		if (!MINIMAL) {
			cout << "Found " << fullPattern << endl;
		}
		auto itr = patternMap.find(fullPattern);
		vector<vector<int> >  oldNumberList = itr->second;
		oldNumberList.reserve(oldNumberList.size() + newNumberList.size());
		for (int j=0;j<newNumberList.size();j++) {
			oldNumberList.push_back(newNumberList[j]);
		}
		patternMap[itr->first] = oldNumberList;
	} else {
		if (!MINIMAL) {
			cout << "Did not find " << fullPattern << " thus inserting new " << endl;
		}
		patternMap.emplace(fullPattern, newNumberList);
	}

}

void resetPatternList(vector<string> &tempPatternList, int *_tempPatternListIndex) {
	*_tempPatternListIndex = 0;
	tempPatternList.clear();
	tempPatternList.reserve(100);
}

void displayPatternList(unordered_map<string, vector<vector<int> > > &patternMap) {
	for (auto itr = patternMap.begin(); itr != patternMap.end(); itr++) {
		string pattern = "" + (string) itr->first;
		cout << pattern << " :\n";
		vector<vector<int> > numberList = itr->second;	
		for (int i =0; i < numberList.size(); i++) {
			printf("\tList %d : \n\t\t\t", i+1);
			for (int j=0;j<numberList[i].size(); j++) {
				printf("%d ",numberList[i][j]);
			}
			printf("\n");
		}

	}
}


void mergeList(unordered_map<string, vector<vector<int> > > patternMapInternal) {
	for (auto itr = patternMapInternal.begin(); itr != patternMapInternal.end(); itr++) {
		const bool is_in = patternMap.find((string) itr->first) != patternMap.end();
		if (is_in) { //Existing pattern
			auto itr_int = patternMap.find((string) itr->first);
			vector<vector<int> >  oldNumberList = itr_int->second;
			((vector<vector<int> >) itr->second).reserve(((vector<vector<int> >) itr->second).size() + oldNumberList.size());
			for (int i=0; i<oldNumberList.size();i++) {
				((vector<vector<int> >) itr->second).push_back(oldNumberList[i]);
			}
		} else { //Insert new pattern
			patternMap.emplace((string) itr->first, ((vector<vector<int> >) itr->second));
		}
	}
}

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	vector<string> tempPatternList;
	int _tempPatternListIndex = 0;
	tempPatternList.reserve(100);

	unordered_map<string, vector<vector<int> > > patternMapInternal;

	cs = foo_start;
	totalLength = strlen(p);
	char *eof;
	if (!MINIMAL) {
		printf("Input is %s \n",p);
	}
	vector<int> temp_numbersInPattern;
	numberList.reserve(100);
	temp_numbersInPattern.reserve(100);
	numbersInPattern.reserve(200);

	if (!MINIMAL) {
		printf("cs is %d and foo_start is %d\n", cs, foo_start);
	}

	%%{
		
		action CHUNK {
            if (DEBUG) {
                cout << "Element -> " << (char) fc << endl;
            }
            currentLength++;
			if (fc >= 97 && fc <= 122) {
				insertIntoTempPatternList(tempPatternList, (char) fc, _tempPatternListIndex);
			}
        }

        action A {
            res++;
			if (!MINIMAL) {
            	printf("Match happened.\n");
			}
            for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
                if (DEBUG) {
                    cout << temp_numbersInPattern[i] << " ~ ";
                }
                numbersInPattern.push_back(temp_numbersInPattern[i]);
            }
            if (DEBUG) {
                printf("\n");
            }
            numberList.push_back(numbersInPattern);
			// #pragma omp critical
			// {
			// 	insertIntoPatternList(patternMap, tempPatternList, numberList);
			// }
			insertIntoPatternList(patternMapInternal, tempPatternList, numberList);

			resetPatternList(tempPatternList, &_tempPatternListIndex);
			numberList.clear();
            numbersInPattern.clear();
            temp_numbersInPattern.clear();
			temp_numbersInPattern.reserve(100);
			numbersInPattern.reserve(200);
			numberList.reserve(100);

            cs = foo_start;
            p--;
        }
        action NUM {
            // printf("fc =%c \n",fc);
            if (fc >= 48 && fc <= 57) {
                // printf("	Num =%c \n",fc);
                temp_numbersInPattern.push_back( (char) (fc-48));
				_tempPatternListIndex = 1;
            }
        }
		action NUM_NOTRACK {
            // printf("fc =%c \n",fc);
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

			numberList.clear();
            temp_numbersInPattern.clear();
			resetPatternList(tempPatternList, &_tempPatternListIndex);
			temp_numbersInPattern.reserve(100);
			numbersInPattern.reserve(200);
			numberList.reserve(100);

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

	cout << "Finished processing \n\n";
	
	if (DEBUG) {
		cout << "Displaying internal pattern map per thread" << endl;
		displayPatternList(patternMapInternal);
	}


	printf("For Thread %d \t", omp_get_thread_num());
	printf("Pattern matched %d times\n", res);

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

int THREAD_COUNT = 80;
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
	#pragma omp parallel for num_threads(THREAD_COUNT) shared(patternMap, inputStream_per_thread) firstprivate(numberListPattern)
	for (int i=0;i<THREAD_COUNT;i++) {
		// cout << "Thread " << i << endl << "initiatng ... " << endl;
		// cout << "Input is " << inputStream_per_thread[i].c_str() << endl;
		char inpPerThChar[inputStream_per_thread[i].size() + 1]; 
		strcpy(inpPerThChar, inputStream_per_thread[i].c_str());
		mine_pattern(inpPerThChar);
	}

	cout << "Size of pattern Map " << patternMap.size() << endl;
	// displayPatternList(patternMap);

	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished in %.6f ms. \n", t);
}