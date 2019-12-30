
// line 1 "sample.rl"
#include <stdio.h>

// line 3 "sample.rl"

// line 8 "sample.java"
private static byte[] init__foo_actions_0()
{
	return new byte [] {
	    0,    1,    0
	};
}

private static final byte _foo_actions[] = init__foo_actions_0();


private static byte[] init__foo_key_offsets_0()
{
	return new byte [] {
	    0,    0,    2,    5
	};
}

private static final byte _foo_key_offsets[] = init__foo_key_offsets_0();


private static char[] init__foo_trans_keys_0()
{
	return new char [] {
	   97,  122,    3,   97,  122,    0
	};
}

private static final char _foo_trans_keys[] = init__foo_trans_keys_0();


private static byte[] init__foo_single_lengths_0()
{
	return new byte [] {
	    0,    0,    1,    0
	};
}

private static final byte _foo_single_lengths[] = init__foo_single_lengths_0();


private static byte[] init__foo_range_lengths_0()
{
	return new byte [] {
	    0,    1,    1,    0
	};
}

private static final byte _foo_range_lengths[] = init__foo_range_lengths_0();


private static byte[] init__foo_index_offsets_0()
{
	return new byte [] {
	    0,    0,    2,    5
	};
}

private static final byte _foo_index_offsets[] = init__foo_index_offsets_0();


private static byte[] init__foo_trans_targs_0()
{
	return new byte [] {
	    2,    0,    3,    2,    0,    0,    0
	};
}

private static final byte _foo_trans_targs[] = init__foo_trans_targs_0();


private static byte[] init__foo_trans_actions_0()
{
	return new byte [] {
	    0,    0,    1,    0,    0,    0,    0
	};
}

private static final byte _foo_trans_actions[] = init__foo_trans_actions_0();


static final int foo_start = 1;
static final int foo_first_final = 3;
static final int foo_error = 0;

static final int foo_en_main = 1;


// line 4 "sample.rl"
int main( int argc, char **argv )
{
	int cs, res = 0;
	if ( argc > 1 ) {
		char *p = argv[1];
		
// line 103 "sample.java"
	{
	cs = foo_start;
	}

// line 108 "sample.java"
	{
	int _klen;
	int _trans = 0;
	int _acts;
	int _nacts;
	int _keys;
	int _goto_targ = 0;

	_goto: while (true) {
	switch ( _goto_targ ) {
	case 0:
	if ( cs == 0 ) {
		_goto_targ = 5;
		continue _goto;
	}
case 1:
	_match: do {
	_keys = _foo_key_offsets[cs];
	_trans = _foo_index_offsets[cs];
	_klen = _foo_single_lengths[cs];
	if ( _klen > 0 ) {
		int _lower = _keys;
		int _mid;
		int _upper = _keys + _klen - 1;
		while (true) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( data[p] < _foo_trans_keys[_mid] )
				_upper = _mid - 1;
			else if ( data[p] > _foo_trans_keys[_mid] )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				break _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _foo_range_lengths[cs];
	if ( _klen > 0 ) {
		int _lower = _keys;
		int _mid;
		int _upper = _keys + (_klen<<1) - 2;
		while (true) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( data[p] < _foo_trans_keys[_mid] )
				_upper = _mid - 2;
			else if ( data[p] > _foo_trans_keys[_mid+1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				break _match;
			}
		}
		_trans += _klen;
	}
	} while (false);

	cs = _foo_trans_targs[_trans];

	if ( _foo_trans_actions[_trans] != 0 ) {
		_acts = _foo_trans_actions[_trans];
		_nacts = (int) _foo_actions[_acts++];
		while ( _nacts-- > 0 )
	{
			switch ( _foo_actions[_acts++] )
			{
	case 0:
// line 12 "sample.rl"
	{ res = 1; { p += 1; _goto_targ = 5; if (true)  continue _goto;} }
	break;
// line 187 "sample.java"
			}
		}
	}

case 2:
	if ( cs == 0 ) {
		_goto_targ = 5;
		continue _goto;
	}
	p += 1;
	_goto_targ = 1;
	continue _goto;
case 4:
case 5:
	}
	break; }
	}

// line 15 "sample.rl"

	}
	printf("execute = %i\n", res );
	return 0;
}
