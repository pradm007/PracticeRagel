/**
 * @file automaton.h
 *
 * @brief Automaton header file for exec
 *
 * @author Pradeep Mahato
 */

// #ifndef AUTOMATON_H
// #define AUTOMATON_H

#include <bits/stdc++.h>
// #include <dlfcn.h>

using namespace std;
#define DEBUG 0

// class Automaton {
//   public:
//     Automaton(){};
//     virtual void mine_pattern(char *p) = 0;
//     virtual ~Automaton(){};
// };

class ParserAutomaton{
  public:
    ParserAutomaton();
    void mine_pattern(const char *p);
    virtual ~ParserAutomaton(){};
};

// #endif