#pragma once

#include <map>
#include <string>
#include <vector>

namespace Ubpa::UGraphviz {
	class Registry {
	public:
		Registry() = default;

		struct Port {
			enum class Compass {
				N,    // n
				NE,   // ne
				E,    // e
				SE,   // se
				S,    // s
				SW,   // sw
				W,    // w
				NW,   // nw
				C,    // c
				None,
			};

			std::string ID;
			Compass compass{ Compass::None };
		};

		const std::vector<std::string>& GetNodes() const noexcept { return nodes; }
		const std::vector<std::pair<std::size_t, std::size_t>>& GetEdges() const noexcept { return edges; }

		using ElemAttrMap = std::map<std::size_t, std::map<std::string, std::string, std::less<>>>;
		using EdgePortMap = std::map<size_t, std::pair<Port, Port>>;
		using DstNodeEdgeIdxMap = std::multimap<std::size_t, std::size_t>;

		const ElemAttrMap& GetNodeAttrs() const noexcept { return nodeAttrs; }
		const ElemAttrMap& GetEdgeAttrs() const noexcept { return edgeAttrs; }
		const EdgePortMap& GetEdgePorts() const noexcept { return edgePorts; }

		bool IsRegisteredNode(std::string_view ID) const;
		bool IsRegisteredEdge(std::size_t lhs, std::size_t rhs) const;
		bool IsRegisteredEdge(std::string_view lhsID, std::string_view rhsID) const;
		
		std::size_t GetNodeIndex(std::string_view ID) const;
		std::pair<DstNodeEdgeIdxMap::const_iterator, DstNodeEdgeIdxMap::const_iterator>
		GetEdgeIndexRange(std::string_view lhsID, std::string_view rhsID) const;

		std::size_t RegisterNode(std::string ID);
		std::size_t RegisterEdge(std::size_t lhs, std::size_t rhs);

		Registry& RegisterNodeAttr(std::size_t nodeIndex, std::string key, std::string value);
		Registry& RegisterEdgeAttr(std::size_t edgeIndex, std::string key, std::string value);

		Registry& RegisterEdgePort(std::size_t edgeIndex, Port srcPort, Port dstPort);

		Registry& UnregisterNodeAttr(std::size_t nodeIndex, std::string_view key);
		Registry& UnregisterEdgeAttr(std::size_t edgeIndex, std::string_view key);
		Registry& UnregisterEdgePort(std::size_t edgeIndex);

	private:
		Registry(const Registry&) = delete;
		Registry(Registry&&) = delete;
		Registry& operator=(const Registry&) = delete;
		Registry& operator=(Registry&&) = delete;

		std::vector<std::string> nodes;
		std::map<std::string, std::size_t, std::less<>> id2idx;
		ElemAttrMap nodeAttrs;

		std::vector<std::pair<std::size_t, std::size_t>> edges;
		
		std::map<std::size_t, std::multimap<std::size_t, std::size_t>, std::less<>> node2edge;
		ElemAttrMap edgeAttrs;
		std::map<size_t, std::pair<Port, Port>> edgePorts;
	};
}
