all: graph-tests bpq-tests dijkstra

graph-tests: Graph.cpp GraphTests.cpp
	g++ -std=c++11 -Wall -g Graph.cpp GraphTests.cpp -o graph-tests

bpq-tests: BetterPriorityQueue.cpp BPQTests.cpp
	g++ -std=c++11 -Wall -g Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests

dijkstra: BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp
	g++ -std=c++11 -Wall -g Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp -o dijkstra

run: all
	./graph-tests
	./bpq-tests
	./dijkstra