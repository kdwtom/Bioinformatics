#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <set>
#include <fstream>
using namespace std;
typedef long long ll;

string inputFileName = "rosalind_ba1d";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string pattern;
string genome;

vector<int> location;

int genomeSize;
int k;
int maxCount;



void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        getline(dnaFile, pattern);
        getline(dnaFile, genome);
    }
    dnaFile.close();
}

void solve()
{

    genomeSize = genome.length();
    k = pattern.length();

    for (int i = 0; i <= genomeSize - k; i++)
    {
        string subGenome = genome.substr(i, k);
        if(pattern.compare(subGenome)==0){
            location.push_back(i);
        }
    }

   
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : location)
        {
            ansFile << s;
            ansFile << " ";
        }
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