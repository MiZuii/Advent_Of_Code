#include "aoc_utils.h"

template<>
struct std::hash<std::pair<int, int>>
{
    size_t operator()(const std::pair<int, int> &r) const noexcept
    {
        size_t res = 0;
        res |= r.first;
        res <<= sizeof(int)*8;
        res |= r.second;
        return res;
    }
};

std::pair<int, int> update_tail(int hx, int hy, int tx, int ty)
{
    if(abs(ty-hy) >= 2 || abs(tx-hx) >= 2)
    {
        if(abs(ty-hy) > 0)
        {
            if(ty-hy > 0) ty--;
            else ty++;
        }
        if(abs(tx-hx) > 0)
        {
            if(tx-hx > 0) tx--;
            else tx++;
        }
    }
    return {tx, ty};
}

int solution(std::vector<std::string> &input)
{
    std::unordered_map<std::pair<int, int>, bool> visited;
    int hx=0, hy=0, tx=0, ty=0;
    for( auto &l : input )
    {
        auto dir = l[0];
        int steps = std::stoi(l.substr(2));

        for( int i=0; i<steps; i++ )
        {
            switch (dir)
            {
            case 'R':
                hx += 1;
                break;
            case 'L':
                hx -= 1;
                break;
            case 'D':
                hy -= 1;
                break;
            case 'U':
                hy += 1;
                break;
            default:
                break;
            }

            auto nt = update_tail(hx, hy, tx, ty);
            tx = nt.first;
            ty = nt.second;
            visited[nt] = true;
        }
    }

    return std::accumulate(visited.begin(), visited.end(), 0, [](int acc, const std::pair<std::pair<int, int>, bool> &r) 
        { return acc + (r.second ? 1 : 0); });
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