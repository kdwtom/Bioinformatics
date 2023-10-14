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

/* Implement MotifEnumeration */

string inputFileName = "rosalind_ba2a";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

set<string> motifs;
set<string> kMer;
vector<string> dnaArr;

int d;
int k;
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
        dnaFile >> k >> d;
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
}

void solve()
{
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = dnaArr[0].substr(i, k);
        kMer.insert(pattern);
    }

    for (auto pattern : kMer)
    {
        set<string> neighbors = neighborhood(pattern, d);
        for (auto neighbor : neighbors)
        {
            bool flag = true;
            int dnaArrSize = dnaArr.size();
            for (int i = 1; i < dnaArrSize; i++)
            {
                for (int j = 0; j <= genomeSize - k; j++)
                {
                    string subPattern = dnaArr[i].substr(j, k);
                    if (hammingDistance(neighbor, subPattern) <= d)
                    {
                        flag = false;
                        break;
                    }
                    flag = true;
                }
                if (flag == true)
                {
                    break;
                }
            }
            if (!flag)
            {
                motifs.insert(neighbor);
            }
        }
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : motifs)
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