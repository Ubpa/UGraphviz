#include <UGraphviz/Subgraph.h>

#include <UGraphviz/Registry.h>

#include <sstream>

#include <cassert>

using namespace Ubpa::UGraphviz;

Subgraph::~Subgraph() {
	for (auto subgraph : subgraphs)
		delete subgraph;
}

Subgraph& Subgraph::GetSubgraph(std::string_view subgraphID) {
	return *subgraphs[subgraphID2idx.find(subgraphID)->second];
}

Subgraph& Subgraph::RegisterGraphAttr(std::string key, std::string value) {
	graphAttrs.emplace(std::move(key), std::move(value));
	return *this;
}
Subgraph& Subgraph::RegisterGraphNodeAttr(std::string key, std::string value) {
	graphNodeAttrs.emplace(std::move(key), std::move(value));
	return *this;
}
Subgraph& Subgraph::RegisterGraphEdgeAttr(std::string key, std::string value) {
	graphEdgeAttrs.emplace(std::move(key), std::move(value));
	return *this;
}

Subgraph& Subgraph::DeregisterGraphAttr(std::string_view key) {
	graphAttrs.erase(graphAttrs.find(key));
	return *this;
}

Subgraph& Subgraph::DeregisterGraphNodeAttr(std::string_view key) {
	graphNodeAttrs.erase(graphNodeAttrs.find(key));
	return *this;
}

Subgraph& Subgraph::DeregisterGraphEdgeAttr(std::string_view key) {
	graphEdgeAttrs.erase(graphEdgeAttrs.find(key));
	return *this;
}

Subgraph& Subgraph::GenSubgraph(std::string ID) {
	subgraphID2idx[ID] = subgraphs.size();
	auto newSubGraph = new Subgraph{ registry, std::move(ID) };
	subgraphs.push_back(newSubGraph);
	return *subgraphs.back();
}

bool Subgraph::HaveNode(size_t nodeIndex) const {
	return nodeIndices.find(nodeIndex) != nodeIndices.end();
}

bool Subgraph::HaveEdge(size_t edgeIndex) const {
	return edgeIndices.find(edgeIndex) != edgeIndices.end();
}

Subgraph& Subgraph::AddNode(size_t nodeIndex) {
	nodeIndices.insert(nodeIndex);
	return *this;
}

Subgraph& Subgraph::AddEdge(size_t edgeIndex) {
	edgeIndices.insert(edgeIndex);
	return *this;
}

Subgraph& Subgraph::EraseNode(size_t nodeIndex) {
	nodeIndices.erase(nodeIndex);
	return *this;
}

Subgraph& Subgraph::EraseEdge(size_t edgeIndex) {
	edgeIndices.erase(edgeIndex);
	return *this;
}

std::string Subgraph::Dump(bool isSub, bool isDigraph, size_t indent) const {
	if (!isSub && subgraphs.empty() && nodeIndices.empty() && edgeIndices.empty())
		return "";

	std::stringstream ss;

	std::string eop = isDigraph ? "->" : "--";

	auto qoute = [](std::string_view id) {
		return "\"" + std::string(id) + "\"";
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

		if (attrs.size() > 1) {
			print_indent() << head << " [" << std::endl;
			indent++;
			for (const auto& [key, value] : attrs)
				print_indent() << key << " = " << "\"" << value << "\"" << std::endl;
			indent--;
			print_indent() << "]" << std::endl;
		}
		else {
			const auto& [key, value] = *attrs.begin();
			print_indent() << head << " [ " << key << " = " << "\"" << value << "\" ]" << std::endl;
		}
	};

	dumpAttrs("graph", graphAttrs);
	dumpAttrs("node", graphNodeAttrs);
	dumpAttrs("edge", graphEdgeAttrs);

	for (const auto& subgraph : subgraphs)
		ss << subgraph->Dump(true, isDigraph, indent);

	const auto& nodeIDs = registry->GetNodes();
	const auto& edgeIDs = registry->GetEdges();
	const auto& nodeAttrs = registry->GetNodeAttrs();
	const auto& edgeAttrs = registry->GetEdgeAttrs();

	for (size_t nodeIndex : nodeIndices) {
		const auto& nodeID = nodeIDs[nodeIndex];
		auto target = nodeAttrs.find(nodeIndex);
		if (target == nodeAttrs.end())
			print_indent() << qoute(nodeID) << std::endl;
		else
			dumpAttrs(qoute(nodeID), target->second);
	}

	for (size_t edgeIndex : edgeIndices) {
		const auto& [lhs, rhs] = edgeIDs[edgeIndex];
		std::string head = qoute(nodeIDs[lhs]) + " " + eop + " " + qoute(nodeIDs[rhs]);
		auto target = edgeAttrs.find(edgeIndex);
		if (target == edgeAttrs.end())
			print_indent() << head << std::endl;
		else
			dumpAttrs(head, target->second);
	}

	indent--;
	print_indent() << "}" << std::endl;

	return ss.str();
}
