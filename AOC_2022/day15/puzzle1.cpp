#include "aoc_utils.h"

constexpr int TARGET_Y = 2000000;
using search_t = std::pair<std::pair<int, int>, std::pair<int, int>>;
using range_t = std::pair<int, int>;

int get_distance(const search_t &v)
{
    return abs(v.first.first - v.second.first) + abs(v.first.second - v.second.second);
}

int solution(std::vector<std::string> &input)
{
    std::vector<search_t> in;
    std::vector<range_t> ranges;
    for( auto &l : input )
    {
        auto line_split = aoc::split(l, ':');
        auto comma = line_split[0].find(',');
        auto eq = line_split[0].find('=');
        auto eq2 = line_split[0].find('=', eq+1);
        auto dot = line_split[0].find(':');
        auto x = std::stoi(line_split[0].substr(eq+1, comma-eq));
        auto y = std::stoi(line_split[0].substr(eq2+1, dot-eq2));

        comma = line_split[1].find(',');
        eq = line_split[1].find('=');
        eq2 = line_split[1].find('=', eq+1);
        auto bx = std::stoi(line_split[1].substr(eq+1, comma-eq));
        auto by = std::stoi(line_split[1].substr(eq2+1));

        in.push_back({{x, y}, {bx, by}});
    }

    for( search_t &s : in )
    {
        auto distance = get_distance(s);
        auto distance_to_target = abs(TARGET_Y - s.first.second);
        if( distance >= distance_to_target )
        {
            // imposibility range found
            auto range_size = distance - distance_to_target;
            ranges.push_back({s.first.first - range_size, s.first.first + range_size});
        }
    }

    std::sort(ranges.begin(), ranges.end(), [](const range_t &l, const range_t &r) -> bool
    {
        if( l.first < r.first ) return true;
        if( l.first > r.first ) return false;
        if( l.second < r.second ) return true;
        return false;
    });

    std::vector<range_t> final_ranges;

    while(ranges.size() >= 2)
    {
        auto base_range = ranges[0];
        auto range_to_merge = ranges[1];
        range_t merged_range;
        if(base_range.second >= range_to_merge.first)
        {
            // ranges overlap
            merged_range = {base_range.first, std::max(base_range.second, range_to_merge.second)};
            ranges[1] = merged_range;
        }
        else
        {
            final_ranges.push_back(base_range);
        }
        ranges.erase(ranges.begin());
    }
    final_ranges.push_back(ranges.back());

    return std::accumulate(final_ranges.begin(), final_ranges.end(), 0, [](int acc, const range_t &r)
    {
        return acc + r.second - r.first;
    });
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