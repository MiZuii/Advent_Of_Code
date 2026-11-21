#include "aoc_utils.h"

const std::array<std::pair<int, int>, 4> shifts = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

int solution(std::vector<std::string> &input)
{
    std::vector<std::vector<bool>> visited(input.size());
    for( auto &v : visited ) v.resize(input[0].size());
    std::queue<std::pair<std::pair<int, int>, int>> queue;

    for( size_t y=0; y<input.size(); y++ )
    {
        for( size_t x=0; x<input[0].size(); x++ )
        {
            if( input[y][x] == 'E' )
            {
                queue.push({{y, x}, 0});
                input[y][x] = 'z';
            }
        }
    }

    while(!queue.empty())
    {
        auto vr = queue.front();
        auto v = vr.first;
        auto d = vr.second;
        queue.pop();

        if( input[v.first][v.second] == 'a' )
        {
            return d;
        }

        if( visited[v.first][v.second] ) continue;
        visited[v.first][v.second] = true;

        for( auto shift : shifts )
        {
            std::pair<int, int> nv = {v.first + shift.first, v.second + shift.second};

            if( nv.first >= 0 && nv.first < input.size() && nv.second >= 0 && nv.second < input[0].size() &&
                input[nv.first][nv.second] - input[v.first][v.second] >= -1)
            {
                queue.push({nv, d+1});
            }
        }
    }

    return 0;
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