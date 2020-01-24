// #include
// "/home/pradeep/UBC/Projects/QRE/miningQre/TRE_Mining/spec-mining/packrat/lib/x86_64-pc-linux-gnu/3.4.4/automatonR/exec/automaton.h"
// #include "automaton.h"
#include <bits/stdc++.h>
#include <dlfcn.h>
using namespace std;

#define FILEINPUT 0

int main(int argc, char **argv) {

  system("ragel -C automaton1.rl -o automaton1.cpp && g++ -fpic -w -g -shared "
         "-o automaton1.so -ldl automaton1.cpp -ldl");

  void *lib = dlopen("./automaton1.so", RTLD_NOW);
  if (!lib) {
    printf("dlopen failed: %s\n", dlerror());
    return 1;
  }

  char *input = "";
  if (FILEINPUT) {

  } else if (argc > 1) {
    input = argv[1];
  } else {
    input = (char *)malloc(INT_MAX * sizeof(char *));
    cout << "Input traceString ";
    cin >> input;
  }

  if (input != NULL && !string(input).empty()) {
    cout << "Input is " << input;
    // ParserAutomaton* (*f)() = (ParserAutomaton* (*)())dlsym(lib,
    // "createParserAutomaton");
    void (*f)(char *);
    f = (void (*)(char *))dlsym(lib, "mine_pattern");
    if (f) {
      // cout << "Address " << f << endl;
      f(input);
    } else {
      printf("dlsym for f1 failed: %s\n", dlerror());
    }

    // ParserAutomaton *p = new ParserAutomaton();
    // char *str = argv[1];
    // p->mine_pattern("a1b");
  }

  dlclose(lib);
  return 0;
}