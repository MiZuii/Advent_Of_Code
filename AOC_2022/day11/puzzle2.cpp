#include "aoc_utils.h"

class Monkey
{
public:
    Monkey(std::vector<long long> items,
           std::string operation,
           int division,
           int throw_if_true,
           int throw_if_false,
           std::vector<Monkey> &monkeys) :
               _inspections_count(0),
               _items(items),
               _division(division),
               _tit(throw_if_true),
               _tif(throw_if_false),
               _monkeys(monkeys)
    {
        auto operation_split = aoc::split(operation, ' ');
        if( operation_split[3] == "+" )
        {
            if( operation_split[4] == "old" )
            {
                _operation = [](long long old) -> long long { return old + old; };
            }
            else
            {
                auto v = std::stoi(operation_split[4]);
                _operation = [v](long long old) -> long long { return old + v; };
            }
        }
        else
        {
            if( operation_split[4] == "old" )
            {
                _operation = [](long long old) -> long long { return old * old; };
            }
            else
            {
                auto v = std::stoi(operation_split[4]);
                _operation = [v](long long old) -> long long { return old * v; };
            }
        }
    }

    Monkey(const Monkey &other) noexcept :
        _inspections_count(other._inspections_count),
        _items(other._items),
        _division(other._division),
        _tit(other._tit), _tif(other._tif),
        _operation(other._operation),
        _monkeys(other._monkeys)
    {}
    Monkey &operator=(const Monkey &other)
    {
        _inspections_count = other._inspections_count;
        _items = other._items;
        _division = other._division;
        _tit = other._tit;
        _tif = other._tif;
        _operation = other._operation;
        _monkeys = other._monkeys;
        return *this;
    }

    void add_item(long long item)
    {
        _items.push_back(item);
    }

    void inspect_items(long long mod)
    {
        for( int i=_items.size()-1; i>=0; i-- )
        {
            _inspections_count++;
            long long new_val = _operation(_items.back());
            new_val %= mod;
            _items.pop_back();
            if( new_val % _division == 0 )
            {
                _monkeys[_tit].add_item(new_val);
            }
            else
            {
                _monkeys[_tif].add_item(new_val);
            }
        }
    }

    long long get_inspection_count() const
    {
        return _inspections_count;
    }

    std::vector<long long> &get_items()
    {
        return _items;
    }

private:
    long long _inspections_count;
    std::vector<long long> _items;
    int _division;
    int _tit, _tif;
    std::function<long long(long long)> _operation;
    std::vector<Monkey> &_monkeys;
};

long long solution(std::vector<std::string> &input)
{
    std::vector<Monkey> monkeys;
    std::vector<long long> divs;
    for( size_t i=0; i<input.size()-5; i+=7)
    {
        auto sv = aoc::split(input[i+1].substr(18), ", ");
        std::vector<long long> items;
        std::transform(sv.begin(), sv.end(), std::back_insert_iterator(items),
            [](std::string &r) { return std::stoi(r); });

        std::string op = input[i+2].substr(13);
        int div = std::stoi(input[i+3].substr(21));
        int iftrue = std::stoi(input[i+4].substr(29));
        int iffalse = std::stoi(input[i+5].substr(30));

        monkeys.emplace_back(items, op, div, iftrue, iffalse, monkeys);
        divs.push_back(div);
    }

    auto lcm = std::accumulate(divs.begin()+1, divs.end(), divs[0],
        [](long long acc, const long long &r)
        {
            return std::lcm(acc, r);
        });

    for( int i=0; i<10000; i++ )
    {
        for( auto &m : monkeys )
        {
            m.inspect_items(lcm);
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey &l, const Monkey &r)
            { return l.get_inspection_count() < r.get_inspection_count(); });
    return (monkeys.end()-1)->get_inspection_count() * (monkeys.end()-2)->get_inspection_count();
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