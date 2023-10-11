#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;
typedef long long ll;



string inputFileName = "rosalind_ba1a";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string text;
string pattern;

int textSize;
int k;
int num;

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {

        getline(dnaFile, text);
        getline(dnaFile, pattern);
        // cout << pattern;
    }
    dnaFile.close();
   
}


void solve(){
    textSize = text.length();
    k = pattern.length();
    cout << k;
    for (int i = 0; i <= textSize - k;i++){
        string subText = text.substr(i, k);
        // cout << subText << "\n";
        if(pattern.compare(subText)==0){
            num++;
        }
    }
        return;
}

void output(){
    ansFile.open(outputFileName);
    if(ansFile.is_open()){
        ansFile << num;
    }
    ansFile.close();
    return;
}

int main()
{
    input();
    solve();
    output();
    return 0;
}