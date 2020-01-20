
#line 1 "try1.rl"

#include <bits/stdc++.h>
using namespace std;
#define DEBUG 2


#line 7 "try1.rl"

#line 12 "try1.cpp"
static const char _foo_actions[] = {
	0, 1, 0, 1, 2, 1, 3, 2, 
	0, 1
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

static const char _foo_indicies[] = {
	1, 0, 2, 0, 3, 2, 0, 1, 
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


#line 8 "try1.rl"
int main( int argc, char **argv )
{
    vector<int> numbersInPattern;
    vector<vector<int> > numberList;	
    int cs, res = 0;
    cs = foo_start;
    char* p = argv[1];
    const char *eof = p + strlen(p);
    printf("Input is %s \n",p);
    
    vector<int> temp_numbersInPattern;

    
#line 84 "try1.cpp"
	{
	}

#line 88 "try1.cpp"
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
#line 40 "try1.rl"
	{
            // printf("fc =%c \n",fc);
            if ((*p) >= 48 && (*p) <= 57) {
                // printf("	Num =%c \n",fc);
                temp_numbersInPattern.push_back( (char) ((*p)-48));
            }
        }
	break;
#line 113 "try1.cpp"
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
#line 47 "try1.rl"
	{
             res = 0;
            printf("Error happened.\n");
            cs = foo_start;
            printf("cs is %d and foo_start is %d\n", cs, foo_start);

            temp_numbersInPattern.clear();

            if ((*p) == 'X') {
					// Force break... very bad practice
					cout << "Trying to break "<< endl;
					{p++; goto _out; }
            }
        }
	break;
#line 195 "try1.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 22 "try1.rl"
	{
            cout << "Element -> " << (char) (*p) << endl;
        }
	break;
	case 1:
#line 26 "try1.rl"
	{
            res++;
            printf("Match happened.\n");
            if (DEBUG == 2) {
                for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
                    cout << temp_numbersInPattern[i] << " ~ ";
                    numbersInPattern.push_back(temp_numbersInPattern[i]);
                }
                cout << endl;
                numberList.push_back(numbersInPattern);
                numbersInPattern.clear();
                temp_numbersInPattern.clear();
            }
        }
	break;
#line 227 "try1.cpp"
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
#line 47 "try1.rl"
	{
             res = 0;
            printf("Error happened.\n");
            cs = foo_start;
            printf("cs is %d and foo_start is %d\n", cs, foo_start);

            temp_numbersInPattern.clear();

            if ((*p) == 'X') {
					// Force break... very bad practice
					cout << "Trying to break "<< endl;
					{p++; goto _out; }
            }
        }
	break;
#line 258 "try1.cpp"
		}
	}
	}

	_out: {}
	}

#line 67 "try1.rl"


    printf("Pattern matched %d times\n", res);
    if (DEBUG == 2) {
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