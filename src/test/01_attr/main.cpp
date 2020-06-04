#include <UGraphviz/UGraphviz.h>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	Graphviz::Graph graph("attr", true);

	auto& registrar = graph.GetRegistrar();

	auto v_a = registrar.RegisterNode("a");
	auto v_b = registrar.RegisterNode("b");
	auto v_c = registrar.RegisterNode("c");
	auto v_d = registrar.RegisterNode("d");
	auto v_e = registrar.RegisterNode("e");

	auto e_ab = registrar.RegisterEdge(v_a, v_b);
	auto e_bc = registrar.RegisterEdge(v_b, v_c);
	auto e_bd = registrar.RegisterEdge(v_b, v_d);

	registrar
		.RegisterNodeAttr(v_a, "shape", "polygon")
		.RegisterNodeAttr(v_a, "sides", "5")
		.RegisterNodeAttr(v_a, "peripheries", "3")
		.RegisterNodeAttr(v_a, "color", "lightblue")
		.RegisterNodeAttr(v_a, "style", "filled")

		.RegisterNodeAttr(v_c, "shape", "polygon")
		.RegisterNodeAttr(v_c, "sides", "4")
		.RegisterNodeAttr(v_c, "skew", ".4")
		.RegisterNodeAttr(v_c, "label", "hello world")

		.RegisterNodeAttr(v_d, "shape", "invtriangle")

		.RegisterNodeAttr(v_e, "shape", "polygon")
		.RegisterNodeAttr(v_e, "sides", "4")
		.RegisterNodeAttr(v_e, "distortion", ".7");

	graph
		.AddNode(v_a)
		.AddNode(v_b)
		.AddNode(v_c)
		.AddNode(v_d)
		.AddNode(v_e)

		.AddEdge(e_ab)
		.AddEdge(e_bc)
		.AddEdge(e_bd);

	cout << graph.Dump() << endl;

	return 0;
}
