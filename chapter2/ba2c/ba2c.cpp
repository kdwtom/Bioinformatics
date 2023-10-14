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

/*Find a Profile-most Probable k-mer in a String*/

string inputFileName = "rosalind_ba2c";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<double> prob[4];

string genome;
string kMer;

int k;
int genomeSize;
double maxProb = 0;

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

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < k; j++)
            {
                double temp;
                dnaFile >> temp;
                prob[i].push_back(temp);
            }
        }
    }
    dnaFile.close();
    genomeSize = genome.length();
}

void solve()
{
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = genome.substr(i, k);
        double probablity = 1;
        for (int j = 0; j < k; j++)
        {
            string subPattern = pattern.substr(j, 1);
            probablity *= prob[patternToNumber(subPattern)][j];
        }
        if (probablity >= maxProb)
        {
            maxProb = probablity;
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