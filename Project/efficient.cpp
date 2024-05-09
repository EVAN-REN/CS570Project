#include <fstream>
#include <string>
#include <sys/resource.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

// getrusage() is available in linux. Your code will be evaluated in Linux OS.
int Alphas[4][4] = {
    {0, 110, 48, 94},
    {110, 0, 118, 48},
    {48, 118, 0, 110},
    {94, 48, 110, 0}};

int Delta = 30;

unordered_map<char, int> LetterToIndex;

void DebufDP(int n1, int n2, std::vector<std::vector<int>> &dp, FILE *outputFile)
{
    for (int i = 0; i <= n1; ++i)
    {
        for (int j = 0; j <= n2; ++j)
        {
            cout << dp[i][j] << ' ';
            fprintf(outputFile, "%d ", dp[i][j]);
        }
        cout << endl;
    }
}

void CalculateDP(std::vector<std::vector<int>> &dp, std::string &s1, std::string &s2)
{
    int n1 = s1.size(), n2 = s2.size();
    for (int i = 1; i <= n1; ++i)
        dp[i][0] = i * Delta;
    for (int j = 1; j <= n2; ++j)
        dp[0][j] = j * Delta;
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
            int a = LetterToIndex[s1[i - 1]];
            int b = LetterToIndex[s2[j - 1]];

            int f1 = dp[i - 1][j - 1] + Alphas[a][b];
            int f2 = dp[i - 1][j] + Delta;
            int f3 = dp[i][j - 1] + Delta;
            dp[i][j] = min(f1, min(f2, f3));
        }
    }
}

void Topdown(std::vector<std::vector<int>> &dp, std::string &s1, std::string &s2, std::string &res1, std::string &res2)
{
    int i = s1.size(), j = s2.size();

    while (i > 0 && j > 0)
    {
        int a = LetterToIndex[s1[i - 1]];
        int b = LetterToIndex[s2[j - 1]];

        int cur = dp[i][j];
        int f1 = dp[i - 1][j - 1] + Alphas[a][b];
        int f2 = dp[i - 1][j] + Delta;
        int f3 = dp[i][j - 1] + Delta;

        if (cur == f1)
        {
            res1 += s1[i - 1];
            res2 += s2[j - 1];
            i--;
            j--;
        }
        else if (cur == f3)
        {
            res1 += '_';
            res2 += s2[j - 1];
            j--;
        }
        else
        {
            res1 += s1[i - 1];
            res2 += '_';
            i--;
        }
    }
    while (i > 0)
    {
        res1 += s1[i - 1];
        res2 += '_';
        i--;
    }
    while (j > 0)
    {
        res1 += '_';
        res2 += s2[j - 1];
        j--;
    }
    // cout << i << ' ' << j << endl;
    reverse(res1.begin(), res1.end());
    reverse(res2.begin(), res2.end());
}

long getTotalMemory()
{
    struct rusage usage;
    int returnCode = getrusage(RUSAGE_SELF, &usage);
    if (returnCode == 0)
    {
        return usage.ru_maxrss;
    }
    else
    {
        // It should never occur. Check man getrusage for more info to debug.
        printf("error %d", errno);
        return -1;
    }
}

// generate new string
std::string generateString(const std::string &base, int index)
{
    string result = base;
    result.insert(index + 1, base);
    return result;
}

// read and generate two input string from txt file
std::vector<std::string> generateInputString(const string &url)
{
    std::vector<std::string> result;

    // open test case file
    std::ifstream file(url);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        exit(0);
    }

    // read file content and generate new string
    std::string S, T;
    std::string indexString;
    std::getline(file, indexString);
    S = indexString;
    while (std::getline(file, indexString))
    {
        if (isdigit(indexString[0]))
        {
            int index = std::stoi(indexString);
            S = generateString(S, index);
        }
        else
        {
            T = indexString;
            break;
        }
    }
    while (std::getline(file, indexString))
    {
        int index = std::stoi(indexString);
        T = generateString(T, index);
    }
    file.close();

    result.push_back(S);
    result.push_back(T);
    return result;
}

void writeOutputFile(const string &url, const vector<string> &outputContent)
{
    std::ofstream file(url);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        exit(0);
    }

    for (const auto &str : outputContent)
    {
        file << str << std::endl;
    }

    file.close();
}

