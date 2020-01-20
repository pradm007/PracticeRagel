
#line 1 "sample2.rl"

#include <bits/stdc++.h>
using namespace std;


#line 6 "sample2.rl"

#line 11 "sample2.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 1, 1, 2
};

static const char _foo_key_offsets[] = {
	0, 0, 1, 3, 6
};

static const char _foo_trans_keys[] = {
	97, 48, 57, 98, 48, 57, 97, 0
};

static const char _foo_single_lengths[] = {
	0, 1, 0, 1, 1
};

static const char _foo_range_lengths[] = {
	0, 0, 1, 1, 0
};

static const char _foo_index_offsets[] = {
	0, 0, 2, 4, 7
};

static const char _foo_trans_targs[] = {
	2, 0, 3, 0, 4, 3, 0, 2, 
	0, 0
};

static const char _foo_trans_actions[] = {
	0, 0, 0, 5, 0, 0, 5, 0, 
	5, 0
};

static const char _foo_to_state_actions[] = {
	0, 0, 0, 0, 1
};

static const char _foo_from_state_actions[] = {
	0, 0, 3, 3, 0
};

static const char _foo_eof_actions[] = {
	0, 0, 5, 5, 0
};

static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 7 "sample2.rl"
int main( int argc, char **argv )
{
	int cs, res = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	if ( argc > 1 ) {
		printf("\tInside actual mining. Mining starts now for pattern lookup.\n");
		char* p = argv[1];//"a12b43a321b";

		vector<int> numbersInPattern;
		vector<vector<int> > numberList;	
		int cs, res = 0;
		char *eof = p + strlen(p);
		printf("Input is %s \n",p);
		
		vector<int> temp_numbersInPattern;

		
#line 84 "sample2.cpp"
	{
	cs = foo_start;
	}

#line 89 "sample2.cpp"
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
	case 1:
#line 38 "sample2.rl"
	{
				printf("fc =%c \n",(*p));
				if ((*p) >= 48 && (*p) <= 57) {
					// printf("	Num =%c \n",fc);
					temp_numbersInPattern.push_back( (char) ((*p)-48));
				}
			}
	break;
#line 114 "sample2.cpp"
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
	cs = _foo_trans_targs[_trans];

	if ( _foo_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _foo_actions + _foo_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 45 "sample2.rl"
	{
				res = 0;
				printf("Error happened.\n");
				cs = foo_start;
				temp_numbersInPattern.clear();
			}
	break;
#line 187 "sample2.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 26 "sample2.rl"
	{
				res++;
				printf("Match happened.\n");
				for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
					cout << temp_numbersInPattern[i] << " ~ ";
					numbersInPattern.push_back(temp_numbersInPattern[i]);
				}
				printf("\n");
				numberList.push_back(numbersInPattern);
				numbersInPattern.clear();
				temp_numbersInPattern.clear();
			}
	break;
#line 211 "sample2.cpp"
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
	case 2:
#line 45 "sample2.rl"
	{
				res = 0;
				printf("Error happened.\n");
				cs = foo_start;
				temp_numbersInPattern.clear();
			}
	break;
#line 234 "sample2.cpp"
		}
	}
	}

	_out: {}
	}

#line 55 "sample2.rl"


		printf("Pattern matched %d times\n", res);
		if (res > 0) {
			printf("Numbers in the list are \n");
			for (int i =0; i < numberList.size(); i++) {
				printf("List %d : \n", i+1);
				for (int j=0;j<numberList[i].size(); j++) {
					printf("%d ",numberList[i][j]);
				}
				printf("\n");
			}
		}
		
	}


	// // printf("input is %s\n", argv[1]);
	// printf("Pattern matched %d times\n", res);
	// cout << "Numbers in the list are " << endl;
	// for (int i =0; i < numberList.size(); i++) {
	// 	cout << "List " << i+1 << " : " << endl;
	// 	for (int j=0;j<numberList[i].size(); j++) {
	// 		cout << numberList[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }


	return 0;
}
