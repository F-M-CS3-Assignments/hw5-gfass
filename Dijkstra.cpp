#include "Dijkstra.h"
#include "BetterPriorityQueue.h"
#include <climits>
#include <map>
#include <set>  // Needed for tracking visited nodes

/*
 * Dijkstra's Algorithm
 * ---------------------
 * Computes the shortest path between two nodes in a graph using a priority queue.
 * Time complexity: O((V + E) * log V)
 * - V = number of vertices
 * - E = number of edges
 */

int dijkstra(nodekey_t source, nodekey_t destination, const Graph *graph) {
    if (!graph->IsPresent(source) || !graph->IsPresent(destination)) {
        return -1;
    }

    std::map<nodekey_t, int> minDistance;
    std::set<nodekey_t> visited;
    BetterPriorityQueue frontier;

    for (nodekey_t node : graph->GetNodes()) {
        BPQNode entry;
        entry.gnode = node;
        entry.pri = (node == source) ? 0 : INT_MAX;
        minDistance[node] = entry.pri;
        frontier.push(entry);
    }

    while (!frontier.empty()) {
    BPQNode current = frontier.top();
    frontier.pop();

   // std::cout << "Visiting node: " << current.gnode << " with priority: " << current.pri << std::endl;

    if (visited.count(current.gnode)) {
        continue;
    }

    // 🛑 Move this block UP so you break early on unreached nodes
    if (current.pri == INT_MAX) {
      //  std::cout << "Remaining node unreachable. Breaking.\n";
        break;
    }

    visited.insert(current.gnode);

    if (current.gnode == destination) {
      //  std::cout << "Reached destination with distance: " << current.pri << std::endl;
        return current.pri;
    }

    for (const GraphEdge* edge : graph->GetOutwardEdgesFrom(current.gnode)) {
        nodekey_t neighbor = edge->to;
        int newDist = current.pri + edge->weight;

        if (newDist < minDistance[neighbor]) {
            minDistance[neighbor] = newDist;

            BPQNode updated;
            updated.gnode = neighbor;
            updated.pri = newDist;

            frontier.Update(updated);
        }
    }
   
    }
    
    return -1; // Destination not reachable
}
