#include <bits/stdc++.h>
#include <dlfcn.h>
using namespace std;

int main(int argc, char **argv) {

  system("g++ -fpic -shared -ldl -o a.so a.cpp");

  void *lib = dlopen("./a.so", RTLD_NOW);
  if (!lib) {
    cout << "dlopen failed: " << dlerror() << endl;
    return 1;
  }

  void (*f)();
  f = (void (*)()) dlsym(lib, "abc");
  if (f) {
      f();
  } else {
      cout << "dlsym for f1 failed: " << dlerror() << endl;
  }

  dlclose(lib);
  return 0;
}