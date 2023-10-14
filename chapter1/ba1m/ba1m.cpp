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

/* Implement NumberToPattern */

string inputFileName = "rosalind_ba1m";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string genome;

int k;
int indexNum;

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

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        dnaFile >> indexNum;
        dnaFile >> k;
    }
    dnaFile.close();
}

void solve()
{
    genome = numberToPattern(indexNum, k);
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        ansFile << genome;
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