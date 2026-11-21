#include "aoc_utils.h"

std::vector<std::string> aoc::split(const std::string &in, const std::string delimiter) {
    if(delimiter.size() == 1) return(split(in, delimiter[0]));
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = in.find(delimiter, pos_start)) != std::string::npos) {
        token = in.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(in.substr(pos_start));
    return res;
}

std::vector<std::string> aoc::split(const std::string &in, const char delimeter)
{
    std::stringstream is(in);
    std::string token;
    std::vector<std::string> out;
    while( std::getline(is, token, delimeter) )
    {
        out.push_back(token);
    }
    return out;    
}

std::string aoc::join(const std::vector<std::string> &in, std::string joint)
{
    if( in.size() == 1 ) return in[0];
    return std::accumulate(in.begin()+1, in.end(), in[0],
        [joint]( std::string acc, const std::string &v)
        { 
            return acc + joint + v;
        });
}

void aoc::GraphBase::add_node(std::string n)
{
    if( std::find(nodes.begin(), nodes.end(), n) != nodes.end() ) return;
    nodes.push_back(n);
}

void aoc::GraphBase::add_edge(std::string from, std::string to)
{
    if( std::find(nodes.begin(), nodes.end(), from) == nodes.end() )
    {
        add_node(from);
    }

    if( std::find(nodes.begin(), nodes.end(), to) == nodes.end() )
    {
        add_node(to);
    }

    edges.emplace_back(from, to);
}

void aoc::DirectedGraph::add_edge(std::string from, std::string to)
{
    if( std::find(nodes.begin(), nodes.end(), from) == nodes.end() )
    {
        add_node(from);
    }

    if( std::find(nodes.begin(), nodes.end(), to) == nodes.end() )
    {
        add_node(to);
    }

    bool found = false;
    for( auto &edge : edges )
    {
        if( edge.first == from && edge.second == to )
        {
            found = true;
            break;
        }
    }
    
    if(!found)
    {
        edges.emplace_back(from, to);
    }
}

void aoc::UndirectedGraph::add_edge(std::string from, std::string to)
{
    if( std::find(nodes.begin(), nodes.end(), from) == nodes.end() )
    {
        add_node(from);
    }

    if( std::find(nodes.begin(), nodes.end(), to) == nodes.end() )
    {
        add_node(to);
    }

    bool found = false;
    for( auto &edge : edges )
    {
        if( (edge.first == to && edge.second == from) ||
            (edge.first == from && edge.second == to) )
        {
            found = true;
            break;
        }
    }
    
    if(!found)
    {
        edges.emplace_back(from, to);
    }
}

std::string aoc::UndirectedGraph::get_dot() const
{
    std::string res;
    res.append("graph {\n");
    for( auto &edge : edges )
    {
        res.append("    ").append(edge.first).append(" -- ").append(edge.second).append("\n");
    }
    res.append("}");
    return res;
}

std::string aoc::DirectedGraph::get_dot() const
{
    std::string res;
    res.append("digraph {\n");
    for( auto &edge : edges )
    {
        res.append("    ").append(edge.first).append(" -> ").append(edge.second).append("\n");
    }
    res.append("}");
    return res;
}

bool collides(int v, int val, std::vector<int> &visited, std::vector<std::vector<int>> &graph)
{
    if( visited[v] && visited[v] != val )
    {
        return true;
    }
    if( visited[v] ) return false;
    visited[v] = val;
    val = 3-val;

    bool composite = false;
    for( auto &u : graph[v] )
    {
        composite = composite || collides(u, val, visited, graph);
        if(composite)
        {
            break;
        }
    }

    return composite;
}

bool aoc::UndirectedGraph::is_bipartiate() const
{
    std::unordered_map<std::string, int> nodes_map;
    std::vector<int> visited(nodes.size());
    std::vector<std::vector<int>> graph(nodes.size());
    
    for( size_t i=0; i<nodes.size(); i++ )
    {
        nodes_map[nodes[i]] = i;
    }

    for( auto &edge : edges )
    {
        graph[nodes_map[edge.first]].push_back(nodes_map[edge.second]);
        graph[nodes_map[edge.second]].push_back(nodes_map[edge.first]);
    }
    
    if(collides(0, 1, visited, graph)) return false;
    return true;
}

bool aoc::DirectedGraph::is_bipartiate() const
{
    return false;
}
