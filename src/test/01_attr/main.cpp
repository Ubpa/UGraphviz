#include <UGraphviz/UGraphviz.hpp>

#include <iostream>

using namespace Ubpa::UGraphviz;

using namespace std;

int main() {
	Graph graph("attr", true);

	auto& registry = graph.GetRegistry();

	auto v_a = registry.RegisterNode("a");
	auto v_b = registry.RegisterNode("b");
	auto v_c = registry.RegisterNode("c");
	auto v_d = registry.RegisterNode("d");
	auto v_e = registry.RegisterNode("e");

	auto e_ab = registry.RegisterEdge(v_a, v_b);
	auto e_bc = registry.RegisterEdge(v_b, v_c);
	auto e_bd = registry.RegisterEdge(v_b, v_d);

	registry
		.RegisterNodeAttr(v_a, Attrs_shape, "polygon")
		.RegisterNodeAttr(v_a, Attrs_sides, "5")
		.RegisterNodeAttr(v_a, Attrs_peripheries, "3")
		.RegisterNodeAttr(v_a, Attrs_color, "lightblue")
		.RegisterNodeAttr(v_a, Attrs_style, "filled")

		.RegisterNodeAttr(v_c, Attrs_shape, "polygon")
		.RegisterNodeAttr(v_c, Attrs_sides, "4")
		.RegisterNodeAttr(v_c, Attrs_skew, ".4")
		.RegisterNodeAttr(v_c, Attrs_label, "hello world")

		.RegisterNodeAttr(v_d, Attrs_shape, "invtriangle")

		.RegisterNodeAttr(v_e, Attrs_shape, "polygon")
		.RegisterNodeAttr(v_e, Attrs_sides, "4")
		.RegisterNodeAttr(v_e, Attrs_distortion, ".7");

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
