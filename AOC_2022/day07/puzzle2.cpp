#include "aoc_utils.h"

int solution(std::vector<std::string> &input)
{
    std::vector<std::string> stack;
    std::stack<size_t> size_stack;
    std::unordered_map<std::string, size_t> dirs;
    size_t res = 0;

    for( auto &l : input )
    {
        if(l == "$ cd /")
        {
            size_stack.push(0);
            stack.push_back("/");
        }
        else if(l == "$ ls")
        {
            continue;
        }
        else if(l == "$ cd ..")
        {
            auto st = stack.back();
            stack.pop_back();
            auto sst = size_stack.top();
            dirs[std::accumulate(stack.begin(), stack.end(), std::string(), 
                [](std::string acc, const std::string &r) { return acc + r; })] = sst;
            size_stack.pop();
            size_stack.top() += sst;

        }
        else if(l.substr(0, 4) == "$ cd")
        {
            stack.push_back(l.substr(5));
            size_stack.push(0);
        }
        else if(l.substr(0, 3) == "dir")
        {
            continue;
        }
        else
        {
            auto s = aoc::split(l, ' ');
            size_stack.top() += std::stoul(s[0]);
        }
    }

    auto stack_size = stack.size();
    for( size_t i=0; i<stack_size-1; i++ )
    {
        auto st = stack.back();
        stack.pop_back();
        auto sst = size_stack.top();
        size_stack.pop();
        size_stack.top() += sst;
        if(sst <= 100000) res += sst;
    }

    size_t needed = size_stack.top() - 40000000;
    size_t min_valid = 70000000;

    for( auto [key, val] : dirs )
    {
        if( val >= needed )
        {
            if(val < min_valid) min_valid = val;
        }
    }

    return min_valid;
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