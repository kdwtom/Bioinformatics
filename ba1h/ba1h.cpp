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

string inputFileName = "rosalind_ba1h";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<int> approximate;

string genome;
string pattern;

int d;
int k;
int genomeSize;

int hammingDistance(string patternPrime)
{
    int hammingDis = 0;
    for (int i = 0; i < k; i++)
    {
        if (pattern[i] != patternPrime[i])
        {
            hammingDis++;
        }
    }
    return hammingDis;
}

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
        dnaFile >> d;
    }
    dnaFile.close();
    genomeSize = genome.length();
    k = pattern.length();
}

void solve()
{
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string patternPrime = genome.substr(i, k);
        if (hammingDistance(patternPrime) <= d)
        {
            approximate.push_back(i);
        }
    }

    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : approximate)
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