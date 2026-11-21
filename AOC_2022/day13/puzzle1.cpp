#include "aoc_utils.h"

std::vector<std::string> csplit(const std::string &s, char delimeter)
{
    std::vector<std::string> res;
    if(s.size() == 0)
    { 
        return res;
    }
    
    int arr_cnt = 0;
    size_t start_pos=0, end_pos;
    for( size_t i=0; i<s.size(); i++ )
    {
        if( s[i] == '[' )
        {
            arr_cnt++;
        }
        else if( s[i] == ']' )
        {
            arr_cnt--;
        }
        else
        {
            if(!arr_cnt)
            {
                if( s[i] == ',' )
                {
                    end_pos = i;
                    res.push_back(s.substr(start_pos, end_pos-start_pos));
                    start_pos = end_pos+1;
                }
            }
        }
    }

    res.push_back(s.substr(start_pos));
    return res;
}

int compare(std::string l, std::string r)
{
    if( l[0] == '[' && r[0] == '[' )
    {
        // both are array
        auto ls = csplit(l.substr(1, l.size()-2), ',');
        auto rs = csplit(r.substr(1, r.size()-2), ',');

        for( size_t i=0; i<std::max(ls.size(), rs.size()); i++)
        {
            if( i >= ls.size() )
            {
                return -1;
            }
            if( i >= rs.size() )
            {
                return 1;
            }
            auto comp_res = compare(ls[i], rs[i]);
            if(comp_res) return comp_res;
        }
        return 0;
    }
    else if( l[0] != '[' && r[0] != '[' )
    {
        return std::stoi(l) - std::stoi(r);
    }
    else if( l[0] == '[' )
    {
        // left is array right is int
        return compare(l, "[" + r + "]");
    }
    else
    {
        // right is array left is int
        return compare("[" + l + "]", r);
    }
}

int solution(std::vector<std::string> &input)
{
    int res = 0;
    for( size_t i=0; i<input.size()-2; i+=3)
    {
        if( compare(input[i], input[i+1]) < 0 ) res += i/3+1;
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