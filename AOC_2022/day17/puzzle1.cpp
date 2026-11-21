#include "aoc_utils.h"
#include <cstring>

constexpr std::array<uint64_t, 5> ROCKS = {{
    0b1111000000000/*-*/,
    0b10000000000000011100000000000000100000000000/*+*/,
    0b1000000000000000100000000000001110000000000/*L*/,
    0b1000000000000000100000000000000010000000000000001000000000000/*|*/,
    0b11000000000000001100000000000/*O*/
}};
constexpr uint16_t ROW_INIT = 0b1000000010000000;

void visualize_state(uint16_t *map, size_t map_size, uint64_t rock, size_t rock_h)
{
    std::vector<std::string> res;
    for( size_t i=0; i<map_size-1; i++ )
    {
        res.push_back({});
        auto &s = res.back();
        if( (uint16_t(1) << 15) & map[i] ) s += "|";
        else s += "O";
        for( size_t shift=1; shift<8; shift++ )
        {
            if( ((uint16_t(1) << 15) >> shift) & map[i] )
            {
                s += "#";
            }
            else
            {
                s += ".";
            }
        }
        if( ((uint16_t(1) << 15) >> 8) & map[i] ) s += "|";
        else s += "O";
    }
    if( map[map_size-1] == uint16_t(0b1111111110000000)) res.push_back("+-------+");
    else res.push_back("+OOOOOOO+");

    for( size_t i=0; i<4; i++ )
    {
        uint16_t rock_row = rock >> ((3-i)*16);
        for( size_t shift=1; shift<8; shift++ )
        {
            char &map = res[rock_h+i][shift];
            if( ((uint16_t(1) << 15) >> shift) & rock_row )
            {
                if( map == '.' )
                {
                    map = '@';
                }
                else
                {
                    map = 'X';
                }
            }
        }
    }

    std::cout << aoc::join(res, "\n") << "\n" << std::endl;
}

uint64_t map_to_range(uint16_t *map, size_t idx)
{
    return ((uint64_t)map[idx  ] << 48) |
           ((uint64_t)map[idx+1] << 32) |
           ((uint64_t)map[idx+2] << 16) |
           ((uint64_t)map[idx+3]);
}

void add_to_map(uint16_t *map, size_t idx, uint64_t val)
{
    map[idx  ] |= val >> 48;
    map[idx+1] |= val >> 32;
    map[idx+2] |= val >> 16;
    map[idx+3] |= val;
}

int solution(std::vector<std::string> &input)
{
    const std::string jet_shifts = input[0];
    size_t step_i = 0; // jet shifts global iteration index

    size_t map_size = 8;
    uint16_t *map = (uint16_t*)malloc(map_size * sizeof(uint16_t));
    map[7] = 0b1111111110000000;
    for( size_t i=0; i<map_size-1; i++ )
    {
        map[i] = ROW_INIT;
    }

    for( size_t i=0; i<2022; i++ )
    {
        // simulate rock
        // init rock variables | the map is correctly allocated at this point
        // having 4 empty rows at the top for shape initization and 3 for falling
        const size_t rock_i = i % ROCKS.size();
        uint64_t rock_shape = ROCKS[rock_i];
        size_t rock_h = 0; // iteration index

        while(true)
        {
            // simulate jest shift
            // visualize_state(map, map_size, rock_shape, rock_h);
            char raw_shift = jet_shifts[step_i++ % jet_shifts.size()];
            if( (raw_shift == '>') && !( (map_to_range(map, rock_h) & (rock_shape >> 1)) ) )
            {
                rock_shape >>= 1; // move rock right if rock doesn't overlap map
            }
            else if( (raw_shift == '<') && !( (map_to_range(map, rock_h) & (rock_shape << 1)) ) )
            {
                rock_shape <<= 1; // move rock left if rock doesn't overlap map
            }

            //simulate rock fall
            // visualize_state(map, map_size, rock_shape, rock_h);
            if( !( (map_to_range(map, rock_h+1) & rock_shape ) ) )
            {
                rock_h++; // move down is possible
            }
            else
            {
                // move down is impossible -> place rock and skip to next shape
                add_to_map(map, rock_h, rock_shape);

                // resize map to prepare for the next shape
                size_t free_rows_count = 0;
                for( ; free_rows_count<map_size; free_rows_count++ )
                {
                    if( map[free_rows_count] & ~ROW_INIT ) break;
                }
                if(free_rows_count >= 7) break; // early break if map is big enough

                size_t new_map_size = map_size + 7 - free_rows_count;
                uint16_t* new_map = (uint16_t*)malloc(new_map_size * sizeof(uint16_t));
                memcpy(new_map + 7 - free_rows_count, map, map_size*sizeof(uint16_t));
                for( size_t init_i=0; init_i<7-free_rows_count; init_i++ )
                {
                    new_map[init_i] = ROW_INIT;
                }
                free(map);
                map = new_map;
                map_size = new_map_size;

                break; // go to next rock simulation
            }
        }
    }

    size_t free_rows_count = 0;
    for( ; free_rows_count<map_size; free_rows_count++ )
    {
        if( map[free_rows_count] & ~ROW_INIT ) break;
    }

    return map_size-1-free_rows_count;
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