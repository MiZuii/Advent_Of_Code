#include "aoc_utils.h"

constexpr std::array<std::tuple<int, int, int>, 6> FACES = {{{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}}};

int solution(std::vector<std::string> &input)
{
    std::array<std::array<std::array<bool, 30>, 30>, 30> map{};

    int res = 0;
    for( auto &l : input )
    {
        auto s = aoc::split(l, ',');
        int x = std::stoi(s[0]);
        int y = std::stoi(s[1]);
        int z = std::stoi(s[2]);
        res += 6;
        map[x][y][z] = true;

        for( auto &face : FACES )
        {
            if( map[std::get<0>(face) + x][std::get<1>(face) + y][std::get<2>(face) + z] )
            {
                res -= 2;
            }
        }
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