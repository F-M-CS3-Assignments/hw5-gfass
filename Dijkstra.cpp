#include "Dijkstra.h"
#include "BetterPriorityQueue.h"
#include <climits>
#include <map>

/*
 * Dijkstra's Algorithm
 * ---------------------
 * Computes the shortest path between two nodes in a graph using a priority queue.
 * Time complexity: O((V + E) * log V)
 * - V = number of vertices
 * - E = number of edges
 */

int dijkstra(nodekey_t source, nodekey_t destination, const Graph *graph) {
    // Check if both the source and destination nodes exist in the graph
    if (!graph->IsPresent(source) || !graph->IsPresent(destination)) {
        return -1;
    }

    // Stores the shortest distance from source to each node
    std::map<nodekey_t, int> minDistance;

    // Priority queue to select the next node with the smallest distance
    BetterPriorityQueue frontier;

    // Initialize all distances to "infinity" except for the source node
    for (nodekey_t node : graph->GetNodes()) {
        BPQNode entry;
        entry.gnode = node;
        entry.pri = (node == source) ? 0 : INT_MAX;
        minDistance[node] = entry.pri;
        frontier.push(entry);
    }

    // Main loop: process nodes in order of increasing distance
    while (!frontier.empty()) {
        BPQNode current = frontier.top();
        frontier.pop();

        // If we reach the destination, return the distance
        if (current.gnode == destination) {
            return current.pri;
        }

        // Stop if remaining nodes are unreachable
        if (current.pri == INT_MAX) {
            break;
        }

        // Traverse all neighboring edges
        for (const GraphEdge* connection : graph->GetOutwardEdgesFrom(current.gnode)) {
            nodekey_t neighbor = connection->to;
            int potentialDistance = current.pri + connection->weight;

            // Update distance if a shorter path is found
            if (potentialDistance < minDistance[neighbor]) {
                minDistance[neighbor] = potentialDistance;

                BPQNode updatedNode;
                updatedNode.gnode = neighbor;
                updatedNode.pri = potentialDistance;

                frontier.Update(updatedNode);
            }
        }
    }

    // If destination is unreachable
    return -1;
}
