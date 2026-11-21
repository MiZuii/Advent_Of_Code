#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <cctype>
#include <algorithm>

int solution(std::vector<std::string> &input)
{
    int res = 0;

    for( size_t i=2; i<input.size(); i += 3)
    {
        std::string fir_intersection;
        std::string intersection;
        std::sort(input[i-2].begin(), input[i-2].end());
        std::sort(input[i-1].begin(), input[i-1].end());
        std::sort(input[i-0].begin(), input[i-0].end());
        std::set_intersection(input[i-2].begin(), input[i-2].end(),
                              input[i-1].begin(), input[i-1].end(),
                              std::back_insert_iterator(fir_intersection));
        std::set_intersection(input[i].begin(), input[i].end(),
                              fir_intersection.begin(), fir_intersection.end(),
                              std::back_insert_iterator(intersection));

        char c = intersection[0];
        if( std::islower(c) ) res += (int)c - (int)'a' + 1;
        else res += (int)c - (int)'A' + 27;
    }

    return res;
}

int main(int argc, char* argv[]) {
    std::string inputFilename = "input.txt";

    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    std::cout << solution(input) << std::endl;
    return 0;
}
