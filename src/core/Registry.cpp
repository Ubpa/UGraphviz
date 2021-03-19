#include <UGraphviz/Registry.hpp>

#include <cassert>

using namespace Ubpa::UGraphviz;

bool Registry::IsRegisteredNode(std::string_view ID) const {
	return id2idx.find(ID) != id2idx.end();
}

bool Registry::IsRegisteredEdge(std::size_t lhs, std::size_t rhs) const {
	auto target_lhs = node2edge.find(lhs);
	if (target_lhs == node2edge.end())
		return false;

	auto target_rhs = target_lhs->second.find(rhs);
	if (target_rhs == target_lhs->second.end())
		return false;

	return true;
}

bool Registry::IsRegisteredEdge(std::string_view lhsID, std::string_view rhsID) const {
	std::size_t lhs = GetNodeIndex(lhsID);
	std::size_t rhs = GetNodeIndex(rhsID);

	return IsRegisteredEdge(lhs, rhs);
}

std::size_t Registry::GetNodeIndex(std::string_view ID) const {
	assert(IsRegisteredNode(ID));
	return id2idx.find(ID)->second;
}

std::size_t Registry::GetEdgeIndex(std::string_view lhsID, std::string_view rhsID) const {
	std::size_t lhs = GetNodeIndex(lhsID);
	std::size_t rhs = GetNodeIndex(rhsID);
	
	assert(IsRegisteredEdge(lhs, rhs));

	return node2edge.find(lhs)->second.find(rhs)->second;
}

std::size_t Registry::RegisterNode(std::string ID) {
	std::size_t idx = nodes.size();
	id2idx[ID] = idx;
	nodes.push_back(std::move(ID));
	return idx;
}

std::size_t Registry::RegisterEdge(std::size_t lhs, std::size_t rhs) {
	std::size_t idx = edges.size();
	edges.emplace_back(lhs, rhs);
	node2edge[lhs][rhs] = idx;
	return idx;
}

Registry& Registry::RegisterNodeAttr(std::size_t nodeIndex, std::string key, std::string value) {
	nodeAttrs[nodeIndex].emplace(std::move(key), std::move(value));
	return *this;
}

Registry& Registry::RegisterEdgeAttr(std::size_t edgeIndex, std::string key, std::string value) {
	edgeAttrs[edgeIndex].emplace(std::move(key), std::move(value));
	return *this;
}

Registry& Registry::DeregisterNodeAttr(std::size_t nodeIndex, std::string_view key) {
	nodeAttrs[nodeIndex].erase(nodeAttrs[nodeIndex].find(key));
	return *this;
}

Registry& Registry::DeregisterEdgeAttr(std::size_t edgeIndex, std::string_view key) {
	edgeAttrs[edgeIndex].erase(edgeAttrs[edgeIndex].find(key));
	return *this;
}
