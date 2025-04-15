#include "Graph.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <set>
#include <string>

using namespace std;

/*
 * Helper function (not part of Graph class):
 * Searches the adjacency list to check if an edge already exists.
 */
const GraphEdge* findExistingEdge(nodekey_t fromNode, nodekey_t toNode, const vector<vector<GraphEdge*>>& adjacencyList) {
    if (adjacencyList.empty()) {
        return nullptr;
    }

    for (const auto& row : adjacencyList) {
        for (const GraphEdge* edge : row) {
            if (edge->from == fromNode && edge->to == toNode) {
                return edge;
            }
        }
    }
    return nullptr;
}

/*
 * Helper function (not part of Graph class):
 * Converts a GraphEdge into a readable string.
 */
string GraphEdgeToString(const GraphEdge* edge) {
    return "((" + to_string(edge->from) + ")->(" + to_string(edge->to) + ") w:" + to_string(edge->weight) + ")";
}

/*
 * Adds a new node to the graph.
 */
void Graph::AddNode(nodekey_t key) {
    if (IsPresent(key)) {
        throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
    }

    nodes.push_back(key);
    adjList.emplace_back();  // creates an empty row in the adjacency list
}

/*
 * Adds a directed edge to the graph.
 */
const GraphEdge* Graph::AddEdge(nodekey_t from, nodekey_t to, unsigned int weight) {
    if (findExistingEdge(from, to, adjList) != nullptr) {
        throw invalid_argument("Duplicate edge cannot be added: " + to_string(from) + " -> " + to_string(to));
    }

    if (!IsPresent(from)) {
        throw invalid_argument("No such source node: " + to_string(from));
    }

    if (!IsPresent(to)) {
        throw invalid_argument("No such destination node: " + to_string(to));
    }

    auto* newEdge = new GraphEdge{from, to, weight};

    size_t index = 0;
    while (index < nodes.size() && nodes[index] != from) {
        index++;
    }

    adjList[index].push_back(newEdge);
    return newEdge;
}

/*
 * Checks whether a node exists in the graph.
 */
bool Graph::IsPresent(nodekey_t key) const {
    for (nodekey_t n : nodes) {
        if (n == key) {
            return true;
        }
    }
    return false;
}

/*
 * Retrieves all outward edges from a given node.
 */
set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const {
    size_t index = 0;
    while (index < nodes.size() && nodes[index] != node) {
        index++;
    }

    if (index == nodes.size()) {
        throw invalid_argument("No such node: " + to_string(node));
    }

    set<const GraphEdge*> result;
    for (GraphEdge* edge : adjList[index]) {
        if (edge->from == node) {
            result.insert(edge);
        }
    }

    return result;
}

/*
 * Returns all node keys in the graph as a set.
 */
set<nodekey_t> Graph::GetNodes() const {
    return set<nodekey_t>(nodes.begin(), nodes.end());
}

/*
 * Returns the number of nodes (order of the graph).
 */
size_t Graph::Order() const {
    return nodes.size();
}

/*
 * Returns the number of edges (size of the graph).
 */
size_t Graph::Size() const {
    size_t count = 0;
    for (const auto& row : adjList) {
        count += row.size();
    }
    return count;
}

/*
 * Returns a string representation of all nodes.
 */
string Graph::NodesToString() const {
    if (nodes.empty()) {
        return "[]";
    }

    string result = "[";
    for (size_t i = 0; i < nodes.size(); ++i) {
        result += "(" + to_string(nodes[i]) + ")";
        if (i != nodes.size() - 1) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

/*
 * Returns a string representation of all edges.
 */
string Graph::EdgesToString() const {
    if (adjList.empty()) {
        return "[]";
    }

    string result = "[";
    size_t edgeCount = Size();
    size_t currentCount = 0;

    for (const auto& row : adjList) {
        for (GraphEdge* edge : row) {
            result += GraphEdgeToString(edge);
            if (++currentCount < edgeCount) {
                result += ", ";
            }
        }
    }

    result += "]";
    return result;
}

/*
 * Destructor to clean up dynamically allocated memory.
 */
Graph::~Graph() {
    for (auto& row : adjList) {
        for (GraphEdge* edge : row) {
            delete edge;
        }
    }
}