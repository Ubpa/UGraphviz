#include <UGraphviz/UGraphviz.h>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	Graphviz::Graph graph("hello world", true);

	graph
		.AddEdge("a", "b")
		.AddEdge("a", "c")
		.AddEdge("b", "d")
		.AddEdge("c", "d");

	cout << graph.Dump() << endl;

	return 0;
}