vector<int> halfDP(const string &s1, const string &s2, bool ifForwards){
    if(ifForwards){
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<int>> halfDpCost(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 1; i <= n1; ++i)
            halfDpCost[i][0] = i * Delta;
        for (int j = 1; j <= n2; ++j)
            halfDpCost[0][j] = j * Delta;
        for (int i = 1; i <= n1; ++i)
        {
            for (int j = 1; j <= n2; ++j)
            {
                int a = LetterToIndex[s1[i - 1]];
                int b = LetterToIndex[s2[j - 1]];

                int f1 = halfDpCost[i - 1][j - 1] + Alphas[a][b];
                int f2 = halfDpCost[i - 1][j] + Delta;
                int f3 = halfDpCost[i][j - 1] + Delta;
                halfDpCost[i][j] = min(f1, min(f2, f3));
            }
        }
        return halfDpCost[n1];
    }else{
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<int>> halfDpCost(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 1; i <= n1; ++i)
            halfDpCost[i][0] = i * Delta;
        for (int j = 1; j <= n2; ++j)
            halfDpCost[0][j] = j * Delta;
        for (int i = 1; i <= n1; ++i)
        {
            for (int j = 1; j <= n2; ++j)
            {
                int a = LetterToIndex[s1[n1 - i]];
                int b = LetterToIndex[s2[n2 - j]];

                int f1 = halfDpCost[i - 1][j - 1] + Alphas[a][b];
                int f2 = halfDpCost[i - 1][j] + Delta;
                int f3 = halfDpCost[i][j - 1] + Delta;
                halfDpCost[i][j] = min(f1, min(f2, f3));
            }
        }
        return halfDpCost[n1];
    }
}

void memoryEfficient(string s1, string s2, string &output1, string &output2, int &cost){
    int n1 = s1.size(), n2 = s2.size();
    if(n1 < 2 || n2 < 2){
        std::vector<std::vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        CalculateDP(dp, s1, s2);
        cost += dp[n1][n2];
        Topdown(dp, s1, s2, output1, output2);
        return;
    }

    int middle = n1 / 2;
    auto front = halfDP(s1.substr(0, middle), s2, true);
    auto back = halfDP(s1.substr(middle), s2, false);

    vector<int> totalDP(n2 + 1, 0);
    for(int j = 0; j <= n2; ++j){
        totalDP[j] = front[j] + back[n2 - j];
    }
    int cut = distance(totalDP.begin(), min_element(totalDP.begin(), totalDP.end()));
    front.clear();
    back.clear();
    string lo1 = "", lo2 = "";
    string ro1 = "", ro2 = "";
    memoryEfficient(s1.substr(0, n1 / 2), s2.substr(0, cut), lo1, lo2, cost);
    memoryEfficient(s1.substr(n1 / 2), s2.substr(cut), ro1, ro2, cost);
    output1 = lo1 + ro1;
    output2 = lo2 + ro2;
}

// ./SampleTestCases/input1.txt
// ./myResult/output1.txt
int main(int argc, char *argv[])
{

    LetterToIndex['A'] = 0;
    LetterToIndex['C'] = 1;
    LetterToIndex['G'] = 2;
    LetterToIndex['T'] = 3;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // input and output address
    const char *inputFilePath = argv[1];
    const char *outputFilePath = argv[2];

    // generate input strings
    std::vector<string> inputStrings = generateInputString(inputFilePath);
    std::vector<string> outputContent;

    // record running time and total memory
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    std::string s1 = inputStrings[0], s2 = inputStrings[1];
    int n1 = s1.size(), n2 = s2.size();
    string res1 = "", res2 = "";

    cout << "input:\n"
         << s1 << endl
         << s2 << endl;
    
    
    int cost = 0;
    memoryEfficient(s1, s2, res1, res2, cost);
    cout << "cost:" << cost << endl;
    outputContent.push_back(std::to_string(cost));
    // DebufDP(n1, n2, dp, outputFile);

    cout << "string1:" << res1 << endl;
    cout << "string2:" << res2 << endl;
    outputContent.push_back(res1);
    outputContent.push_back(res2);

    // record running time and total memory
    double totalmemory = getTotalMemory();
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double totaltime = seconds * 1000 + microseconds * 1e-3;

    printf("Time used: %f\n", totaltime);
    printf("Memory used: %f\n", totalmemory);
    outputContent.push_back(std::to_string(totaltime));
    outputContent.push_back(std::to_string(totalmemory));

    cout << outputContent.size() << endl;
    writeOutputFile(outputFilePath, outputContent);

    return EXIT_SUCCESS;
}
