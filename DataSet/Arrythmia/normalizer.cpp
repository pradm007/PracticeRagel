#include <bits/stdc++.h>

using namespace std;

int main() {

    string inputFile = "./arrhythmia.data";
    string outputFile = "./arrhythmia_cleaned.data";
    
    string inputContent, outputContent;

    ifstream myfileInput(inputFile);
    int skipLine = 1;

    if (myfileInput.is_open()) {
        while(getline(myfileInput, inputContent)) {
            if  (skipLine > 0) {
                skipLine--;
                continue;
            }

            int index = 0;
            string innerOutput = "a";
            index++;

            for (int i=0;i<inputContent.size();i++) {
                if ((char) inputContent[i] == ',') {
                    innerOutput += (char) (97+index);
                    index++;
                } else {
                    innerOutput += (char) inputContent[i];
                }
            }
            innerOutput += (char) (97+index); //for new line itendified as end of a record
            outputContent += innerOutput;
        }
    }

    ofstream myfileOutput;
    myfileOutput.open(outputFile);
    myfileOutput << outputContent << flush;
    // outputFile.close();

    return 0;
}