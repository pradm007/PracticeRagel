
#line 1 "practice.rl"

#include <bits/stdc++.h>
using namespace std;
#define DEBUG 1


#line 7 "practice.rl"

#line 12 "practice.cpp"
static const char _foo_actions[] = {
	0, 1, 0
};

static const char _foo_key_offsets[] = {
	0, 0, 1, 3, 4, 5, 6, 7
};

static const char _foo_trans_keys[] = {
	97, 97, 98, 98, 96, 32, 96, 0
};

static const char _foo_single_lengths[] = {
	0, 1, 2, 1, 1, 1, 1, 0
};

static const char _foo_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0
};

static const char _foo_index_offsets[] = {
	0, 0, 2, 5, 7, 9, 11, 13
};

static const char _foo_trans_targs[] = {
	2, 0, 3, 2, 0, 4, 0, 5, 
	0, 6, 0, 7, 0, 0, 0
};

static const char _foo_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 0, 0, 0
};

static const int foo_start = 1;
static const int foo_first_final = 7;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 8 "practice.rl"

void mine_pattern(char *p) {
	int cs = foo_start;
	char *eof;
	
	
#line 61 "practice.cpp"
	{
	cs = foo_start;
	}

#line 66 "practice.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( cs == 0 )
		goto _out;
_resume:
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
	case 0:
#line 15 "practice.rl"
	{
			printf("Match happened.\n");
        }
	break;
#line 143 "practice.cpp"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	p += 1;
	goto _resume;
	_out: {}
	}

#line 27 "practice.rl"

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
