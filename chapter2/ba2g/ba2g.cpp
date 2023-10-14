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

/*Implement GibbsSampler*/

string inputFileName = "rosalind_ba2g";
string outputFileName;
ifstream dnaFile;
ofstream ansFile;

vector<string> dnaArr;
vector<string> bestMotifs;
vector<string> motifs;
vector<vector<double>> profile;

random_device rd;

int k, t;
int n;
int genomeSize;

double probSum = 0;

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

vector<double> probIMaker(vector<vector<double>> profile, string dnaI, int k, int genomeSize)
{
    probSum = 0;
    vector<double> probI;
    for (int i = 0; i <= genomeSize - k; i++)
    {
        string pattern = dnaI.substr(i, k);
        double probablity = 1;
        for (int j = 0; j < k; j++)
        {
            string subPattern = pattern.substr(j, 1);
            probablity *= profile[patternToNumber(subPattern)][j];
        }
        probSum += probablity;
        probI.push_back(probablity);
    }
    for (int i = 0; i <= genomeSize - k; i++)
    {
        probI[i] = probI[i] / probSum;
    }
    return probI;
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

int pickNumber(vector<double> probablities)
{
    double sum = 0;
    vector<double> cumulatvieProb;
    for (double prob : probablities)
    {
        sum += prob;
        cumulatvieProb.push_back(sum);
    }
    mt19937 generateReal(rd());
    uniform_real_distribution<double> dice(0.0, 1.0);
    double r = dice(generateReal);
    auto it = lower_bound(cumulatvieProb.begin(), cumulatvieProb.end(), r);
    return distance(cumulatvieProb.begin(), it);
}

void input()
{
    outputFileName = inputFileName;
    outputFileName.append("_ans.txt");
    inputFileName.append(".txt");

    dnaFile.open(inputFileName);
    if (dnaFile.is_open())
    {

        dnaFile >> k >> t >> n;
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
    for (int l = 1; l <= 20; l++)
    {
        uniform_int_distribution<int> dis(0, genomeSize - k);
        motifs.clear();
        for (int i = 0; i < t; i++)
        {
            string firstKMer;
            int r = dis(gen);
            firstKMer = dnaArr[i].substr(r, k);
            motifs.push_back(firstKMer);
        }
        if (l == 1)
        {
            bestMotifs = motifs;
        }

        if (score(motifs) < score(bestMotifs))
        {
            bestMotifs = motifs;
        }
        uniform_int_distribution<int> distribution(0, t - 1);
        for (int i = 1; i <= n; i++)
        {
            int r = distribution(gen);
            vector<string> motifsPart;
            vector<double> probIList;
            vector<vector<double>> profilePart;
            double probSum = 0;
            int numPick;
            for (int j = 0; j < t; j++)
            {
                if (r != j)
                {
                    motifsPart.push_back(motifs[j]);
                }
            }
            profilePart = makeProfile(motifsPart);
            probIList = probIMaker(profilePart, dnaArr[r], k, genomeSize);
            numPick = pickNumber(probIList);
            motifs[r] = dnaArr[r].substr(numPick, k);
            if (score(motifs) < score(bestMotifs))
            {
                bestMotifs = motifs;
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