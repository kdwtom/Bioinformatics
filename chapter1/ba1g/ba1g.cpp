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

string inputFileName = "rosalind_ba1g";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string genome;
string genome2;

int genomeSize;
int hammingDistance;

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        getline(dnaFile, genome);
        getline(dnaFile, genome2);
    }
    dnaFile.close();
    genomeSize = genome.length();
}

void solve()
{
    for (int i = 0; i < genomeSize; i++)
    {
        if (genome[i] != genome2[i])
            hammingDistance++;
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        ansFile << hammingDistance;
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