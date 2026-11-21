#include "aoc_utils.h"

constexpr std::array<std::tuple<int, int, int>, 6> FACES = {{{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}}};

int fill(int sx, int sy, int sz, std::array<std::array<std::array<bool, 30>, 30>, 30> &map)
{
    // return number of bubble faces if bubble was detected
    std::array<std::array<std::array<bool, 30>, 30>, 30> visited{};
    std::queue<std::tuple<int, int, int>> q;
    q.push({sx, sy, sz});
    int res = 0;
    bool edge_flag = false;

    while(!q.empty())
    {
        auto vr = q.front();
        q.pop();
        auto x = std::get<0>(vr);
        auto y = std::get<1>(vr);
        auto z = std::get<2>(vr);
        if( x == 0 || x == 29 || y == 0 || y == 29 || z == 0 || z == 29 ) edge_flag = true;

        if( visited[x][y][z] || map[x][y][z] ) continue;
        visited[x][y][z] = true;

        // calculate number of visible faces
        for( auto &face : FACES )
        {
            auto nx = x + std::get<0>(face);
            auto ny = y + std::get<1>(face);
            auto nz = z + std::get<2>(face);

            if( nx >= 0 && nx < 30 &&
                ny >= 0 && ny < 30 &&
                nz >= 0 && nz < 30 &&
                map[nx][ny][nz] == true)
            {
                res++;
            }
        }

        // push new faces into the bfs queue
        for( auto &face : FACES )
        {
            auto nx = x + std::get<0>(face);
            auto ny = y + std::get<1>(face);
            auto nz = z + std::get<2>(face);

            if( nx >= 0 && nx < 30 &&
                ny >= 0 && ny < 30 &&
                nz >= 0 && nz < 30)
            {
                q.push({nx, ny, nz});
            }
        }
    }

    // update map after new visited bubble
    for( int x=0; x<30; x++ )
    {
        for( int y=0; y<30; y++ )
        {
            for( int z=0; z<30; z++ )
            {
                map[x][y][z] = map[x][y][z] || visited[x][y][z];
            }
        }
    }

    if( edge_flag ) return 0;
    return res;
}

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

    for( int x=0; x<30; x++ )
    {
        for( int y=0; y<30; y++ )
        {
            for( int z=0; z<30; z++ )
            {
                if( map[x][y][z] ) continue;
                auto f = fill(x, y, z, map);
                res -= f;
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