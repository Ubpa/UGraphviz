#include <UGraphviz/Graph.h>

#include <UGraphviz/Registrar.h>

#include <sstream>

#include <cassert>

using namespace Ubpa::Graphviz;

Graph::Graph(std::string id, bool isDigraph)
	: Subgraph{ new Registrar, std::move(id) }, isDigraph{ isDigraph } {}

Graph::~Graph() {
	delete registrar;
}

std::string Graph::Dump() const {
	std::stringstream ss;

	ss << "strict ";

	if (isDigraph)
		ss << "di";

	ss << Subgraph::Dump(false, isDigraph, 0);

	return ss.str();
}

Graph::Graph(Graph&& g) noexcept
	: Subgraph{ std::move(g) }, isDigraph{ g.isDigraph }
{
	g.registrar = nullptr;
}

Graph& Graph::operator=(Graph&& g) noexcept {
	Subgraph::operator=(std::move(g));
	isDigraph = g.isDigraph;
	g.registrar = nullptr;
	return *this;
}
