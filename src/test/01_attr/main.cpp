#include <UGraphviz/UGraphviz.h>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	Graphviz::Graph g("hello world", true);

	auto a = g.AddNode("a");
	auto b = g.AddNode("b");
	auto c = g.AddNode("c");
	auto d = g.AddNode("d");
	auto e = g.AddNode("e");

	g.AddEdge(a, b);
	g.AddEdge(b, c);
	g.AddEdge(b, d);

	g
		.AddNodeAttr(a, "shape", "polygon")
		.AddNodeAttr(a, "sides", "5")
		.AddNodeAttr(a, "peripheries", "3")
		.AddNodeAttr(a, "color", "lightblue")
		.AddNodeAttr(a, "style", "filled")

		.AddNodeAttr(c, "shape", "polygon")
		.AddNodeAttr(c, "sides", "4")
		.AddNodeAttr(c, "skew", ".4")
		.AddNodeAttr(c, "label", "hello world")

		.AddNodeAttr(d, "shape", "invtriangle")

		.AddNodeAttr(e, "shape", "polygon")
		.AddNodeAttr(e, "sides", "4")
		.AddNodeAttr(e, "distortion", ".7");

	cout << g.Dump() << endl;

	return 0;
}
