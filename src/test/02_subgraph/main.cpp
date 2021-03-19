#include <UGraphviz/UGraphviz.hpp>

#include <iostream>

using namespace Ubpa;

using namespace std;

int main() {
	UGraphviz::Graph graph("G", true);

	auto& registry = graph.GetRegistry();

	auto v_a0 = registry.RegisterNode("a0");
	auto v_a1 = registry.RegisterNode("a1");
	auto v_a2 = registry.RegisterNode("a2");
	auto v_a3 = registry.RegisterNode("a3");

	auto v_b0 = registry.RegisterNode("b0");
	auto v_b1 = registry.RegisterNode("b1");
	auto v_b2 = registry.RegisterNode("b2");
	auto v_b3 = registry.RegisterNode("b3");

	auto v_start = registry.RegisterNode("start");
	auto v_end = registry.RegisterNode("end");

	auto e_a0_a1 = registry.RegisterEdge(v_a0, v_a1);
	auto e_a1_a2 = registry.RegisterEdge(v_a1, v_a2);
	auto e_a2_a3 = registry.RegisterEdge(v_a2, v_a3);
	auto e_a3_a0 = registry.RegisterEdge(v_a3, v_a0);

	auto e_b0_b1 = registry.RegisterEdge(v_b0, v_b1);
	auto e_b1_b2 = registry.RegisterEdge(v_b1, v_b2);
	auto e_b2_b3 = registry.RegisterEdge(v_b2, v_b3);

	auto e_a1_b3 = registry.RegisterEdge(v_a1, v_b3);
	auto e_b2_a3 = registry.RegisterEdge(v_b2, v_a3);

	auto e_start_a0 = registry.RegisterEdge(v_start, v_a0);
	auto e_start_b0 = registry.RegisterEdge(v_start, v_b0);

	auto e_a3_end = registry.RegisterEdge(v_a3, v_end);
	auto e_b3_end = registry.RegisterEdge(v_b3, v_end);

	auto& c0 = graph.GenSubgraph("cluster0");
	c0
		.RegisterGraphNodeAttr("style", "filled")
		.RegisterGraphNodeAttr("color", "white")
		.RegisterGraphAttr("style", "filled")
		.RegisterGraphAttr("color", "lightgrey")
		.RegisterGraphAttr("label", "process #1")
		
		.AddEdge(e_a0_a1)
		.AddEdge(e_a1_a2)
		.AddEdge(e_a2_a3);

	auto& c1 = graph.GenSubgraph("cluster1");
	c1
		.RegisterGraphNodeAttr("style", "filled")
		.RegisterGraphAttr("color", "blue")
		.RegisterGraphAttr("label", "process #2")
		
		.AddEdge(e_b0_b1)
		.AddEdge(e_b1_b2)
		.AddEdge(e_b2_b3);

	registry
		.RegisterNodeAttr(v_start, "shape", "Mdiamond")
		.RegisterNodeAttr(v_end, "shape", "Msquare");

	graph
		.AddNode(v_start)
		.AddNode(v_end)

		.AddEdge(e_start_a0)
		.AddEdge(e_start_b0)
		.AddEdge(e_a1_b3)
		.AddEdge(e_b2_a3)
		.AddEdge(e_a3_a0)
		.AddEdge(e_a3_end)
		.AddEdge(e_b3_end);

	cout << graph.Dump() << endl;

	return 0;
}
