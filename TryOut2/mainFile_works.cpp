// #include
// "/home/pradeep/UBC/Projects/QRE/miningQre/TRE_Mining/spec-mining/packrat/lib/x86_64-pc-linux-gnu/3.4.4/automatonR/exec/automaton.h"
// #include "automaton.h"
// #include <bits/stdc++.h>
#include<stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  // system("ragel -C automaton.rl -o automaton.cpp && gcc -ldl -fpic -shared -g -w -o automaton.so automaton.cpp");
  system("gcc -fpic -g -shared -ldl -o a.so a.c");

  void *lib = dlopen("./a.so", RTLD_NOW);
  if (!lib) {
    printf("dlopen failed: %s\n", dlerror());
    return 1;
  }
  // printf("Hi");

  // void* (*f)() = dlsym(lib, "abc");
  void (*f)() = dlsym(lib, "abc");
  if (f) {
        f();
    } else {
        printf("dlsym for f1 failed: %s\n", dlerror());
    }


  // ParserAutomaton *p = new ParserAutomaton();
  // char *str = argv[1];
  // p->mine_pattern("a1b");
  dlclose(lib);
  return 0;
}