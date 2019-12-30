
#line 1 "sample.rl"

#include <bits/stdc++.h>
using namespace std;
// #include <stdio.h>
// #include <string.h>


#line 8 "sample.rl"

#line 13 "sample.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 1, 1, 2
};

static const char _foo_key_offsets[] = {
	0, 0, 1, 2, 4, 7, 8
};

static const char _foo_trans_keys[] = {
	97, 98, 48, 57, 99, 48, 57, 100, 
	97, 0
};

static const char _foo_single_lengths[] = {
	0, 1, 1, 0, 1, 1, 1
};

static const char _foo_range_lengths[] = {
	0, 0, 0, 1, 1, 0, 0
};

static const char _foo_index_offsets[] = {
	0, 0, 2, 4, 6, 9, 11
};

static const char _foo_trans_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 4, 
	0, 6, 0, 2, 0, 0
};

static const char _foo_trans_actions[] = {
	0, 0, 0, 5, 0, 5, 0, 0, 
	5, 0, 5, 0, 5, 0
};

static const char _foo_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 1
};

static const char _foo_from_state_actions[] = {
	0, 0, 0, 3, 3, 0, 0
};

static const char _foo_eof_actions[] = {
	0, 0, 5, 5, 5, 5, 0
};

static const int foo_start = 1;
static const int foo_first_final = 6;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 9 "sample.rl"
int main( int argc, char **argv )
{
	int cs, res = 0;
	vector<int> numbersInPattern;
	vector<vector<int> > numberList;	
	if ( argc > 1 ) {
		char *p = argv[1];
		char *eof = p + strlen(p);
		printf("Input is %s \n",p);
		vector<int> temp_numbersInPattern;
		
#line 80 "sample.cpp"
	{
	cs = foo_start;
	}

#line 85 "sample.cpp"
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
#line 32 "sample.rl"
	{
				// printf("fc =%c \n",fc);
				if ((*p) >= 48 && (*p) <= 57) {
					// printf("\tNum =%c \n",fc);
					temp_numbersInPattern.push_back( (char) ((*p)-48));
				}
			}
	break;
#line 110 "sample.cpp"
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
#line 39 "sample.rl"
	{
				// res = 0;
				// printf("Error happened.\n");
				cs = foo_start;
				temp_numbersInPattern.clear();
			}
	break;
#line 183 "sample.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 20 "sample.rl"
	{
				res++;
				// printf("Match happened.\n");
				for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
					// cout << temp_numbersInPattern[i] << " ~ ";
					numbersInPattern.push_back(temp_numbersInPattern[i]);
				}
				cout << endl;
				numberList.push_back(numbersInPattern);
				numbersInPattern.clear();
				temp_numbersInPattern.clear();
			}
	break;
#line 207 "sample.cpp"
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
#line 39 "sample.rl"
	{
				// res = 0;
				// printf("Error happened.\n");
				cs = foo_start;
				temp_numbersInPattern.clear();
			}
	break;
#line 230 "sample.cpp"
		}
	}
	}

	_out: {}
	}

#line 48 "sample.rl"

	}
	// printf("input is %s\n", argv[1]);
	printf("Pattern matched %d times\n", res);
	cout << "Numbers in the list are " << endl;
	for (int i =0; i < numberList.size(); i++) {
		cout << "List " << i+1 << " : " << endl;
		for (int j=0;j<numberList[i].size(); j++) {
			cout << numberList[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}
