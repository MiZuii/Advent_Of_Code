#include "aoc_utils.h"

enum class Obj
{
    Empty,
    Sand,
    Wall
};

using map_t = std::array<std::array<Obj, 400>, 1000>;

void sim(int x, int y, map_t &map)
{
    if( map[x][y+1] == Obj::Empty )
    {
        sim(x, y+1, map);
    }
    if( map[x-1][y+1] == Obj::Empty )
    {
        sim(x-1, y+1, map);
    }
    if( map[x+1][y+1] == Obj::Empty )
    {
        sim(x+1, y+1, map);
    }

    map[x][y] = Obj::Sand;
}

int solution(std::vector<std::string> &input)
{
    map_t map{};

    int max_y = 0;
    for( auto &l : input )
    {
        auto sp = aoc::split(l, " -> ");
        std::vector<std::pair<int, int>> line;
        std::transform(sp.begin(), sp.end(), std::back_insert_iterator(line),
            [](const std::string &v) -> std::pair<int, int>
            {
                auto p = aoc::split(v, ',');
                return {std::stoi(p[0]), std::stoi(p[1])};
            });

        max_y = std::max(max_y, line[0].second);
        for( size_t i=1; i<line.size(); i++ )
        {
            max_y = std::max(max_y, line[i].second);
            if( line[i-1].first == line[i].first )
            {
                // vertical line
                auto mm = std::minmax(line[i-1].second, line[i].second);
                for( int j=mm.first; j<=mm.second; j++)
                {
                    map[line[i].first][j] = Obj::Wall;
                }
            }
            else if( line[i-1].second == line[i].second )
            {
                // horizontal line
                auto mm = std::minmax(line[i-1].first, line[i].first);
                for( int j=mm.first; j<=mm.second; j++)
                {
                    map[j][line[i].second] = Obj::Wall;
                }
            }
        }
    }

    for( int i=0; i<1000; i++ )
    {
        map[i][max_y+2] = Obj::Wall;
    }

    sim(500, 0, map);

    int res = 0;
    for( auto &r : map )
    {
        for( auto v : r )
        {
            if( Obj::Sand == v ) res++;
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