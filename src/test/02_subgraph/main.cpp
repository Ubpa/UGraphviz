#include <UGraphviz/UGraphviz.h>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	Graphviz::Subgraph c0("cluster0");
	c0
		.AddAllNodeAttr("style", "filled")
		.AddAllNodeAttr("color", "white")
		.AddGraphAttr("style", "filled")
		.AddGraphAttr("color", "lightgrey")
		.AddGraphAttr("label", "process #1")
		
		.AddEdge("a0", "a1")
		.AddEdge("a1", "a2")
		.AddEdge("a2", "a3");

	Graphviz::Subgraph c1("cluster1");
	c1
		.AddAllNodeAttr("style", "filled")
		.AddGraphAttr("color", "blue")
		.AddGraphAttr("label", "process #2")
		
		.AddEdge("b0", "b1")
		.AddEdge("b1", "b2")
		.AddEdge("b2", "b3");

	Graphviz::Graph graph("G", true);

	graph
		.AddNodeAttr("start", "shape", "Mdiamond")
		.AddNodeAttr("end", "shape", "Msquare")
		
		.AddSubgraph(move(c0))
		.AddSubgraph(move(c1))
		
		.AddEdge("start", "a0")
		.AddEdge("start", "b0")
		.AddEdge("a1", "b3")
		.AddEdge("b2", "a3")
		.AddEdge("a3", "a0")
		.AddEdge("a3", "end")
		.AddEdge("b3", "end");

	cout << graph.Dump() << endl;

	return 0;
}
