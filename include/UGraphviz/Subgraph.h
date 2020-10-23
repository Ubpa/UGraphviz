#pragma once

#include <map>
#include <unordered_set>
#include <vector>
#include <string>

namespace Ubpa::UGraphviz {
	class Registry;

	class Subgraph {
	public:
		Subgraph(Registry* registry, std::string id)
			: registry{ registry }, id{ std::move(id) } {}

		~Subgraph();

		std::string_view GetID() const noexcept { return id; }

		Subgraph& GetSubgraph(std::string_view subgraphID);

		Registry& GetRegistry() { return *registry; }

		// return new subgraph
		Subgraph& GenSubgraph(std::string ID);

		// return *this
		Subgraph& RegisterGraphAttr(std::string key, std::string value);
		Subgraph& RegisterGraphNodeAttr(std::string key, std::string value);
		Subgraph& RegisterGraphEdgeAttr(std::string key, std::string value);

		Subgraph& DeregisterGraphAttr(std::string_view key);
		Subgraph& DeregisterGraphNodeAttr(std::string_view key);
		Subgraph& DeregisterGraphEdgeAttr(std::string_view key);

		bool HaveNode(size_t nodeIndex) const;
		bool HaveEdge(size_t edgeIndex) const;
		Subgraph& AddNode(size_t nodeIndex);
		Subgraph& AddEdge(size_t edgeIndex);
		Subgraph& EraseNode(size_t nodeIndex);
		Subgraph& EraseEdge(size_t edgeIndex);

	protected:
		Subgraph(Subgraph&&) = default;
		Subgraph& operator=(Subgraph&&) noexcept = default;

		std::string Dump(bool isSub, bool isDigraph, size_t indent) const;

		Registry* registry;

	private:
		std::string id;

		std::map<std::string, std::string, std::less<>> graphAttrs;
		std::map<std::string, std::string, std::less<>> graphNodeAttrs;
		std::map<std::string, std::string, std::less<>> graphEdgeAttrs;

		std::vector<Subgraph*> subgraphs;
		std::map<std::string, size_t, std::less<>> subgraphID2idx;

		std::unordered_set<size_t> nodeIndices;
		std::unordered_set<size_t> edgeIndices;
	};
}
