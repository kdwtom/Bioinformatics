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

string inputFileName = "rosalind_ba1f";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string genome;

vector<int> minSkewIndex;

int skew;
int genomeSize;
int minDiff;

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        getline(dnaFile, genome);
    }
    dnaFile.close();
    genomeSize = genome.length();
}

void solve()
{
    minDiff = 0;
    skew = 0;
    minSkewIndex.push_back(0);
    for (int i = 0; i < genomeSize; i++)
    {
        if (genome[i] == 'G')
        {
            skew++;
        }
        else if (genome[i] == 'C')
        {
            skew--;
            if (skew < minDiff)
            {
                minSkewIndex.clear();
                minSkewIndex.push_back(i + 1);
                minDiff = skew;
            }
            else if (skew == minDiff)
            {
                minSkewIndex.push_back(i + 1);
            }
        }

        else
        {
            if (skew == minDiff)
            {
                minSkewIndex.push_back(i + 1);
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
        for (auto s : minSkewIndex)
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