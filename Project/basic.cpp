#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/resource.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
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
void CalculateDP(std::vector<std::vector<int>> &dp, std::__cxx11::string &s1, std::__cxx11::string &s2)
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

void Topdown(std::vector<std::vector<int>> &dp, std::__cxx11::string &s1, std::__cxx11::string &s2, std::__cxx11::string &res1, std::__cxx11::string &res2)
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

        // if(f2 == f3 || f1 == f3 || f2 == f1)cout<<'1';

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
    cout << i << ' ' << j << endl;
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
std::string generateString(const std::string& base, int index) {
    std::string result = base;
    result.insert(index + 1, base);
    return result;
}

// read and generate two input string from txt file
std::vector<std::string> generateInputString(const string& url){
    std::vector<std::string> result;

    // open test case file
    std::ifstream file("./SampleTestCases/input1.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        exit(0);
    }

    // read file content and generate new string
    std::string S, T;
    std::getline(file, S);
    std::cout << S << std::endl;
    std::string indexString;
    while (std::getline(file, indexString)) {
        if(isdigit(indexString[0])){
            int index = std::stoi(indexString);
            
            S = generateString(S, index);
            std::cout << S << std::endl;
        }else{
            T = indexString;
            std::cout << T << std::endl;
            break;
        }
    }
    while (std::getline(file, indexString)) {
        int index = std::stoi(indexString);
        T = generateString(T, index);
        std::cout << T << std::endl;
    }
    file.close();

    result.push_back(S);
    result.push_back(T);
    return result;
}

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

    const char *inputFilePath = argv[1];
    const char *outputFilePath = argv[2];

    FILE *inputFile = fopen(inputFilePath, "r");
    if (!inputFile)
    {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen(outputFilePath, "w");
    if (!outputFile)
    {
        perror("Failed to open/create output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }


    struct timeval begin, end;
    gettimeofday(&begin, 0);
    // write your solution here

    std::string s1, s2;
    int t = 0;
    char buffer[2001];
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL)
    {
        if (t == 0)
            s1 = buffer;
        else
            s2 = buffer;
        t++;
        fprintf(outputFile, s2.c_str());
    }

    int n1 = s1.size(), n2 = s2.size();
    string res1 = "", res2 = "";
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
    CalculateDP(dp, s1, s2);
    cout << dp[n1][n2] << endl;
    // DebufDP(n1, n2, dp, outputFile);

    Topdown(dp, s1, s2, res1, res2);

    cout << res1 << res2 << endl;

    // Please call getTotalMemory() only after calling your solution function. It calculates max memory used by the program.
    double totalmemory = getTotalMemory();
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double totaltime = seconds * 1000 + microseconds * 1e-3;

    printf("%f\n", totaltime);
    printf("%f\n", totalmemory);

    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}
