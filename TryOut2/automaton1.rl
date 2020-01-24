// #include "/home/pradeep/UBC/Projects/QRE/miningQre/TRE_Mining/spec-mining/packrat/lib/x86_64-pc-linux-gnu/3.4.4/automatonR/exec/automaton.h"
// #include "automaton.h"
#include <bits/stdc++.h>
// #include <stdio.h>
#define DEBUG 1

/**
* @file Temporary file. DO NOT MODIFY
*
* @brief Dynamically generated ragel file for specific expression
*
*/

using namespace std;
%% machine foo;
%% write data;

void mine_pattern() {

    if (DEBUG) {
        printf("\tInside actual mining. Mining starts now for pattern lookup.\n");
    }

    char *p = (char *)malloc(INT_MAX * sizeof(char *));
    // if (DEBUG) {
        printf("Enter input string \n");
    // }
    scanf("%s",p);

    int cs, res = 0;
    int totalLength = 0, currentLength = 0;
    vector<int> numbersInPattern;
    vector<vector<int> > numberList;	
    cs = foo_start;
    char *eof;//= p + strlen(p);;
    totalLength = strlen(p);
    //printf("Input is %s \n",p);
    
    vector<int> temp_numbersInPattern;

    %%{

        action CHUNK {
            if (DEBUG) {
                // cout << "Element -> " << (char) fc << endl;
                printf("Element -> %c\n", (char) fc);
            }
            currentLength++;
        }

        action A {
            res++;
            printf("Match happened.\n");
            for (int i=0 ;i< temp_numbersInPattern.size(); i++) {
                if (DEBUG) {
                    printf("%d ~ ", temp_numbersInPattern[i]);
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
            p--;
        }
        action NUM {
            // printf("fc =%c \n",fc);
            if (fc >= 48 && fc <= 57) {
                // printf("	Num =%c \n",fc);
                temp_numbersInPattern.push_back( (char) (fc-48));
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
    			printf("currentLength is %d and totalLength is %d\n", currentLength, totalLength);
            }

            temp_numbersInPattern.clear();

            if (currentLength >= totalLength) {
                // Force break... very bad practice
                if (DEBUG) {
                    // cout << "Trying to break "<< endl;
                    printf("Trying to break \n");
                }
                fbreak;
            }
        }
    
        main := ((('a'([0-9]+ $from(NUM))'a') | ('a'([0-9]+ $from(NUM))'b') | ('a'([0-9]+ $from(NUM))'c') | ('a'([0-9]+ $from(NUM))'d') | ('b'([0-9]+ $from(NUM))'a') | ('b'([0-9]+ $from(NUM))'b') | ('b'([0-9]+ $from(NUM))'c') | ('b'([0-9]+ $from(NUM))'d') | ('c'([0-9]+ $from(NUM))'a') | ('c'([0-9]+ $from(NUM))'b') | ('c'([0-9]+ $from(NUM))'c') | ('c'([0-9]+ $from(NUM))'d') | ('d'([0-9]+ $from(NUM))'a') | ('d'([0-9]+ $from(NUM))'b') | ('d'([0-9]+ $from(NUM))'c') | ('d'([0-9]+ $from(NUM))'d'))+)$to(CHUNK) %to(A) $lerr(E);
                
        write init nocs;
        write exec noend;
    }%%

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

int main() {
    // mine_pattern("a111b222c");
    mine_pattern();
    return 0;
}

// ParserAutomaton::ParserAutomaton() {
// }

// ParserAutomaton* createParserAutomaton() {
//     ParserAutomaton *p = new ParserAutomaton();
//     return p;
// }

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
