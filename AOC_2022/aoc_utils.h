#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <array>
#include <queue>
#include <stack>
#include <functional>

namespace aoc
{

class GraphBase
{
public:
    virtual void add_node(std::string n);
    virtual void add_edge(std::string from, std::string to);
    virtual std::string get_dot() const = 0;

    //checks
    virtual bool is_bipartiate() const = 0;

protected:
    std::vector<std::string> nodes;
    std::vector<std::pair<std::string, std::string>> edges;
};

class UndirectedGraph : public GraphBase
{
public:
    virtual void add_edge(std::string from, std::string to) override;
    std::string get_dot() const;
    bool is_bipartiate() const;
};

class DirectedGraph : public GraphBase
{
public:
    virtual void add_edge(std::string from, std::string to) override;
    std::string get_dot() const;
    bool is_bipartiate() const;
};

std::vector<std::string> split(const std::string &in, const std::string delimiter);
std::vector<std::string> split(const std::string &in, const char delimeter);
std::string join(const std::vector<std::string> &in, std::string joint);

}
