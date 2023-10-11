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

string inputFileName = "rosalind_ba1b";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

string text;
string kStr;

vector<int> countArr;
set<string> frequent;

int textSize;
int k;
int maxCount;

int patternCount(string pattern)
{
    int num = 0;
    for (int i = 0; i <= textSize - k; i++)
    {
        string subText = text.substr(i, k);
        if (pattern.compare(subText) == 0)
        {
            num++;
        }
    }
    return num;
}

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        getline(dnaFile, text);
        getline(dnaFile, kStr);
    }
    k = stoi(kStr);
    dnaFile.close();
}

void solve()
{

    textSize = text.length();
    countArr.resize(textSize + 5);

    for (int i = 0; i <= textSize - k; i++)
    {
        string pattern = text.substr(i, k);
        countArr[i] = patternCount(pattern);
        maxCount = max(maxCount, countArr[i]);
    }

    for (int i = 0; i <= textSize - k; i++)
    {
        if (maxCount == countArr[i])
        {
            frequent.insert(text.substr(i, k));
        }
    }
    return;
}

void output()
{
    ansFile.open(outputFileName);
    if (ansFile.is_open())
    {
        for (auto s : frequent)
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