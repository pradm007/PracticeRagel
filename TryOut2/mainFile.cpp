// #include
// "/home/pradeep/UBC/Projects/QRE/miningQre/TRE_Mining/spec-mining/packrat/lib/x86_64-pc-linux-gnu/3.4.4/automatonR/exec/automaton.h"
#include "automaton.h"
#include<stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  // system("ragel -C automaton1.rl -o automaton1.cpp && g++ -fpic -w -g -shared -o automaton1.so -ldl automaton1.cpp -ldl");
  // system("gcc --save-temps=obj -fpic -w -g -shared -o automaton.so automaton.cpp");

  void *lib = dlopen("./automaton1.so", RTLD_NOW);
  if (!lib) {
    printf("dlopen failed: %s\n", dlerror());
    return 1;
  }

  // ParserAutomaton* (*f)() = (ParserAutomaton* (*)())dlsym(lib, "createParserAutomaton");
  void (*f)(char *);
  f = (void (*)(char *)) dlsym(lib, "mine_pattern");
  if (f) {
        cout << "Address " << f << endl;
        // ((ParserAutomaton *) f)->mine_pattern("a1b");
    } else {
        printf("dlsym for f1 failed: %s\n", dlerror());
    }


  // ParserAutomaton *p = new ParserAutomaton();
  // char *str = argv[1];
  // p->mine_pattern("a1b");
  dlclose(lib);
  return 0;
}