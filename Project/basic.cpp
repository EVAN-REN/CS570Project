#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

int main() {
    // open test case file
    std::string url = "./SampleTestCases/input1.txt";
    // get input string
    std::vector<std::string> inputString = generateInputString(url);

    std::cout << inputString[0] << std::endl;
    std::cout << inputString[1] << std::endl;


    
    return 0;
}
