#include "aoc_utils.h"

int solution(std::vector<std::string> &input)
{
    int res = 0;
    for( auto &l : input )
    {
        auto ranges = aoc::split(l, ',');
        auto range1 = aoc::split(ranges[0], '-');
        auto range2 = aoc::split(ranges[1], '-');
        std::pair<int, int> r1 = {std::stoi(range1[0]), std::stoi(range1[1])};
        std::pair<int, int> r2 = {std::stoi(range2[0]), std::stoi(range2[1])};
        if((r1.first <= r2.second && r1.first >= r2.first) ||
           (r1.second <= r2.second && r1.second >= r2.first) ||
           (r2.first <= r1.second && r2.first >= r1.first) ||
           (r2.second <= r1.second && r2.second >= r1.first)) res++;
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