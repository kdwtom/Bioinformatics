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

/* Generate the d-Neighborhood of a String */

string inputFileName = "rosalind_ba1n";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

set<string> neighborAll;

string genome;

int d;

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
        dnaFile >> d;
    }
    dnaFile.close();
}

void solve()
{

    neighborAll = neighborhood(genome, d);
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : neighborAll)
        {
            ansFile << s << "\n";
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