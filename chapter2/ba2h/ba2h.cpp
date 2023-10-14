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
int INF = 2000000000;

/* Implement DistanceBetweenPatternAndStrings */

string inputFileName = "rosalind_ba2h";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<string> dnaArr;

string genome;

int distanceDNA;
int k;
int dnaNum;
int genomeSize;

int hammingDistance(string pattern, string patternPrime)
{
    int hammingDis = 0;
    int patternLength = pattern.length();
    for (int i = 0; i < patternLength; i++)
    {
        if (pattern[i] != patternPrime[i])
        {
            hammingDis++;
        }
    }
    return hammingDis;
}

int minHammingDistance(int index, string pattern, vector<string> dna)
{
    int minDis = INF;
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string subPattern = dna[index].substr(i, k);
        minDis = min(minDis, hammingDistance(pattern, subPattern));
    }
    return minDis;
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
        while (!dnaFile.eof())
        {
            string temp;
            dnaFile >> temp;
            if (temp.length() >= 1)
            {
                dnaArr.push_back(temp);
            }
        }
    }
    dnaFile.close();
    k = genome.length();
    genomeSize = dnaArr[0].length();
    dnaNum = dnaArr.size();
}

void solve()
{
    for (int i = 0; i < dnaNum; i++)
    {
        int disForEach = minHammingDistance(i, genome, dnaArr);
        distanceDNA += disForEach;
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        ansFile << distanceDNA;
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