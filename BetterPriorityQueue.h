#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include "Graph.h" // For nodekey_t and INVALID_NODE_KEY

/*
 * Struct: BPQNode
 * ---------------
 * Represents a node in the priority queue with:
 * - 'pri': the priority (e.g., current shortest distance)
 * - 'visited': flag for visited state
 * - 'gnode': the node key identifier
 *
 * Defines comparison operators for use with std::priority_queue.
 */
struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;

	// Lower priority means higher priority in queue
	bool operator<(const BPQNode& other) const {
		return pri < other.pri;
	}
	bool operator>(const BPQNode& other) const {
		return pri > other.pri;
	}
	bool operator==(const BPQNode& other) const {
		return this->gnode == other.gnode;
	}
};

/*
 * Class: BetterPriorityQueue
 * --------------------------
 * A wrapper around std::priority_queue with additional capabilities:
 * - Contains(): checks if a node exists in the queue
 * - Update(): updates the priority of a node if the new one is better
 * - ToString(): string representation for debugging
 */
class BetterPriorityQueue : public std::priority_queue<BPQNode, std::vector<BPQNode>, std::greater<BPQNode>> {
public:

	// Checks whether a given node (by gnode) is in the queue
	bool Contains(const BPQNode& node) const {
		for (const auto& existing : this->c) {
			if (existing == node) return true;
		}
		return false;
	}

	// Updates a node's priority if the new one is lower
	bool Update(const BPQNode& node) {
		for (size_t i = 0; i < this->c.size(); i++) {
			if (this->c[i] == node) {
				if (node.pri < this->c[i].pri) {
					this->c[i] = node;

					// Re-heapify the internal container after change
					std::make_heap(this->c.begin(), this->c.end(), this->comp);
					return true;
				}
				return false; // Node found but new priority is not better
			}
		}
		return false; // Node not found in queue
	}

	// Returns a string representation of the queue contents
	std::string ToString() const {
		std::ostringstream out;
		out << "[";
		for (size_t i = 0; i < this->c.size(); i++) {
			out << BPQNodeToString(this->c[i]);
			if (i != this->c.size() - 1) {
				out << ", ";
			}
		}
		out << "]";
		return out.str();
	}

	// Static utility function to convert a BPQNode to string
	static std::string BPQNodeToString(const BPQNode& node) {
		std::ostringstream out;
		out << "(" << node.gnode << ", pri: " << node.pri << ")";
		return out.str();
	}
};

#endif // BETTER_PRIORITY_QUEUE_H
