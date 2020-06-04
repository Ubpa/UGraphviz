#include <UGraphviz/core.h>

#include <sstream>

#include <cassert>

using namespace Ubpa;

Graphviz::SubGraph& Graphviz::SubGraph::AddGraphAttr(std::string key, std::string value) {
	graphAttrs.emplace_back(std::move(key), std::move(value));
	return *this;
}
Graphviz::SubGraph& Graphviz::SubGraph::AddAllNodeAttr(std::string key, std::string value) {
	allNodeAttrs.emplace_back(std::move(key), std::move(value));
	return *this;
}
Graphviz::SubGraph& Graphviz::SubGraph::AddAllEdgeAttr(std::string key, std::string value) {
	allEdgeAttrs.emplace_back(std::move(key), std::move(value));
	return *this;
}

size_t Graphviz::SubGraph::AddNode(std::string nodeID) {
	size_t idx = nodes.size();
	id2idx[nodeID] = idx;
	nodes.emplace_back(std::move(nodeID));
	return idx;
}

size_t Graphviz::SubGraph::AddEdge(size_t lhs, size_t rhs) {
	assert(lhs < nodes.size() && rhs < nodes.size());
	size_t idx = edges.size();
	edges.emplace_back(lhs, rhs);
	return idx;
}

size_t Graphviz::SubGraph::GetNodeIdx(const std::string& nodeID) const {
	auto target = id2idx.find(nodeID);
	assert(target != id2idx.end());
	return target->second;
}

Graphviz::SubGraph& Graphviz::SubGraph::AddNodeAttr(size_t nodeIdx, std::string key, std::string value) {
	assert(nodeIdx < nodes.size());
	nodeAttrs[nodeIdx].emplace_back(std::move(key), std::move(value));
	return *this;
}

Graphviz::SubGraph& Graphviz::SubGraph::AddEdgeAttr(size_t edgeIdx, std::string key, std::string value) {
	assert(edgeIdx < edges.size());
	edgeAttrs[edgeIdx].emplace_back(std::move(key), std::move(value));
	return *this;
}

Graphviz::SubGraph& Graphviz::SubGraph::AddSubGraph(SubGraph subgraph) {
	subgraphs.emplace_back(std::move(subgraph));
	return *this;
}

std::string Graphviz::SubGraph::Dump(bool isSub, bool isDigraph, size_t indent) const {
	std::stringstream ss;

	std::string eop = isDigraph ? "->" : "--";

	auto qoute = [](const std::string& id) {
		return "\"" + id + "\"";
	};

	auto print_indent = [&]() -> std::stringstream& {
		for (size_t i = 0; i < indent; i++)
			ss << "  ";
		return ss;
	};

	if (isSub)
		ss << "sub";

	ss << "graph " << qoute(id) << " {" << std::endl;

	indent++;

	auto dumpAttrs = [&](std::string_view head, const auto& attrs) {
		if (attrs.empty())
			return;

		print_indent() << head << " [" << std::endl;
		indent++;
		for (const auto& [key, value] : attrs)
			print_indent() << key << " = " << "\"" << value << "\"" << std::endl;
		indent--;
		print_indent() << "]" << std::endl;
	};

	dumpAttrs("graph", graphAttrs);
	dumpAttrs("node", allNodeAttrs);
	dumpAttrs("edge", allEdgeAttrs);

	for (const auto& subgraph : subgraphs)
		ss << subgraph.Dump(true, isDigraph, indent);

	for (const auto& [nodeIdx, attrs] : nodeAttrs)
		dumpAttrs(qoute(nodes[nodeIdx]), attrs);

	for (size_t i = 0; i < edges.size(); i++) {
		auto [lhs, rhs] = edges[i];
		std::string head = qoute(nodes[lhs]) + " " + eop + " " + qoute(nodes[rhs]);
		auto target = edgeAttrs.find(i);
		if (target == edgeAttrs.end())
			print_indent() << head << std::endl;
		else
			dumpAttrs(head, target->second);
	}

	indent--;
	print_indent() << "}" << std::endl;

	return ss.str();
}

Graphviz::Graph::Graph(std::string id, bool isDigraph, bool isStrict)
	: SubGraph{ std::move(id) }, isDigraph{ isDigraph }, isStrict{ isStrict }{}

Graphviz::Graph& Graphviz::Graph::AddGraphAttr(std::string key, std::string value) {
	return static_cast<Graph&>(SubGraph::AddGraphAttr(std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddAllNodeAttr(std::string key, std::string value) {
	return static_cast<Graph&>(SubGraph::AddAllNodeAttr(std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddAllEdgeAttr(std::string key, std::string value) {
	return static_cast<Graph&>(SubGraph::AddAllEdgeAttr(std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddNodeAttr(size_t nodeIdx, std::string key, std::string value) {
	return static_cast<Graph&>(SubGraph::AddNodeAttr(nodeIdx, std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddEdgeAttr(size_t edgeIdx, std::string key, std::string value) {
	return static_cast<Graph&>(SubGraph::AddEdgeAttr(edgeIdx, std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddSubGraph(SubGraph subgraph) {
	return static_cast<Graph&>(SubGraph::AddSubGraph(std::move(subgraph)));
}

std::string Graphviz::Graph::Dump() const {
	std::stringstream ss;

	if (isStrict)
		ss << "strict ";

	if (isDigraph)
		ss << "di";

	ss << SubGraph::Dump(false, isDigraph, 0);

	return ss.str();
}
