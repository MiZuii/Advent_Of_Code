#include "aoc_utils.h"

int solution(std::vector<std::string> &input)
{
    std::stack<size_t> size_stack;
    size_t res = 0;

    for( auto &l : input )
    {
        if(l == "$ cd /")
        {
            size_stack.push(0);
        }
        else if(l == "$ ls")
        {
            continue;
        }
        else if(l == "$ cd ..")
        {
            auto sst = size_stack.top();
            size_stack.pop();
            size_stack.top() += sst;
            if(sst <= 100000) res += sst;
        }
        else if(l.substr(0, 4) == "$ cd")
        {
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

    auto stack_size = size_stack.size();
    for( size_t i=0; i<stack_size-1; i++ )
    {
        auto sst = size_stack.top();
        size_stack.pop();
        size_stack.top() += sst;
        if(sst <= 100000) res += sst;
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