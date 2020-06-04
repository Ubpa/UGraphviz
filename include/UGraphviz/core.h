#pragma once

#include <unordered_map>
#include <unordered_set>

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
		
		size_t GetNodeIdx(const std::string& ID) const {
			// assert(id2idx.find(ID) != id2idx.end());
			return id2idx.find(ID)->second;
		}

		size_t GetEdgeIdx(const std::string& lhsID, const std::string& rhsID) const {
			size_t lhs = GetNodeIdx(lhsID);
			size_t rhs = GetNodeIdx(rhsID);
			return node2edge.find(lhs)->second.find(rhs)->second;
		}

		size_t RegisterNode(std::string ID) {
			size_t idx = nodes.size();
			id2idx[ID] = idx;
			nodes.push_back(std::move(ID));
			return idx;
		}

		size_t RegisterEdge(size_t lhs, size_t rhs) {
			size_t idx = edges.size();
			edges.emplace_back(lhs, rhs);
			node2edge[lhs][rhs] = idx;
			return idx;
		}

		Registrar& RegisterNodeAttr(size_t nodeIdx, std::string key, std::string value) {
			nodeAttrs[nodeIdx].emplace(std::move(key), std::move(value));
			return *this;
		}

		Registrar& RegisterEdgeAttr(size_t edgeIdx, std::string key, std::string value) {
			edgeAttrs[edgeIdx].emplace(std::move(key), std::move(value));
			return *this;
		}

		Registrar& DeregisterNodeAttr(size_t nodeIdx, const std::string& key) {
			nodeAttrs[nodeIdx].erase(key);
			return *this;
		}

		Registrar& DeregisterEdgeAttr(size_t edgeIdx, const std::string& key) {
			edgeAttrs[edgeIdx].erase(key);
			return *this;
		}

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

	class Subgraph {
	public:
		Subgraph(Registrar* registrar, std::string id)
			: registrar{ registrar }, id{ std::move(id) } {}

		~Subgraph();

		const std::string& GetID() const noexcept { return id; }

		Subgraph& GetSubgraph(const std::string& subgraphID);

		Registrar& GetRegistrar() { return *registrar; }

		// return new subgraph
		Subgraph& GenSubgraph(std::string ID);

		// return *this
		Subgraph& RegisterGraphAttr(std::string key, std::string value);
		Subgraph& RegisterGraphNodeAttr(std::string key, std::string value);
		Subgraph& RegisterGraphEdgeAttr(std::string key, std::string value);

		Subgraph& DeregisterGraphAttr(const std::string& key);
		Subgraph& DeregisterGraphNodeAttr(const std::string& key);
		Subgraph& DeregisterGraphEdgeAttr(const std::string& key);

		bool HaveNode(size_t nodeIdx) const;
		bool HaveEdge(size_t edgeIdx) const;
		Subgraph& AddNode(size_t nodeIdx);
		Subgraph& AddEdge(size_t edgeIdx);
		Subgraph& EraseNode(size_t nodeIdx);
		Subgraph& EraseEdge(size_t edgeIdx);

	protected:
		std::string Dump(bool isSub, bool isDigraph, size_t indent) const;

		Registrar* registrar;
	private:
		Subgraph(const Subgraph&) = delete;
		Subgraph(Subgraph&&) = delete;
		Subgraph& operator=(const Subgraph&) = delete;
		Subgraph& operator=(Subgraph&&) = delete;

		std::string id;

		std::unordered_map<std::string, std::string> graphAttrs;
		std::unordered_map<std::string, std::string> graphNodeAttrs;
		std::unordered_map<std::string, std::string> graphEdgeAttrs;

		std::vector<Subgraph*> subgraphs;
		std::unordered_map<std::string, size_t> subgraphID2idx;

		std::unordered_set<size_t> nodeIndices;
		std::unordered_set<size_t> edgeIndices;
	};

	class Graph : public Subgraph {
	public:
		Graph(std::string id, bool isDigraph = false);
		~Graph();

		std::string Dump() const;

	private:
		bool isDigraph;
	};
}
