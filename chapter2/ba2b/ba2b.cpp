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
const int INF = 2000000000;

/* Find a Median String*/

string inputFileName = "rosalind_ba2b";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<string> dnaArr;

string genome;
string kMer;

int k;
int genomeSize;
int dnaNum;
int minD;

string numberToSymbol(int index)
{
    if (index == 0)
    {
        return "A";
    }
    else if (index == 1)
    {
        return "C";
    }
    else if (index == 2)
    {
        return "G";
    }
    else if (index == 3)
    {
        return "T";
    }
}

string numberToPattern(int index, int k)
{
    int remain;
    if (k == 1)
        return numberToSymbol(index);
    remain = index % 4;
    index = index / 4;
    return numberToPattern(index, k - 1) + numberToSymbol(remain);
}

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

int minHammingDistance(int index, string pattern)
{
    int minDis = INF;
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string subPattern = dnaArr[index].substr(i, k);
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
        dnaFile >> k;
        while (!dnaFile.eof())
        {
            string temp;
            getline(dnaFile, temp);
            if (temp.length() >= 1)
            {
                dnaArr.push_back(temp);
            }
        }
    }
    dnaFile.close();
    genomeSize = dnaArr[0].length();
    dnaNum = dnaArr.size();
    minD = INF;
}

void solve()
{
    for (int i = 0; i <= (int)pow(4, k) - 1; i++)
    {
        string pattern = numberToPattern(i, k);
        int totalD = 0;
        for (int j = 0; j < dnaNum; j++)
        {
            int minHamming = minHammingDistance(j, pattern);
            totalD += minHamming;
        }
        if (totalD < minD)
        {
            minD = totalD;
            kMer = pattern;
        }
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        ansFile << kMer;
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