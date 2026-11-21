#include "aoc_utils.h"

using graph_t = std::vector<std::pair<int, std::vector<int>>>;
using wgraph_t = std::vector<std::pair<int, std::vector<std::pair<int, int>>>>;
using cache_t = std::unordered_map<std::pair<int, size_t>, int>;
constexpr int START_TIME = 26;

template<>
struct std::hash<std::vector<bool>>
{
    size_t operator()(const std::vector<bool> &v) const noexcept
    {
        size_t res = 0;
        for( auto b : v )
        {
            res <<= 1;
            res |= b;
        }
        return res;
    }
};

template<>
struct std::hash<std::pair<int, size_t>>
{
    size_t operator()(const std::pair<int, size_t> &v) const noexcept
    {
        size_t res = v.first;
        res <<= 32;
        res ^= v.second;
        return res;
    }
};

int elephant_dfs(int v, int time, std::vector<bool> &visited, wgraph_t &graph)
{
    int max_flow = 0;
    visited[v] = true;
    for( auto &edge : graph[v].second )
    {
        auto u = edge.first;
        auto d = edge.second;
        auto res = 0;
        if( !visited[u] && time-d-1 > 0 )
        {
            res = elephant_dfs(u, time-d-1, visited, graph);
        }

        if( res > max_flow )
        {
            max_flow = res;
        }
    }
    visited[v] = false;

    return max_flow + time*graph[v].first;
}

int dfs(int v, int time, std::vector<bool> &visited, wgraph_t &graph,
        std::vector<std::pair<int, int>> &starting_points, cache_t &elephant_cache)
{
    int max_flow = 0;
    visited[v] = true;
    for( auto &edge : graph[v].second )
    {
        auto u = edge.first;
        auto d = edge.second;
        auto res = 0;
        if( !visited[u] && time-d-1 > 0 )
        {
            res = dfs(u, time-d-1, visited, graph, starting_points, elephant_cache);
        }

        if( res > max_flow )
        {
            max_flow = res;
        }
    }

    size_t visited_hash = std::hash<std::vector<bool>>()(visited);
    for( size_t i=0; i<starting_points.size(); i++ )
    {
        if( !visited[starting_points[i].first] )
        {
            cache_t::iterator it;
            int dfs_res;
            if( (it = elephant_cache.find({i, visited_hash})) != elephant_cache.end() )
            {
                dfs_res = it->second;
            }
            else
            {
                dfs_res = elephant_dfs(starting_points[i].first, starting_points[i].second, visited, graph);
                elephant_cache[{i, visited_hash}] = dfs_res;
            }

            if( dfs_res > max_flow )
            {
                max_flow = dfs_res;
            }
        }
    }

    visited[v] = false;
    return max_flow + time*graph[v].first;
}

int solution(std::vector<std::string> &input)
{
    graph_t raw_graph(input.size());
    wgraph_t optimized_graph;

    std::unordered_map<std::string, int> node_map;
    int c=0;
    for( auto &l : input )
    {
        auto valve_s = l.find(' ');
        auto valve_e = l.find(' ', valve_s+1);
        std::string valve = l.substr(valve_s+1, valve_e-valve_s-1);
        node_map[valve] = c++;
    }

    for( auto &l : input )
    {
        auto spl = aoc::split(l, ';');
        auto valve_s = spl[0].find(' ');
        auto valve_e = spl[0].find(' ', valve_s+1);
        std::string valve = spl[0].substr(valve_s+1, valve_e-valve_s-1);
        auto eq_s = spl[0].find('=');
        int flow = std::stoi(spl[0].substr(eq_s+1));

        std::vector<std::string> edges;
        std::vector<int> transformed_edges;
        if( spl[1][23] == ' ' )
        {
            edges = aoc::split(spl[1].substr(24), ", ");
        }
        else
        {
            edges = aoc::split(spl[1].substr(23), ", ");
        }
        std::transform(edges.begin(), edges.end(), std::back_insert_iterator(transformed_edges),
            [&node_map](const std::string &v) { return node_map[v]; });

        raw_graph[node_map[valve]] = {flow, transformed_edges};
    }

    std::unordered_map<int, int> raw_to_optimized_map;
    c=0;
    for( size_t i=0; i<raw_graph.size(); i++ )
    {
        if( 0 == raw_graph[i].first ) continue;
        optimized_graph.push_back({raw_graph[i].first, {}});
        raw_to_optimized_map[i] = c++;
    }

    for( size_t i=0; i<raw_graph.size(); i++ )
    {
        // perform bfs on nodes which non 0 valve flow rates
        // constructs optimized graph edges with weights

        if( 0 == raw_graph[i].first ) continue;
        std::vector<bool> visited(raw_graph.size());
        std::queue<std::pair<int, int>> q;
        q.push({i, 0});

        while(!q.empty())
        {
            auto rv = q.front();
            q.pop();
            auto v = rv.first;
            auto d = rv.second;

            if( visited[v] ) continue;
            visited[v] = true;

            if( d != 0 && raw_graph[v].first != 0 )
            {
                optimized_graph[raw_to_optimized_map[i]].second.push_back({raw_to_optimized_map[v], d});
            }

            // go deeper
            for( auto u : raw_graph[v].second )
            {
                q.push({u, d+1});
            }
        }
    }


    // perform BFS on starting vertex as it does not have a flow value
    // because of that it is not inlcuded in a optimized graph
    int starting_vertex = node_map["AA"];
    std::vector<bool> visited(raw_graph.size());
    std::queue<std::pair<int, int>> q;
    q.push({starting_vertex, 0});
    std::vector<std::pair<int, int>> starting_points;

    while(!q.empty())
    {
        auto rv = q.front();
        q.pop();
        auto v = rv.first;
        auto d = rv.second;

        if( visited[v] ) continue;
        visited[v] = true;

        if( d != 0 && raw_graph[v].first != 0 )
        {
            starting_points.push_back({raw_to_optimized_map[v], START_TIME-d-1});
        }

        // go deeper
        for( auto u : raw_graph[v].second )
        {
            q.push({u, d+1});
        }
    }

    int res = 0;
    cache_t elephant_cache;
    for( auto &setup : starting_points )
    {
        std::vector<bool> visited(optimized_graph.size());
        auto dfs_res = dfs(setup.first, setup.second, visited, optimized_graph, starting_points, elephant_cache);
        if( dfs_res > res )
        {
            res = dfs_res;
        }
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