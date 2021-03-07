#include <bits/stdc++.h>

using namespace std;
map<string, string> customClass;

void defineCustomClass() {
    customClass["33"] = "a";
    customClass["34"] = "b";
    customClass["35"] = "c";
    customClass["48"] = "d";
    customClass["57"] = "e";
    customClass["58"] = "f";
    customClass["59"] = "g";
    customClass["60"] = "h";
    customClass["61"] = "i";
    customClass["62"] = "j";
    customClass["63"] = "k";
    customClass["64"] = "l";
    customClass["65"] = "m";
    customClass["66"] = "n";
    customClass["67"] = "o";
    customClass["68"] = "p";
    customClass["69"] = "q";
    customClass["70"] = "r";
    customClass["71"] = "s";
    customClass["72"] = "t";
}

string getClass(string classValue) {
    return customClass.find(classValue)->second;
}

int main() {

    string inputFile = "./data-all";
    string outputFileEM = "./data-all_cleaned_EM";
    string outputFileTime = "./data-all_cleaned_Time";
    
    string inputContent, outputContent;
    string outputContentEM, outputContentTime;

    ifstream myfileInput(inputFile);
    defineCustomClass();
    
    if (myfileInput.is_open()) {
        while(getline(myfileInput, inputContent)) {
            vector<string> splitString;
            
            /** Split the string with whitespace */
            string splittedString;
            string temp="";
            for (int i=0;i<inputContent.size();i++) {
                // cout << inputContent[i] << endl;
                if (inputContent[i] == 9 && temp.size() > 0) {
                    splitString.push_back(temp);
                    temp.clear();
                } else if (inputContent[i] != 9){
                    temp += inputContent[i];
                }
            }
            splitString.push_back(temp); //flush the remaninig 
            temp.clear();
            
            /** Extract Date */
            vector<int> ownDate;
            for (int i=0;i<splitString[0].size();i++) {
                if (splitString[0][i] == '-') {
                    ownDate.push_back((int)stof(temp));
                    temp.clear();
                } else {
                    temp += splitString[0][i];
                }
            }
            ownDate.push_back((int)stof(temp)); //flush the remaninig 
            temp.clear();
            
            /** Extract Time */
            vector<int> ownTime;
            for (int i=0;i<splitString[1].size();i++) {
                if (splitString[1][i] == ':') {
                    ownTime.push_back((int)stof(temp));
                    temp.clear();
                } else {
                    temp += splitString[1][i];
                }
            }
            ownTime.push_back((int)stof(temp)); //flush the remaninig 
            temp.clear();
            
            struct tm when ={0};
            
            when.tm_mon = ownDate[0];
            when.tm_mday = ownDate[1];
            when.tm_year = ownDate[2];
            when.tm_hour = ownTime[0];
            when.tm_min = ownTime[1];
            
            time_t timeStamp = mktime(&when);
            outputContentTime += " " + to_string((long)timeStamp) + " " + to_string((long)(timeStamp) + 1);
            
            int reading = 0;
            try {
                reading = (int)stof(splitString[3]);
            } catch(const std::exception& e) {
                cout << " a standard exception was caught, with message '" << e.what() << "'\n";
            }
            
            outputContentEM += " " + getClass(splitString[2]) + " " + to_string(reading);
        }
    }
    
    ofstream myoutputFile;
    myoutputFile.open(outputFileEM);
    myoutputFile << outputContentEM << flush;
    myoutputFile.close();
    
    myoutputFile.open(outputFileTime);
    myoutputFile << outputContentTime << flush;
    myoutputFile.close();

    return 0;
}