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

string inputFileName = "rosalind_ba1j";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<int> frequencyArray;
set<string> mismatchArray;

string genome;

int d;
int k;
int genomeSize;
int maxCount;

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

string numberToString(int index, int k)
{
    int remain;
    if (k == 1)
        return numberToSymbol(index);
    remain = index % 4;
    index = index / 4;
    return numberToString(index, k - 1) + numberToSymbol(remain);
}

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

int hammingDistance(string pattern, string patternPrime)
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

string complementStrand(string strand)
{
    reverse(strand.begin(), strand.end());
    int length = strand.length();
    for (int i = 0; i < length; i++)
    {
        if (strand[i] == 'A')
        {
            strand[i] = 'T';
        }
        else if (strand[i] == 'C')
        {
            strand[i] = 'G';
        }
        else if (strand[i] == 'G')
        {
            strand[i] = 'C';
        }
        else if (strand[i] == 'T')
        {
            strand[i] = 'A';
        }
    }

    return strand;
}

vector<string> neighborhood(string pattern, string reversePattern)
{
    vector<string> neighbors;
    for (int i = 0; i <= (int)pow(4, k) - 1; i++)
    {
        string patternPrime = numberToString(i, k);
        if (hammingDistance(pattern, patternPrime) <= d )
        {
            neighbors.push_back(patternPrime);
        }
        if(hammingDistance(reversePattern, patternPrime) <= d){
            neighbors.push_back(patternPrime);
        }
    }
    return neighbors;
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
        dnaFile >> k >> d;
    }
    dnaFile.close();
    genomeSize = genome.length();
    frequencyArray.resize(1 << (2 * k) + 1);
}

void solve()
{
    // cout << complementStrand("ACTG");
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = genome.substr(i, k);
        string reversePattern = complementStrand(pattern);
        vector<string> neighbors = neighborhood(pattern, reversePattern);
        for (auto approximatePattern : neighbors)
        {
            ll j = patternToNumber(approximatePattern);
            frequencyArray[j]++;
            maxCount = max(maxCount, frequencyArray[j]);
        }
    }

    for (int i = 0; i <= (int)pow(4, k) - 1; i++)
    {
        if (frequencyArray[i] == maxCount)
        {
            mismatchArray.insert(numberToString(i, k));
        }
    }

    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : mismatchArray)
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