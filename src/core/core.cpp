#include <UGraphviz/core.h>

#include <sstream>

#include <cassert>

using namespace Ubpa;

Graphviz::Subgraph& Graphviz::Subgraph::GetSubgraph(const std::string& subgraphID) {
	return subgraphs.find(subgraphID)->second;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddGraphAttr(std::string key, std::string value) {
	graphAttrs.emplace_back(std::move(key), std::move(value));
	return *this;
}
Graphviz::Subgraph& Graphviz::Subgraph::AddAllNodeAttr(std::string key, std::string value) {
	allNodeAttrs.emplace_back(std::move(key), std::move(value));
	return *this;
}
Graphviz::Subgraph& Graphviz::Subgraph::AddAllEdgeAttr(std::string key, std::string value) {
	allEdgeAttrs.emplace_back(std::move(key), std::move(value));
	return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddNode(std::string nodeID) {
	nodeAttrs[nodeID];
	return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddEdge(std::string lhs, std::string rhs) {
	auto edgeID = lhs + rhs;
	edges[edgeID] = { std::move(lhs), std::move(rhs) };
	return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddNodeAttr(const std::string& nodeID, std::string key, std::string value) {
	nodeAttrs[nodeID].emplace_back(std::move(key), std::move(value));
	return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddEdgeAttr(const std::string& lhs, const std::string& rhs, std::string key, std::string value) {
	auto edgeID = lhs + rhs;
	edgeAttrs[edgeID].emplace_back(std::move(key), std::move(value));
	return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddSubgraph(Subgraph subgraph) {
	subgraphs.emplace(subgraph.id, std::move(subgraph));
	return *this;
}

std::string Graphviz::Subgraph::Dump(bool isSub, bool isDigraph, size_t indent) const {
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

	print_indent();

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

	for (const auto& [id, sub] : subgraphs)
		ss << sub.Dump(true, isDigraph, indent);

	for (const auto& [nodeID, attrs] : nodeAttrs)
		dumpAttrs(qoute(nodeID), attrs);

	for (const auto& [edgeID, edge] : edges) {
		const auto& [lhs, rhs] = edge;
		std::string head = qoute(lhs) + " " + eop + " " + qoute(rhs);
		auto target = edgeAttrs.find(lhs + rhs);
		if (target == edgeAttrs.end())
			print_indent() << head << std::endl;
		else
			dumpAttrs(head, target->second);
	}

	indent--;
	print_indent() << "}" << std::endl;

	return ss.str();
}

Graphviz::Graph::Graph(std::string id, bool isDigraph)
	: Subgraph{ std::move(id) }, isDigraph{ isDigraph }{}

Graphviz::Graph& Graphviz::Graph::AddGraphAttr(std::string key, std::string value) {
	return static_cast<Graph&>(Subgraph::AddGraphAttr(std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddAllNodeAttr(std::string key, std::string value) {
	return static_cast<Graph&>(Subgraph::AddAllNodeAttr(std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddAllEdgeAttr(std::string key, std::string value) {
	return static_cast<Graph&>(Subgraph::AddAllEdgeAttr(std::move(key), std::move(value)));
}

Graphviz::Graph& Graphviz::Graph::AddSubgraph(Subgraph subgraph) {
	return static_cast<Graph&>(Subgraph::AddSubgraph(std::move(subgraph)));
}

Graphviz::Graph& Graphviz::Graph::AddNode(std::string nodeID) {
	return static_cast<Graph&>(Subgraph::AddNode(std::move(nodeID)));
}
Graphviz::Graph& Graphviz::Graph::AddEdge(std::string lhs, std::string rhs) {
	return static_cast<Graph&>(Subgraph::AddEdge(std::move(lhs), std::move(rhs)));
}

Graphviz::Graph& Graphviz::Graph::AddNodeAttr(const std::string& nodeID, std::string key, std::string value) {
	return static_cast<Graph&>(Subgraph::AddNodeAttr(nodeID, std::move(key), std::move(value)));
}
Graphviz::Graph& Graphviz::Graph::AddEdgeAttr(const std::string& lhs, const std::string& rhs, std::string key, std::string value) {
	return static_cast<Graph&>(Subgraph::AddEdgeAttr(lhs, rhs, std::move(key), std::move(value)));
}

std::string Graphviz::Graph::Dump() const {
	std::stringstream ss;

	ss << "strict ";

	if (isDigraph)
		ss << "di";

	ss << Subgraph::Dump(false, isDigraph, 0);

	return ss.str();
}
