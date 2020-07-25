#include <UGraphviz/Registry.h>

#include <cassert>

using namespace Ubpa::UGraphviz;


bool Registry::IsRegisteredNode(const std::string& ID) const {
	return id2idx.find(ID) != id2idx.end();
}

bool Registry::IsRegisteredEdge(size_t lhs, size_t rhs) const {
	auto target_lhs = node2edge.find(lhs);
	if (target_lhs == node2edge.end())
		return false;

	auto target_rhs = target_lhs->second.find(rhs);
	if (target_rhs == target_lhs->second.end())
		return false;

	return true;
}

bool Registry::IsRegisteredEdge(const std::string& lhsID, const std::string& rhsID) const {
	size_t lhs = GetNodeIdx(lhsID);
	size_t rhs = GetNodeIdx(rhsID);

	return IsRegisteredEdge(lhs, rhs);
}

size_t Registry::GetNodeIdx(const std::string& ID) const {
	assert(IsRegisteredNode(ID));
	return id2idx.find(ID)->second;
}

size_t Registry::GetEdgeIdx(const std::string& lhsID, const std::string& rhsID) const {
	size_t lhs = GetNodeIdx(lhsID);
	size_t rhs = GetNodeIdx(rhsID);
	
	assert(IsRegisteredEdge(lhs, rhs));

	return node2edge.find(lhs)->second.find(rhs)->second;
}

size_t Registry::RegisterNode(std::string ID) {
	size_t idx = nodes.size();
	id2idx[ID] = idx;
	nodes.push_back(std::move(ID));
	return idx;
}

size_t Registry::RegisterEdge(size_t lhs, size_t rhs) {
	size_t idx = edges.size();
	edges.emplace_back(lhs, rhs);
	node2edge[lhs][rhs] = idx;
	return idx;
}

Registry& Registry::RegisterNodeAttr(size_t nodeIdx, std::string key, std::string value) {
	nodeAttrs[nodeIdx].emplace(std::move(key), std::move(value));
	return *this;
}

Registry& Registry::RegisterEdgeAttr(size_t edgeIdx, std::string key, std::string value) {
	edgeAttrs[edgeIdx].emplace(std::move(key), std::move(value));
	return *this;
}

Registry& Registry::DeregisterNodeAttr(size_t nodeIdx, const std::string& key) {
	nodeAttrs[nodeIdx].erase(key);
	return *this;
}

Registry& Registry::DeregisterEdgeAttr(size_t edgeIdx, const std::string& key) {
	edgeAttrs[edgeIdx].erase(key);
	return *this;
}
