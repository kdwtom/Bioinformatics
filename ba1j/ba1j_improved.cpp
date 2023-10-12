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

set<string> neighborhood(string pattern, int d)
{
    set<string> neighbors;
    int patternLength = pattern.length();
    char firstSymbol = pattern.front();

    if (d == 0)
    {
        return {pattern};
    }
    if (patternLength == 1)
    {
        return {"A", "G", "T", "C"};
    }

    string suffixPattern = pattern.substr(1, patternLength - 1);

    set<string> suffixNeighbors = neighborhood(suffixPattern, d);

    for (auto text : suffixNeighbors)
    {
        if (hammingDistance(suffixPattern, text) < d)
        {
            neighbors.insert("A" + text);
            neighbors.insert("G" + text);
            neighbors.insert("T" + text);
            neighbors.insert("C" + text);
        }
        else if (hammingDistance(suffixPattern, text) == d)
        {
            string temp = firstSymbol + text;
            neighbors.insert(temp);
        }
        else
        {
            cout << "error ";
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

    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = genome.substr(i, k);
        string reversePattern = complementStrand(pattern);
        set<string> neighborsForward = neighborhood(pattern, d);
        set<string> neighborsReverse = neighborhood(reversePattern, d);

        for (auto approximatePattern : neighborsForward)
        {
            ll j = patternToNumber(approximatePattern);
            frequencyArray[j]++;
            maxCount = max(maxCount, frequencyArray[j]);
        }

        for (auto approximatePattern : neighborsReverse)
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