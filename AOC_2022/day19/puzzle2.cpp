#include "aoc_utils.h"

using blueprint_t = std::tuple<int, int, std::pair<int, int>, std::pair<int, int>>;
using ores_t = std::tuple<int, int, int, int>;
using robots_t = std::tuple<int, int, int, int>;

void produce(ores_t &ores, const robots_t &robots)
{
    std::get<0>(ores) += std::get<0>(robots);
    std::get<1>(ores) += std::get<1>(robots);
    std::get<2>(ores) += std::get<2>(robots);
    std::get<3>(ores) += std::get<3>(robots);
}

int maximize_blueprint(ores_t ores, robots_t robots, int time, blueprint_t &bp, int &max)
{
    // since it is heuristicly better to make the robot instantly after
    // it is possible to make it the search is reduced to <4 branches each call
    // every call (because there are 4 robots and sometimes it is impossible to produce a robot)
    //   if there is no robot producing geodes the calculations end after producing every possible robot
    // after geode producing robots are made we don't need to modify anything because the previous robots
    // will only waste resources to make more geode robots and the geode robots will work constantly anyway
    // increasing the score

    // cut branch if it cannot create enough geodes to surpass max
    auto max_possible_geodes = std::get<3>(ores) + time*std::get<3>(robots) + (time-1)*(time)/2;
    if( max > max_possible_geodes )
    {
        return 0;
    }

    robots_t produced_robots;
    while(true)
    {
        if( time <= 0 ) break; // time ended -> return number of geodes produced

        if( std::get<0>(produced_robots) == 0 && // ore robot not yet produced in this iteration
            std::get<0>(ores) >= std::get<0>(bp) )
        {
            // can produce ore robot
            std::get<0>(produced_robots) = 1;

            auto ores_cpy = ores;
            auto robots_cpy = robots;
            std::get<0>(ores_cpy) -= std::get<0>(bp);
            std::get<0>(robots_cpy) += 1;
            produce(ores_cpy, robots);

            auto res = maximize_blueprint(ores_cpy, robots_cpy, time-1, bp, max);
            if( res > max ) max = res;
        }
        if( std::get<1>(produced_robots) == 0 && // clay robot not yet produced in this iteration
            std::get<0>(ores) >= std::get<1>(bp) )
        {
            // can produce clay robot
            std::get<1>(produced_robots) = 1;

            auto ores_cpy = ores;
            auto robots_cpy = robots;
            std::get<0>(ores_cpy) -= std::get<1>(bp);
            std::get<1>(robots_cpy) += 1;
            produce(ores_cpy, robots);

            auto res = maximize_blueprint(ores_cpy, robots_cpy, time-1, bp, max);
            if( res > max ) max = res;
        }
        if( std::get<2>(produced_robots) == 0 && // obsidian robot not yet produced in this iteration
            std::get<0>(ores) >= std::get<2>(bp).first &&
            std::get<1>(ores) >= std::get<2>(bp).second )
        {
            // can produce obsidian
            std::get<2>(produced_robots) = 1;

            auto ores_cpy = ores;
            auto robots_cpy = robots;
            std::get<0>(ores_cpy) -= std::get<2>(bp).first;
            std::get<1>(ores_cpy) -= std::get<2>(bp).second;
            std::get<2>(robots_cpy) += 1;
            produce(ores_cpy, robots);

            auto res = maximize_blueprint(ores_cpy, robots_cpy, time-1, bp, max);
            if( res > max ) max = res;
        }
        if( std::get<3>(produced_robots) == 0 && // geode robot not yet produced in this iteration
            std::get<0>(ores) >= std::get<3>(bp).first &&
            std::get<2>(ores) >= std::get<3>(bp).second )
        {
            // can produce geode robot
            std::get<3>(produced_robots) = 1;

            auto ores_cpy = ores;
            auto robots_cpy = robots;
            std::get<0>(ores_cpy) -= std::get<3>(bp).first;
            std::get<2>(ores_cpy) -= std::get<3>(bp).second;
            std::get<3>(robots_cpy) += 1;
            produce(ores_cpy, robots);

            auto res = maximize_blueprint(ores_cpy, robots_cpy, time-1, bp, max);
            if( res > max ) max = res;
        }

        produce(ores, robots);
        time--;
    }

    if( std::get<3>(ores) > max ) max = std::get<3>(ores);
    return max;
}

int solution(std::vector<std::string> &input)
{
    std::vector<blueprint_t> blueprints;
    for( auto &l : input )
    {
        auto ls = aoc::split(l.substr(14), ". ");
        auto r1 = aoc::split(ls[0], ' ');
        auto r2 = aoc::split(ls[1], ' ');
        auto r3 = aoc::split(ls[2], ' ');
        auto r4 = aoc::split(ls[3], ' ');

        blueprints.push_back({
            std::stoi(r1[4]),
            std::stoi(r2[4]),
            {std::stoi(r3[4]), std::stoi(r3[7])},
            {std::stoi(r4[4]), std::stoi(r4[7])}});
    }

    int max;
    int out = 1;
    for( size_t i=1; i<=3; i++ )
    {
        max = 0;
        auto res = maximize_blueprint({0, 0, 0, 0}, {1, 0, 0, 0}, 32, blueprints[i-1], max);
        out *= res;
    }

    return out;
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