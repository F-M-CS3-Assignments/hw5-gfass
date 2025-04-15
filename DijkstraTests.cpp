
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;


int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	g->AddNode(4);
	g->AddNode(5);
	g->AddNode(6);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);
	g->AddEdge(1, 6, 14);
	g->AddEdge(6, 1, 14);
	
	g->AddEdge(2, 3, 10);
	g->AddEdge(3, 2, 10);
	g->AddEdge(2, 4, 15);
	g->AddEdge(4, 2, 15);
	
	g->AddEdge(3, 6, 2);
	g->AddEdge(6, 3, 2);
	g->AddEdge(3, 4, 11);
	g->AddEdge(4, 3, 11);
	
	g->AddEdge(6, 5, 9);
	g->AddEdge(5, 6, 9);
	
	g->AddEdge(4, 5, 6);
	g->AddEdge(5, 4, 6);
	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 5;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 20);

	delete g;
	
	cout << "DONE Testing Dijkstra Algorithm" << endl;
	
	return ans;
}


void MoreDijkstraTests(){
	cout << "Deep Testing Dijkstra Algorithm..." << endl;

	// Test 2: Single node graph
	{
		Graph g;
		g.AddNode(42);
		assert(dijkstra(42, 42, &g) == 0);  // Distance to self should be 0
	}

	// Test 3: Unreachable destination
	{
		Graph g;
		g.AddNode(1);
		g.AddNode(2);
		assert(dijkstra(1, 2, &g) == -1);  // No edge between them
	}

	// Test 4: Two-node connected graph
	{
		Graph g;
		g.AddNode(1);
		g.AddNode(2);
		g.AddEdge(1, 2, 5);
		assert(dijkstra(1, 2, &g) == 5);
		assert(dijkstra(2, 1, &g) == -1);  // No reverse edge
	}

	// Test 5: Cycle in graph
	{
		Graph g;
		g.AddNode(1);
		g.AddNode(2);
		g.AddNode(3);
		g.AddEdge(1, 2, 1);
		g.AddEdge(2, 3, 1);
		g.AddEdge(3, 1, 1);
		assert(dijkstra(1, 3, &g) == 2);
	}

	// Test 6: Graph with multiple paths (choosing shortest)
	{
		Graph g;
		g.AddNode(1);
		g.AddNode(2);
		g.AddNode(3);
		g.AddEdge(1, 2, 10);
		g.AddEdge(1, 3, 3);
		g.AddEdge(3, 2, 2);
		assert(dijkstra(1, 2, &g) == 5);  // Path: 1 → 3 → 2
	}

	// Test 7: Disconnected node
	{
		Graph g;
		g.AddNode(1);
		g.AddNode(2);
		g.AddNode(3);
		g.AddEdge(1, 2, 4);
		// node 3 is disconnected
		assert(dijkstra(1, 3, &g) == -1);
	}

	
	cout << "DONE Deep Testing Dijkstra Algorithm" << endl;
}


int main(){
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	cout << endl;
	MoreDijkstraTests();
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
