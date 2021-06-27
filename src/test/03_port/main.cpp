#include <UGraphviz/UGraphviz.hpp>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	// https://graphviz.org/doc/info/shapes.html#record

	UGraphviz::Graph graph("structs", true);

	auto& registry = graph.GetRegistry();

	auto v_struct1 = registry.RegisterNode("struct1");
	auto v_struct2 = registry.RegisterNode("struct2");
	auto v_struct3 = registry.RegisterNode("struct3");

	auto e_struct1_f1_struct2_f0 = registry.RegisterEdge(v_struct1, v_struct2);
	auto e_struct1_f2_struct3_here = registry.RegisterEdge(v_struct1, v_struct3);

	graph.RegisterGraphNodeAttr("shape", "record");

	registry
		.RegisterNodeAttr(v_struct1, "label", "<f0> left|<f1> mid&#92; dle|<f2> right")
		.RegisterNodeAttr(v_struct2, "label", "<f0> one|<f1> two")
		.RegisterNodeAttr(v_struct3, "label", "hello&#92;nworld |{ b |{c|<here> d|e}| f}| g | h")

		.RegisterEdgePort(e_struct1_f1_struct2_f0, { .ID = "f1" }, { .ID = "f0" })
		.RegisterEdgePort(e_struct1_f2_struct3_here, { .ID = "f2" }, { .ID = "here" })
		;

	graph
		.AddNode(v_struct1)
		.AddNode(v_struct2)
		.AddNode(v_struct3)

		.AddEdge(e_struct1_f1_struct2_f0)
		.AddEdge(e_struct1_f2_struct3_here)
		;

	cout << graph.Dump() << endl;

	return 0;
}
