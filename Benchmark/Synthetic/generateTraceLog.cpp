#include <bits/stdc++.h>
#include <fstream>

using namespace std;
#define minOf(a, b) ((a) < (b) ? (a) : (b))
#define maxOf(a, b) ((a) > (b) ? (a) : (b))
#define abss(a) ((a) < 0 ? -1 * (a) : (a))

int getRandomDigit(int maxUpperLimit = 10) { return rand() % maxUpperLimit; }

char getRandomCharacter(int maxShift = 1) {
  maxShift = minOf(abss(maxShift), 26);
  return (char)(getRandomDigit(maxShift) + 97);
}

void writeToFile(string name, int alphabetLength = 4, long traceLength = 100)
{

  //   char *traceString = (char *)malloc(INT64_MAX * sizeof(char *));
  string traceString;

  string fileName = "./" + name + ".txt";
  ofstream myfile;

  myfile.open(fileName);
  for (long i = 0; i < traceLength; i++) {
    traceString += getRandomCharacter(alphabetLength) +
                   to_string(getRandomDigit(100000));
  }
  traceString += getRandomCharacter(alphabetLength) + "\n";
  myfile << traceString;
  myfile.close();
}

int main() {
  printf("Hellow \n");

  string name;

  long traceLength;
  cout << "Trace Length : ";
  cin >> traceLength;

  cout << "File Name : ";
  cin >> name;

  int alphabetLength;
  cout << "Alphabet Length : ";
  cin >> alphabetLength;

    writeToFile(name, alphabetLength, traceLength);
  return 0;
}