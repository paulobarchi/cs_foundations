/* Compile and run: g++ -std=c++11 -W -Wall -O3 -o graph graph.cpp && ./graph
 */

#include <iostream>
#include <cstdint>
#include <sstream>
#include <fstream>

#include "graph.hpp"

graph<size_t> read_file(std::string filename)
{
	std::string line;
	std::ifstream infile(filename);

	std::getline(infile, line);
	size_t V;

	std::istringstream iss_0(line);
	iss_0 >> V;

	graph<size_t> g;

	for (size_t i = 0; i < V; ++i) {
		g.addVertex(i);
	}

	std::getline(infile, line);
	std::istringstream iss_1(line);
	size_t E;
	iss_1 >> E;

	for (size_t i = 0; i < E; ++i) {
		std::getline(infile, line);
		std::istringstream iss_2(line);
		size_t v;
		size_t w;
		double weight;

		iss_2 >> v;
		iss_2 >> w;
		iss_2 >> weight;

		g.addEdge(v, w, weight);
	}

	return g;
}

int main(int argc, char *argv[])
{
	{
		std::cout << "GRAPH 1:\n\n";
		graph<std::string> test;

		test.addVertex("a");
		test.addVertex("b");
		test.addVertex("c");
		test.addVertex("d");
		test.addVertex("e");
		test.addVertex("f");
		test.addEdge("a", "e", 22); 
		test.addEdge("c", "d", 12); 
		test.addEdge("a", "b", 42); 

		std::cout << test << std::endl;
		std::cout << "There is a edge between a and e: " 
			<< ( test.searchByEdge("a", "e") ? "True" : "False") << std::endl;

		std::cout << std::endl;

		test.removeVertex("d");
		test.removeEdge("a", "e");
		test.removeVertex("f");

		std::cout << test;
		std::cout << "\n\n";
	}
	{
		std::cout << "GRAPH 2:\n\n";
		graph<std::string> test1;

		test1.addVertex("u");
		test1.addVertex("w");
		test1.addVertex("v");
		test1.addVertex("t");
		test1.addVertex("a");
		test1.addEdge("u", "v", 12); 
		test1.addEdge("u", "w", 9); 
		test1.addEdge("v", "t", -10); 
		test1.addEdge("w", "t", 2); 
		test1.addEdge("t", "a", 1);
		
		std::cout << test1 << std::endl;
		std::cout << "DISTANCE FROM s TO t:\n";
		std::cout << "Dijkstra's " << test1.dist("u", "a") << std::endl;
		auto path = test1.path("u", "a");
		std::cout << "PATH ";
		for (auto it = path.begin(); it != path.end(); ++it) {
			std::cout << *it << "->";
		}
		std::cout<<std::endl;

	        std::cout << "Bellman Ford " << test1.distNeg("u", "a") << std::endl; 
		path = test1.pathNeg("u", "a");
		std::cout << "PATH ";
		for (auto it = path.begin(); it != path.end(); ++it) {
			std::cout << *it << "->";
		}
		std::cout<<std::endl;
		std::cout << "\n\n";
	}
	{
		std::cout << "GRAPH 3:\n\n";
		graph<size_t> g = read_file("input_graph_1");
		std::cout << g;
		std::cout << "\n";
		std::cout << "DISTANCE FROM 0 TO 3:\n";
		std::cout << g.dist(0, 3);
		std::cout << "\n\n";
	}
	{
		std::cout << "GRAPH 4:\n\n";
		graph<size_t> g = read_file("input_graph_2");
		std::cout << g;
		std::cout << "\n";
		std::cout << "DISTANCE FROM 0 TO 3:\n";
		std::cout << g.dist(0, 3);
		std::cout << "\n\n";
		auto path = g.path(0, 3);
		std::cout << "PATH\n";
		for (auto it = path.begin(); it != path.end(); ++it) {
			std::cout << *it << "->";
		}
		std::cout << std::endl;
		path = g.pathNeg(0, 3);
		for (auto it = path.begin(); it != path.end(); ++it) {
			std::cout << *it << "->";
		}
		std::cout << "\n\n";
	}
	{
		if (argc != 2) {
			return 0;
		}

		graph<size_t> g = read_file(argv[1]);

		std::cout << g.dist(50, 500);
	}

	return 0;
}
