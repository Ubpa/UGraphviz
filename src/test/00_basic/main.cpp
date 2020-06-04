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

	g.AddEdge(a, b);
	g.AddEdge(a, c);
	g.AddEdge(b, d);
	g.AddEdge(c, d);

	cout << g.Dump() << endl;

	return 0;
}
