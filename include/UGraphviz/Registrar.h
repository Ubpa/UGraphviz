#pragma once

#include <unordered_map>

#include <string>

namespace Ubpa::Graphviz {
	class Registrar {
	public:
		Registrar() = default;

		const std::vector<std::string>& GetNodes() const noexcept { return nodes; }
		const std::vector<std::pair<size_t, size_t>>& GetEdges() const noexcept { return edges; }

		const std::unordered_map<size_t, std::unordered_map<std::string, std::string>>&
		GetNodeAttrs() const noexcept { return nodeAttrs; }
		const std::unordered_map<size_t, std::unordered_map<std::string, std::string>>&
		GetEdgeAttrs() const noexcept { return edgeAttrs; }

		bool IsRegisteredNode(const std::string& ID) const;
		bool IsRegisteredEdge(const std::string& lhsID, const std::string& rhsID) const;
		
		size_t GetNodeIdx(const std::string& ID) const;
		size_t GetEdgeIdx(const std::string& lhsID, const std::string& rhsID) const;

		size_t RegisterNode(std::string ID);
		size_t RegisterEdge(size_t lhs, size_t rhs);

		Registrar& RegisterNodeAttr(size_t nodeIdx, std::string key, std::string value);
		Registrar& RegisterEdgeAttr(size_t edgeIdx, std::string key, std::string value);

		Registrar& DeregisterNodeAttr(size_t nodeIdx, const std::string& key);
		Registrar& DeregisterEdgeAttr(size_t edgeIdx, const std::string& key);

	private:
		Registrar(const Registrar&) = delete;
		Registrar(Registrar&&) = delete;
		Registrar& operator=(const Registrar&) = delete;
		Registrar& operator=(Registrar&&) = delete;

		std::vector<std::string> nodes;
		std::unordered_map<std::string, size_t> id2idx;
		std::unordered_map<size_t, std::unordered_map<std::string, std::string>> nodeAttrs;

		std::vector<std::pair<size_t, size_t>> edges;
		std::unordered_map<size_t, std::unordered_map<size_t, size_t>> node2edge;
		std::unordered_map<size_t, std::unordered_map<std::string, std::string>> edgeAttrs;
	};
}
