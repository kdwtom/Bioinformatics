#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <set>
#include <fstream>
#include <random>
using namespace std;
typedef long long ll;
int INF = 2000000000;

/*Implement RandomizedMotifSearch*/

string inputFileName = "rosalind_ba2f";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<string> dnaArr;
vector<string> bestMotifs;
vector<string> motifs;
vector<vector<double>> profile;

random_device rd;

int k, t;
int genomeSize;

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

vector<vector<double>> makeProfile(vector<string> motifsArr)
{
    int motifRowNum = motifsArr.size();
    int motifColNum = motifsArr[0].length();
    vector<vector<double>> pro;
    pro.resize(4);
    for (int i = 0; i < 4; i++)
    {
        pro[i].resize(motifColNum);
        fill(pro[i].begin(), pro[i].end(), 0);
    }
    for (int i = 0; i < motifColNum; i++)
    {
        int anum = 1;
        int gnum = 1;
        int tnum = 1;
        int cnum = 1;
        for (int j = 0; j < motifRowNum; j++)
        {
            if (motifsArr[j][i] == 'A')
            {
                anum++;
            }
            else if (motifsArr[j][i] == 'C')
            {
                cnum++;
            }
            else if (motifsArr[j][i] == 'G')
            {
                gnum++;
            }
            else if (motifsArr[j][i] == 'T')
            {
                tnum++;
            }
        }
        pro[0][i] = ((double)anum / (double)motifRowNum);
        pro[1][i] = ((double)cnum / (double)motifRowNum);
        pro[2][i] = ((double)gnum / (double)motifRowNum);
        pro[3][i] = ((double)tnum / (double)motifRowNum);
    }

    return pro;
}

string probableKmer(vector<vector<double>> profile, string dnaI, int k, int genomeSize)
{
    double maxProb = -1;
    string probableK;
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = dnaI.substr(i, k);
        double probablity = 1;
        for (int j = 0; j < k; j++)
        {
            string subPattern = pattern.substr(j, 1);
            probablity *= profile[patternToNumber(subPattern)][j];
        }
        if (probablity > maxProb)
        {
            maxProb = probablity;
            probableK = pattern;
        }
    }

    return probableK;
}

vector<string> motfisMaker(vector<vector<double>> profile, vector<string> dna, int k)
{
    vector<string> motifs;
    int t = dna.size();
    int l = dna[0].length();
    for (int i = 0; i < t; i++)
    {
        string motifI = probableKmer(profile, dna[i], k, l);
        motifs.push_back(motifI);
    }
    return motifs;
}

int score(vector<string> motifs)
{
    int col = motifs[0].length();
    int row = motifs.size();
    if (row != t)
    {
        cout << "error\n";
    }
    int score = 0;
    for (int i = 0; i < col; i++)
    {
        int anum = 0;
        int gnum = 0;
        int tnum = 0;
        int cnum = 0;

        int colScore = row;
        for (int j = 0; j < row; j++)
        {
            if (motifs[j][i] == 'A')
            {
                anum++;
            }
            else if (motifs[j][i] == 'C')
            {
                cnum++;
            }
            else if (motifs[j][i] == 'G')
            {
                gnum++;
            }
            else if (motifs[j][i] == 'T')
            {
                tnum++;
            }
        }
        colScore -= max(max(anum, cnum), max(gnum, tnum));
        score += colScore;
    }

    return score;
}

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {
        dnaFile >> k >> t;
        for (int i = 0; i < t; i++)
        {
            string temp;
            dnaFile >> temp;
            dnaArr.push_back(temp);
        }
    }
    dnaFile.close();
    genomeSize = dnaArr[0].length();
}

void solve()
{
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, genomeSize - k);

    for (int i = 0; i < 5000; i++)
    {
        motifs.clear();
        for (int j = 0; j < t; j++)
        {
            string firstKMer;
            if (i == 0)
            {
                firstKMer = dnaArr[j].substr(0, k);
                motifs.push_back(firstKMer);
                bestMotifs = motifs;
            }
            else
            {
                int r = dis(gen);
                firstKMer = dnaArr[j].substr(r, k);
                motifs.push_back(firstKMer);
            }
        }

        while (1)
        {
            profile.clear();
            profile = makeProfile(motifs);
            motifs = motfisMaker(profile, dnaArr, k);
            if (score(motifs) < score(bestMotifs))
            {
                bestMotifs = motifs;
            }
            else
            {
                break;
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
        for (auto s : bestMotifs)
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