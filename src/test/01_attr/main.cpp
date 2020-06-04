#include <UGraphviz/UGraphviz.h>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	Graphviz::Graph graph("attr", true);

	graph
		.AddEdge("a", "b")
		.AddEdge("b", "c")
		.AddEdge("b", "d")

		.AddNodeAttr("a", "shape", "polygon")
		.AddNodeAttr("a", "sides", "5")
		.AddNodeAttr("a", "peripheries", "3")
		.AddNodeAttr("a", "color", "lightblue")
		.AddNodeAttr("a", "style", "filled")

		.AddNodeAttr("c", "shape", "polygon")
		.AddNodeAttr("c", "sides", "4")
		.AddNodeAttr("c", "skew", ".4")
		.AddNodeAttr("c", "label", "hello world")

		.AddNodeAttr("d", "shape", "invtriangle")

		.AddNodeAttr("e", "shape", "polygon")
		.AddNodeAttr("e", "sides", "4")
		.AddNodeAttr("e", "distortion", ".7");

	cout << graph.Dump() << endl;

	return 0;
}
