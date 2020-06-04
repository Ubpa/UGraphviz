#pragma once

#include <unordered_map>
#include <unordered_set>

#include <string>

namespace Ubpa::Graphviz {
	class Subgraph {
	public:
		static constexpr size_t SelfIdx = static_cast<size_t>(0);

		Subgraph(std::string id) : id{ std::move(id) } {}

		const std::string& GetID() const noexcept { return id; }

		Subgraph& GetSubgraph(const std::string& subgraphID);

		Subgraph& AddGraphAttr(std::string key, std::string value);
		Subgraph& AddAllNodeAttr(std::string key, std::string value);
		Subgraph& AddAllEdgeAttr(std::string key, std::string value);

		Subgraph& AddSubgraph(Subgraph subgraph);

		Subgraph& AddNode(std::string nodeID);
		Subgraph& AddEdge(std::string lhs, std::string rhs);

		Subgraph& AddNodeAttr(const std::string& nodeID, std::string key, std::string value);
		Subgraph& AddEdgeAttr(const std::string& lhs, const std::string& rhs, std::string key, std::string value);

	protected:
		std::string Dump(bool isSub, bool isDigraph, size_t indent) const;

		std::string id;

		std::vector<std::pair<std::string, std::string>> graphAttrs;
		std::vector<std::pair<std::string, std::string>> allNodeAttrs;
		std::vector<std::pair<std::string, std::string>> allEdgeAttrs;

		std::unordered_map<std::string, Subgraph> subgraphs;

		std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> nodeAttrs;

		std::unordered_map<std::string, std::pair<std::string, std::string>> edges;
		std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> edgeAttrs;
	};

	class Graph : private Subgraph {
	public:
		Graph(std::string id, bool isDigraph = false);

		using Subgraph::GetID;
		using Subgraph::GetSubgraph;

		Graph& AddGraphAttr(std::string key, std::string value);
		Graph& AddAllNodeAttr(std::string key, std::string value);
		Graph& AddAllEdgeAttr(std::string key, std::string value);

		Graph& AddSubgraph(Subgraph subgraph);

		Graph& AddNode(std::string nodeID);
		Graph& AddEdge(std::string lhs, std::string rhs);

		Graph& AddNodeAttr(const std::string& nodeID, std::string key, std::string value);
		Graph& AddEdgeAttr(const std::string& lhs, const std::string& rhs, std::string key, std::string value);

		std::string Dump() const;

	private:
		bool isDigraph;
	};
}
