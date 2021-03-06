
#line 1 "automaton.rl"
// #include "/home/pradeep/UBC/Projects/QRE/miningQre/TRE_Mining/spec-mining/packrat/lib/x86_64-pc-linux-gnu/3.4.4/automatonR/exec/automaton.h"
#include "automaton.h"

/**
* @file Temporary file. DO NOT MODIFY
*
* @brief Dynamically generated ragel file for specific expression
*
*/

using namespace std;

#line 13 "automaton.rl"

#line 18 "automaton.cpp"
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


#line 14 "automaton.rl"

void ParserAutomaton::mine_pattern(char const *p) {

    if (DEBUG) {
        printf("\tInside actual mining. Mining starts now for pattern lookup.\n");
    }

    // char *p = (char *)malloc(INT_MAX * sizeof(char *));
    // if (DEBUG) {
    //     printf("Enter input string \n");
    // }
    // scanf("%s",&p);
    vector<int> numbersInPattern;
    vector<vector<int> > numberList;	
    int cs, res = 0;
    cs = foo_start;
    int totalLength = 0, currentLength = 0;
    const char *eof;//= p + strlen(p);;
    totalLength = strlen(p);
    //printf("Input is %s \n",p);
    
    vector<int> temp_numbersInPattern;

    
#line 102 "automaton.cpp"
	{
	}

#line 106 "automaton.cpp"
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
#line 65 "automaton.rl"
	{
            // printf("fc =%c \n",fc);
            if ((*p) >= 48 && (*p) <= 57) {
                // printf("	Num =%c \n",fc);
                temp_numbersInPattern.push_back( (char) ((*p)-48));
            }
        }
	break;
#line 131 "automaton.cpp"
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
#line 72 "automaton.rl"
	{
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

            temp_numbersInPattern.clear();

            if (currentLength == totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                {p++; goto _out; }
            }
        }
	break;
#line 219 "automaton.cpp"
		}
	}

_again:
	_acts = _foo_actions + _foo_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 39 "automaton.rl"
	{
            if (DEBUG) {
                cout << "Element -> " << (char) (*p) << endl;
            }
            currentLength++;
        }
	break;
	case 1:
#line 46 "automaton.rl"
	{
            res++;
            // printf("Match happened.\n");
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
            numbersInPattern.clear();
            temp_numbersInPattern.clear();

            cs = foo_start;
            //p--;
        }
	break;
#line 259 "automaton.cpp"
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
#line 72 "automaton.rl"
	{
            //res = 0;
            if (DEBUG) {
                printf("Error happened.\n");
            }
            cs = foo_start;
            if (DEBUG) {
                printf("cs is %d and foo_start is %d\n", cs, foo_start);
            }

            temp_numbersInPattern.clear();

            if (currentLength == totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    cout << "Trying to break "<< endl;
                }
                {p++; goto _out; }
            }
        }
	break;
#line 296 "automaton.cpp"
		}
	}
	}

	_out: {}
	}

#line 97 "automaton.rl"


    printf("Pattern matched %d times\n", res);
    if (numberList.size() > 0) {
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

ParserAutomaton::ParserAutomaton() {
}

ParserAutomaton* createParserAutomaton() {
    ParserAutomaton *p = new ParserAutomaton();
    return p;
}

// //  [[Rcpp::export]]
// Rcpp::XPtr<ParserAutomaton> getAutomatonPointer(){
//     ParserAutomaton *ptr = new ParserAutomaton();
//     Rcpp::XPtr< ParserAutomaton > p(ptr, true);
//     return p;
// }

// int main()
// {
//   ParserAutomaton* p = new ParserAutomaton()  ;
//   p->minePattern();
//   return 0;
// }
