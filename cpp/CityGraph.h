#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class CityGraph {
private:
    std::map<std::string, std::vector<std::pair<std::string, int>>> graph;

public:
    CityGraph() {
        road("Zone A", "Zone B", 5);
        road("Zone A", "Zone C", 10);
        road("Zone B", "Zone C", 3);
        road("Zone B", "Zone D", 7);
        road("Zone C", "Zone D", 2);
    }

    void road(std::string a, std::string b, int weight) {
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight});
    }

    bool route(
        std::string source,
        std::string target,
        std::vector<std::string>& path,
        int& cost
    ) const {
        using Node = std::pair<int, std::string>;

        std::priority_queue<
            Node,
            std::vector<Node>,
            std::greater<Node>
        > queue;

        std::map<std::string, int> distance;
        std::map<std::string, std::string> previous;

        for (const auto& entry : graph) {
            distance[entry.first] = std::numeric_limits<int>::max();
        }

        if (!distance.count(source) || !distance.count(target)) {
            return false;
        }

        distance[source] = 0;
        queue.push({0, source});

        while (!queue.empty()) {
            auto current = queue.top();
            queue.pop();

            if (current.first != distance[current.second]) {
                continue;
            }

            for (const auto& edge : graph.find(current.second)->second) {
                if (distance[current.second] + edge.second < distance[edge.first]) {
                    distance[edge.first] = distance[current.second] + edge.second;
                    previous[edge.first] = current.second;
                    queue.push({distance[edge.first], edge.first});
                }
            }
        }

        if (distance[target] == std::numeric_limits<int>::max()) {
            return false;
        }

        cost = distance[target];

        for (std::string current = target;; current = previous[current]) {
            path.push_back(current);

            if (current == source) {
                break;
            }
        }

        std::reverse(path.begin(), path.end());
        return true;
    }
};

#endif
