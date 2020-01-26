
#include <bits/stdc++.h>
using namespace std;
#define DEBUG 1


const string numberListPattern = "[0-9]+";
int _tempPatternListIndex = 0;

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

void insertIntoPatternList(map<string, vector<vector<int> > > &patternMap, vector<string>  &tempPatternList, vector<vector<int> > &numberList) {
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
		cout << "Found " << fullPattern << endl;
		auto itr = patternMap.find(fullPattern);
		vector<vector<int> >  oldNumberList = itr->second;
		for (int j=0;j<newNumberList.size();j++) {
			oldNumberList.push_back(newNumberList[j]);
		}
		patternMap[itr->first] = oldNumberList;
	} else {
		cout << "Did not find " << fullPattern << " thus inserting new " << endl;
		patternMap.emplace(fullPattern, newNumberList);
	}

}

void resetPatternList(vector<string> &tempPatternList) {
	_tempPatternListIndex = 0;
	tempPatternList.clear();
}

void displayPatternList(map<string, vector<vector<int> > > &patternMap) {
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

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	vector<string> tempPatternList;

	map<string, vector<vector<int> > > patternMap;

	cs = foo_start;
	totalLength = strlen(p);
	char *eof;
	printf("Input is %s \n",p);
	vector<int> temp_numbersInPattern;
	printf("cs is %d and foo_start is %d\n", cs, foo_start);

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
            printf("Match happened.\n");
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
			insertIntoPatternList(patternMap, tempPatternList, numberList);
			resetPatternList(tempPatternList);
			numberList.clear();
            numbersInPattern.clear();
            temp_numbersInPattern.clear();

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
			resetPatternList(tempPatternList);

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                fbreak;
            }
        }
    

		#pattern1 = ((('ab'([0-9]+ $from(NUM))'cd')) $to(CHUNK) %to(A) $lerr(E));
		#pattern2 = ((('ab'([0-9]+ $from(NUM))'ef')) $to(CHUNK) %to(A) $lerr(E));
		#pattern3 = ((('cd'([0-9]+ $from(NUM))'ef')) $to(CHUNK) %to(A) $lerr(E));
		#pat1 = ((('ab'([0-9]+)'cd') | ('cd'([0-9]+)'ef'))+) $to(CHUNK) %to(A) $lerr(E);
		#main := (pattern1 | pattern2 | pattern3)+;
		#main := ((('ab'([0-9]+ $from(NUM))'cd') | ('ab'([0-9]+ $from(NUM))'ef') | ('cd'([0-9]+ $from(NUM))'ef'))+) $to(CHUNK) %to(A) $lerr(E);
		#main := ((('a'([0-9]+ $from(NUM))'a') | ('a'([0-9]+ $from(NUM))'b') | ('a'([0-9]+ $from(NUM))'c') | ('a'([0-9]+ $from(NUM))'d') | ('b'([0-9]+ $from(NUM))'a') | ('b'([0-9]+ $from(NUM))'b') | ('b'([0-9]+ $from(NUM))'c') | ('b'([0-9]+ $from(NUM))'d') | ('c'([0-9]+ $from(NUM))'a') | ('c'([0-9]+ $from(NUM))'b') | ('c'([0-9]+ $from(NUM))'c') | ('c'([0-9]+ $from(NUM))'d') | ('d'([0-9]+ $from(NUM))'a') | ('d'([0-9]+ $from(NUM))'b') | ('d'([0-9]+ $from(NUM))'c') | ('d'([0-9]+ $from(NUM))'d'))+)$to(CHUNK) %to(A) $lerr(E);
		#main := pat1;
        main := ((('a'([0-9]+ $from(NUM))'b'([0-9]+ $from(NUM_NOTRACK))'c') | ('b'([0-9]+ $from(NUM))'c') | ('d'([0-9]+ $from(NUM_NOTRACK))'e'([0-9]+ $from(NUM))'a') | ('c'([0-9]+ $from(NUM))'d'([0-9]+ $from(NUM_NOTRACK))'e'))+)$to(CHUNK) %to(A) $lerr(E);

		write init nocs;
		write exec noend;
	}%%

	cout << "Finished processing \n\n";
	


	printf("Pattern matched %d times\n", res);
	if (DEBUG) {
		displayPatternList(patternMap);
		// if (numberList.size() > 0) {
		// 	printf("Numbers in the list are \n");
		// 	for (int i =0; i < numberList.size(); i++) {
		// 		printf("List %d : \n", i+1);
		// 		for (int j=0;j<numberList[i].size(); j++) {
		// 			printf("%d ",numberList[i][j]);
		// 		}
		// 		printf("\n");
		// 	}
    	// }



	}

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
