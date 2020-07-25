#pragma once

#include <unordered_map>

#include <string>

namespace Ubpa::UGraphviz {
	class Registry {
	public:
		Registry() = default;

		const std::vector<std::string>& GetNodes() const noexcept { return nodes; }
		const std::vector<std::pair<size_t, size_t>>& GetEdges() const noexcept { return edges; }

		using ElemAttrMap = std::unordered_map<size_t, std::unordered_map<std::string, std::string>>;

		const ElemAttrMap& GetNodeAttrs() const noexcept { return nodeAttrs; }
		const ElemAttrMap& GetEdgeAttrs() const noexcept { return edgeAttrs; }

		bool IsRegisteredNode(const std::string& ID) const;
		bool IsRegisteredEdge(size_t lhs, size_t rhs) const;
		bool IsRegisteredEdge(const std::string& lhsID, const std::string& rhsID) const;
		
		size_t GetNodeIndex(const std::string& ID) const;
		size_t GetEdgeIndex(const std::string& lhsID, const std::string& rhsID) const;

		size_t RegisterNode(std::string ID);
		size_t RegisterEdge(size_t lhs, size_t rhs);

		Registry& RegisterNodeAttr(size_t nodeIndex, std::string key, std::string value);
		Registry& RegisterEdgeAttr(size_t edgeIndex, std::string key, std::string value);

		Registry& DeregisterNodeAttr(size_t nodeIndex, const std::string& key);
		Registry& DeregisterEdgeAttr(size_t edgeIndex, const std::string& key);

	private:
		Registry(const Registry&) = delete;
		Registry(Registry&&) = delete;
		Registry& operator=(const Registry&) = delete;
		Registry& operator=(Registry&&) = delete;

		std::vector<std::string> nodes;
		std::unordered_map<std::string, size_t> id2idx;
		ElemAttrMap nodeAttrs;

		std::vector<std::pair<size_t, size_t>> edges;
		std::unordered_map<size_t, std::unordered_map<size_t, size_t>> node2edge;
		ElemAttrMap edgeAttrs;
	};
}
