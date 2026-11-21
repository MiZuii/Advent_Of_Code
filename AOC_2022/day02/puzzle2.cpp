#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <map>

int solution(std::vector<std::string> &input)
{
    int myscore = 0;

    // 0 - kamień
    // 1 - papier
    // 2 - nozyce

    std::vector<std::vector<int>> scores = {
        {3, 1, 2}, // lose
        {4, 5, 6}, // draw
        {8, 9, 7}  // win
    };

    for( auto round : input )
    {
        int enemy = (int)round[0] - (int)'A';
        int me    = (int)round[2] - (int)'X';

        myscore += scores[me][enemy];
    }

    return myscore;
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
