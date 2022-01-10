#include <UGraphviz/Subgraph.hpp>

#include <UGraphviz/Registry.hpp>

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

Subgraph& Subgraph::UnregisterGraphAttr(std::string_view key) {
	graphAttrs.erase(graphAttrs.find(key));
	return *this;
}

Subgraph& Subgraph::UnregisterGraphNodeAttr(std::string_view key) {
	graphNodeAttrs.erase(graphNodeAttrs.find(key));
	return *this;
}

Subgraph& Subgraph::UnregisterGraphEdgeAttr(std::string_view key) {
	graphEdgeAttrs.erase(graphEdgeAttrs.find(key));
	return *this;
}

Subgraph& Subgraph::GenSubgraph(std::string ID) {
	subgraphID2idx[ID] = subgraphs.size();
	auto newSubGraph = new Subgraph{ registry, std::move(ID) };
	subgraphs.push_back(newSubGraph);
	return *subgraphs.back();
}

bool Subgraph::HaveNode(std::size_t nodeIndex) const {
	return nodeIndices.find(nodeIndex) != nodeIndices.end();
}

bool Subgraph::HaveEdge(std::size_t edgeIndex) const {
	return edgeIndices.find(edgeIndex) != edgeIndices.end();
}

Subgraph& Subgraph::AddNode(std::size_t nodeIndex) {
	nodeIndices.insert(nodeIndex);
	return *this;
}

Subgraph& Subgraph::AddEdge(std::size_t edgeIndex) {
	edgeIndices.insert(edgeIndex);
	return *this;
}

Subgraph& Subgraph::EraseNode(std::size_t nodeIndex) {
	nodeIndices.erase(nodeIndex);
	return *this;
}

Subgraph& Subgraph::EraseEdge(std::size_t edgeIndex) {
	edgeIndices.erase(edgeIndex);
	return *this;
}

std::string Subgraph::Dump(bool isSub, bool isDigraph, std::size_t indent) const {
	constexpr const char* compass2name[] = {
		"n","ne","e","se","s","sw","w","nw","c"
	};

	if (!isSub && subgraphs.empty() && nodeIndices.empty() && edgeIndices.empty())
		return "";

	const auto& nodeIDs = registry->GetNodes();
	const auto& edgeIDs = registry->GetEdges();
	const auto& nodeAttrs = registry->GetNodeAttrs();
	const auto& edgeAttrs = registry->GetEdgeAttrs();
	const auto& edgePorts = registry->GetEdgePorts();

	std::stringstream ss;

	std::string eop = isDigraph ? "->" : "--";

	auto qoute = [](std::string_view id) {
		return "\"" + std::string(id) + "\"";
	};

	auto print_indent = [&]() -> std::stringstream& {
		for (std::size_t i = 0; i < indent; i++)
			ss << "  ";
		return ss;
	};

	auto dump_edge = [&, compass2name](size_t idx) {
		const auto& [lhs, rhs] = edgeIDs[idx];
		std::string str;

		str += qoute(nodeIDs[lhs]);
		if (edgePorts.contains(idx)) {
			const auto& port = edgePorts.at(idx);
			if (!port.first.ID.empty())
				str += ":" + qoute(port.first.ID);
			if (port.first.compass != Registry::Port::Compass::None) {
				str += ":";
				str += compass2name[static_cast<int>(port.first.compass)];
			}
		}
		str += " " + eop + " ";

		str += qoute(nodeIDs[rhs]);
		if (edgePorts.contains(idx)) {
			const auto& port = edgePorts.at(idx);
			if (!port.second.ID.empty())
				str += ":" + qoute(port.second.ID);
			if (port.second.compass != Registry::Port::Compass::None) {
				constexpr const char* compass2name[] = {
					"n","ne","e","se","s","sw","w","nw","c"
				};
				str += ":";
				str += compass2name[static_cast<int>(port.second.compass)];
			}
		}

		return str;
	};

	print_indent();

	if (isSub)
		ss << "sub";

	ss << "graph " << qoute(id) << " {" << std::endl;

	indent++;

	auto dumpAttrs = [&, compass2name](std::string_view head, const auto& attrs) {
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

	for (std::size_t nodeIndex : nodeIndices) {
		const auto& nodeID = nodeIDs[nodeIndex];
		auto target = nodeAttrs.find(nodeIndex);
		if (target == nodeAttrs.end())
			print_indent() << qoute(nodeID) << std::endl;
		else
			dumpAttrs(qoute(nodeID), target->second);
	}

	for (std::size_t edgeIndex : edgeIndices) {
		std::string head = dump_edge(edgeIndex);
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
