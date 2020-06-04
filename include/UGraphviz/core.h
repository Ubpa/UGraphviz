#pragma once

#include <unordered_map>

#include <string>

namespace Ubpa::Graphviz {
	class SubGraph {
	public:
		SubGraph(std::string id) : id{ std::move(id) } {}

		const std::string& GetID() const noexcept { return id; }

		size_t GetNodeIdx(const std::string& nodeID) const;

		SubGraph& AddGraphAttr(std::string key, std::string value);
		SubGraph& AddAllNodeAttr(std::string key, std::string value);
		SubGraph& AddAllEdgeAttr(std::string key, std::string value);

		size_t AddSubGraph(SubGraph subgraph);

		size_t AddNode(std::string nodeID);
		size_t AddEdge(size_t lhs, size_t rhs);

		SubGraph& AddNodeAttr(size_t nodeIdx, std::string key, std::string value);
		SubGraph& AddEdgeAttr(size_t edgeIdx, std::string key, std::string value);

	protected:
		std::string Dump(bool isSub, bool isDigraph, size_t indent) const;

		std::string id;

		std::vector<std::pair<std::string, std::string>> graphAttrs;
		std::vector<std::pair<std::string, std::string>> allNodeAttrs;
		std::vector<std::pair<std::string, std::string>> allEdgeAttrs;

		std::vector<SubGraph> subgraphs;

		std::vector<std::string> nodes;
		std::unordered_map<std::string, size_t> id2idx;
		std::unordered_map<size_t, std::vector<std::pair<std::string, std::string>>> nodeAttrs;

		std::vector<std::pair<size_t, size_t>> edges;
		std::unordered_map<size_t, std::vector<std::pair<std::string, std::string>>> edgeAttrs;
	};

	class Graph : private SubGraph {
	public:

		Graph(std::string id, bool isDigraph = false, bool isStrict = false);

		using SubGraph::GetID;
		using SubGraph::GetNodeIdx;
		using SubGraph::AddSubGraph;
		using SubGraph::AddNode;
		using SubGraph::AddEdge;

		Graph& AddGraphAttr(std::string key, std::string value);
		Graph& AddAllNodeAttr(std::string key, std::string value);
		Graph& AddAllEdgeAttr(std::string key, std::string value);

		Graph& AddNodeAttr(size_t nodeIdx, std::string key, std::string value);
		Graph& AddEdgeAttr(size_t edgeIdx, std::string key, std::string value);

		std::string Dump() const;

	private:
		bool isDigraph;
		bool isStrict;
	};
}
