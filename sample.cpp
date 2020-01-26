
#line 1 "sample.rl"

#include <bits/stdc++.h>
using namespace std;
#define DEBUG 1


const string numberListPattern = "[0-9]+";
int _tempPatternListIndex = 0;


#line 11 "sample.rl"

#line 16 "sample.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 1, 
	4, 2, 0, 1
};

static const char _foo_key_offsets[] = {
	0, 0, 4, 6, 9, 11, 14, 16, 
	19, 21, 24, 26, 29, 31, 34
};

static const char _foo_trans_keys[] = {
	97, 98, 99, 100, 48, 57, 98, 48, 
	57, 48, 57, 99, 48, 57, 48, 57, 
	100, 48, 57, 48, 57, 101, 48, 57, 
	48, 57, 101, 48, 57, 48, 57, 97, 
	48, 57, 97, 98, 99, 100, 0
};

static const char _foo_single_lengths[] = {
	0, 4, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 4
};

static const char _foo_range_lengths[] = {
	0, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 0
};

static const char _foo_index_offsets[] = {
	0, 0, 5, 7, 10, 12, 15, 17, 
	20, 22, 25, 27, 30, 32, 35
};

static const char _foo_indicies[] = {
	1, 2, 3, 4, 0, 5, 0, 6, 
	5, 0, 7, 0, 6, 7, 0, 8, 
	0, 9, 8, 0, 10, 0, 6, 10, 
	0, 11, 0, 12, 11, 0, 13, 0, 
	6, 13, 0, 1, 2, 3, 4, 0, 
	0
};

static const char _foo_trans_targs[] = {
	0, 2, 4, 6, 10, 3, 14, 5, 
	7, 8, 9, 11, 12, 13
};

static const char _foo_trans_actions[] = {
	7, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const char _foo_to_state_actions[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 9
};

static const char _foo_from_state_actions[] = {
	0, 0, 3, 3, 3, 3, 3, 3, 
	5, 5, 5, 5, 3, 3, 0
};

static const char _foo_eof_actions[] = {
	0, 7, 7, 7, 7, 7, 7, 7, 
	7, 7, 7, 7, 7, 7, 0
};

static const int foo_start = 1;
static const int foo_first_final = 14;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 12 "sample.rl"

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

	
#line 189 "sample.cpp"
	{
	}

#line 193 "sample.cpp"
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
#line 142 "sample.rl"
	{
            // printf("fc =%c \n",fc);
            if ((*p) >= 48 && (*p) <= 57) {
                // printf("	Num =%c \n",fc);
                temp_numbersInPattern.push_back( (char) ((*p)-48));
				_tempPatternListIndex = 1;
            }
        }
	break;
	case 3:
#line 150 "sample.rl"
	{
            // printf("fc =%c \n",fc);
            if ((*p) >= 48 && (*p) <= 57) {
                // printf("Skipping Num =%c \n",fc);
                // temp_numbersInPattern.push_back( (char) (fc-48));
				// _tempPatternListIndex = 1;
            }
        }
	break;
#line 230 "sample.cpp"
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
	case 4:
#line 158 "sample.rl"
	{
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
                {p++; goto _out; }
            }
        }
	break;
#line 320 "sample.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 110 "sample.rl"
	{
            if (DEBUG) {
                cout << "Element -> " << (char) (*p) << endl;
            }
            currentLength++;
			if ((*p) >= 97 && (*p) <= 122) {
				insertIntoTempPatternList(tempPatternList, (char) (*p), _tempPatternListIndex);
			}
        }
	break;
	case 1:
#line 120 "sample.rl"
	{
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
	break;
#line 366 "sample.cpp"
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
	case 4:
#line 158 "sample.rl"
	{
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
                {p++; goto _out; }
            }
        }
	break;
#line 405 "sample.cpp"
		}
	}
	}

	_out: {}
	}

#line 194 "sample.rl"


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
