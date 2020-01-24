
#line 1 "sample.rl"

#include <bits/stdc++.h>
using namespace std;
#define DEBUG 1


#line 7 "sample.rl"

#line 12 "sample111.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 2, 
	0, 1
};

static const char _foo_key_offsets[] = {
	0, 0, 2, 4, 8
};

static const char _foo_trans_keys[] = {
	97, 100, 48, 57, 48, 57, 97, 100, 
	97, 100, 0
};

static const char _foo_single_lengths[] = {
	0, 0, 0, 0, 0
};

static const char _foo_range_lengths[] = {
	0, 1, 1, 2, 1
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


#line 8 "sample.rl"

void mine_pattern(char *p) {
	int cs, res = 0;
	int totalLength = 0, currentLength = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	// char *p = (char *)malloc(INT_MAX * sizeof(char *));
	// if (argc >= 2) {
	// 	p = argv[1];
	// } else {
	// 	scanf("%s",p);
	// }
	cs = foo_start;
	totalLength = strlen(p);
	char *eof;
	printf("Input is %s \n",p);
	vector<int> temp_numbersInPattern;
	printf("cs is %d and foo_start is %d\n", cs, foo_start);

	
#line 92 "sample111.cpp"
	{
	}

#line 96 "sample111.cpp"
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
#line 50 "sample.rl"
	{
			// printf("fc =%c \n",fc);
			if ((*p) >= 48 && (*p) <= 57) {
				// printf("\tNum =%c \n",fc);
				temp_numbersInPattern.push_back( (char) ((*p)-48));
			}
		}
	break;
#line 121 "sample111.cpp"
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
#line 57 "sample.rl"
	{
			// res = 0;
			printf("Error happened.\n");
			cs = foo_start;
			printf("cs is %d and foo_start is %d\n", cs, foo_start);
			printf("currentLength is %d and totalLength is %d\n", currentLength, totalLength);

			temp_numbersInPattern.clear();
			if (currentLength >= totalLength) {
				// Force break... very bad practice
				cout << "Trying to break "<< endl;
				{p++; goto _out; }
			}
			// fgoto main;
			
		}
	break;
#line 205 "sample111.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 29 "sample.rl"
	{
			cout << "Element -> " << (char) (*p) << endl;
			currentLength++;
		}
	break;
	case 1:
#line 34 "sample.rl"
	{
			res++;
			printf("ACTUAL Match happened.\n");
			if (DEBUG) {
				for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
					cout << temp_numbersInPattern[i] << " ~ ";
					numbersInPattern.push_back(temp_numbersInPattern[i]);
				}
				cout << endl;
				numberList.push_back(numbersInPattern);
				numbersInPattern.clear();
				temp_numbersInPattern.clear();
			}
			cs = foo_start;
			p--;
		}
	break;
#line 240 "sample111.cpp"
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
#line 57 "sample.rl"
	{
			// res = 0;
			printf("Error happened.\n");
			cs = foo_start;
			printf("cs is %d and foo_start is %d\n", cs, foo_start);
			printf("currentLength is %d and totalLength is %d\n", currentLength, totalLength);

			temp_numbersInPattern.clear();
			if (currentLength >= totalLength) {
				// Force break... very bad practice
				cout << "Trying to break "<< endl;
				{p++; goto _out; }
			}
			// fgoto main;
			
		}
	break;
#line 273 "sample111.cpp"
		}
	}
	}

	_out: {}
	}

#line 86 "sample.rl"


	cout << "Finished processing \n\n";
	


	printf("Pattern matched %d times\n", res);
	if (DEBUG) {
		cout << "Numbers in the list are " << endl;
		for (int i =0; i < numberList.size(); i++) {
			cout << "List " << i+1 << " : " << endl;
			for (int j=0;j<numberList[i].size(); j++) {
				cout << numberList[i][j] << " ";
			}
			cout << endl;
		}
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
