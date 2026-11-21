#include "aoc_utils.h"

int solution(std::vector<std::string> &input)
{
    std::string in = input[0];
    const int seq_size = 14;

    for( size_t pos=seq_size-1; pos<in.size(); pos++ )
    {
        bool valid = true;
        for( size_t i=0; i<seq_size-1; i++ )
        {
            for( size_t j=i+1; j<seq_size; j++ )
            {
                if(in[pos+i-seq_size+1] == in[pos+j-seq_size+1]) valid = false;
            }
        }
        if(valid)
        {
            return pos+1;
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