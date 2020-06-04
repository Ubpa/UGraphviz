#include <UGraphviz/UGraphviz.h>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	Graphviz::Graph g("G", true);

	Graphviz::SubGraph c0("cluster0");
	c0
		.AddAllNodeAttr("style", "filled")
		.AddAllNodeAttr("color", "white")
		.AddGraphAttr("style", "filled")
		.AddGraphAttr("color", "lightgrey")
		.AddGraphAttr("label", "process #1");
	auto a0 = c0.AddNode("a0");
	auto a1 = c0.AddNode("a1");
	auto a2 = c0.AddNode("a2");
	auto a3 = c0.AddNode("a3");
	c0.AddEdge(a0, a1);
	c0.AddEdge(a1, a2);
	c0.AddEdge(a2, a3);

	Graphviz::SubGraph c1("cluster1");
	c1
		.AddAllNodeAttr("style", "filled")
		.AddGraphAttr("color", "blue")
		.AddGraphAttr("label", "process #2");
	auto b0 = c1.AddNode("b0");
	auto b1 = c1.AddNode("b1");
	auto b2 = c1.AddNode("b2");
	auto b3 = c1.AddNode("b3");
	c1.AddEdge(b0, b1);
	c1.AddEdge(b1, b2);
	c1.AddEdge(b2, b3);

	auto start = g.AddNode("start");
	auto end = g.AddNode("end");

	g
		.AddNodeAttr(start, "shape", "Mdiamond")
		.AddNodeAttr(end, "shape", "Msquare");

	auto c0_base = g.AddSubGraph(move(c0));
	auto c1_base = g.AddSubGraph(move(c1));

	g.AddEdge(start, c0_base + a0);
	g.AddEdge(start, c1_base + b0);
	g.AddEdge(c0_base + a1, c1_base + b3);
	g.AddEdge(c1_base + b2, c0_base + a3);
	g.AddEdge(c0_base + a3, c0_base + a0);
	g.AddEdge(c0_base + a3, end);
	g.AddEdge(c1_base + b3, end);

	cout << g.Dump() << endl;

	return 0;
}
