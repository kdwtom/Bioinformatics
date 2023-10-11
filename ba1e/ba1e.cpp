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

string inputFileName = "rosalind_ba1e";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string genome;

set<string> frequentPatterns;
vector<int> frequenyArray;
vector<int> clump;

int genomeSize;
int k;
int l;
int t;

ll patternToNumber(string pattern)
{
    char lastNucleotide;
    int patternLength = pattern.length();

    if (patternLength == 0)
        return 0;

    lastNucleotide = pattern.back();
    pattern = pattern.substr(0, patternLength - 1);
    if (lastNucleotide == 'A')
    {
        return 4 * patternToNumber(pattern) + 0;
    }
    else if (lastNucleotide == 'C')
    {
        return 4 * patternToNumber(pattern) + 1;
    }
    else if (lastNucleotide == 'G')
    {
        return 4 * patternToNumber(pattern) + 2;
    }
    else if (lastNucleotide == 'T')
    {
        return 4 * patternToNumber(pattern) + 3;
    }
}

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
    if (k == 1)
        return numberToSymbol(index);
    int remain = index % 4;
    index = index / 4;
    return numberToPattern(index, k - 1) + numberToSymbol(remain);
}

void computingFrequencies(string text, int k)
{
    for (int i = 0; i <= l - k; i++)
    {
        string pattern = text.substr(i, k);
        ll j = patternToNumber(pattern);
        frequenyArray[j]++;
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
        dnaFile >> l;
        dnaFile >> t;
    }

    genomeSize = genome.length();
    clump.resize(1 << (2 * k));
    frequenyArray.resize(1 << (2 * k));

    dnaFile.close();
}

void solve()
{

    string text = genome.substr(0, l);
    computingFrequencies(text, k);

    for (int i = 0; i <= (int)pow(4, k) - 1; i++)
    {
        if (frequenyArray[i] >= t)
        {
            clump[i] = 1;
        }
    }

    for (int i = 1; i <= genomeSize - l; i++)
    {
        string firstPattern = genome.substr(i - 1, k);
        int index = patternToNumber(firstPattern);
        frequenyArray[index]--;
        string lastPattern = genome.substr(i + l - k, k);
        index = patternToNumber(lastPattern);
        frequenyArray[index]++;

        if (frequenyArray[index] >= t)
        {
            clump[index] = 1;
        }
    }

    for (int i = 0; i <= (int)pow(4, k) - 1; i++)
    {
        if (clump[i] == 1)
        {
            string pattern = numberToPattern(i, k);
            frequentPatterns.insert(pattern);
        }
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : frequentPatterns)
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