#include "aoc_utils.h"

using graph_t = std::vector<std::pair<int, std::vector<int>>>;
using wgraph_t = std::vector<std::pair<int, std::vector<std::pair<int, int>>>>;

int dfs(int v, int time, std::vector<bool> &visited, wgraph_t &graph)
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
            res = dfs(u, time-d-1, visited, graph);
        }

        if( res > max_flow )
        {
            max_flow = res;
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
    int res = 0;
    std::vector<bool> visited(raw_graph.size());
    std::queue<std::pair<int, int>> q;
    q.push({starting_vertex, 0});

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
            std::vector<bool> visited(optimized_graph.size());
            auto dfs_res = dfs(raw_to_optimized_map[v], 30-d-1, visited, optimized_graph);
            if( dfs_res > res )
            {
                res = dfs_res;
            }
        }

        // go deeper
        for( auto u : raw_graph[v].second )
        {
            q.push({u, d+1});
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