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

string inputFileName = "rosalind_ba1k";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<int> frequencyArray;

string genome;

int k;
int genomeSize;

ll patternToNumber(string pattern)
{
    int patternLength = pattern.length();
    string subPattern;
    if (patternLength == 0)
        return 0;
    subPattern = pattern.substr(0, patternLength - 1);
    if (pattern.back() == 'A')
    {
        return 4 * patternToNumber(subPattern) + 0;
    }
    else if (pattern.back() == 'C')
    {
        return 4 * patternToNumber(subPattern) + 1;
    }
    else if (pattern.back() == 'G')
    {
        return 4 * patternToNumber(subPattern) + 2;
    }
    else if (pattern.back() == 'T')
    {
        return 4 * patternToNumber(subPattern) + 3;
    }
}

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        getline(dnaFile, genome);
        dnaFile >> k;
    }
    dnaFile.close();
    genomeSize = genome.length();
    frequencyArray.resize(1 << (2 * k));
}

void solve()
{
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = genome.substr(i, k);
        int j = patternToNumber(pattern);
        frequencyArray[j]++;
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : frequencyArray)
        {
            ansFile << s << " ";
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