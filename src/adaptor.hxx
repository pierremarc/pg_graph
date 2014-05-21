/**
 *  Copyright (C) 2014  Pierre Marchand <pierremarc07@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU  General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU  General Public License for more details.
 *
 *  You should have received a copy of the GNU  General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */


#ifndef PGGRAPH_ADAPTOR_H
#define PGGRAPH_ADAPTOR_H

#include <utility>
#include "graphbase.hxx"
#include <boost/graph/graph_traits.hpp>

namespace boost {



template<>
struct graph_traits< pggraph::GraphBase >
{
    typedef directed_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category;
    typedef incidence_graph_tag traversal_category;

    typedef unsigned long vertices_size_type;
    typedef unsigned long edges_size_type;
    typedef unsigned long degree_size_type;


    typedef pggraph::Vertex vertex_descriptor;
    typedef pggraph::Edge edge_descriptor;
    typedef pggraph::PqIterator<pggraph::Edge>  out_edge_iterator;
};


typedef graph_traits< pggraph::GraphBase > PqGraph;


inline std::pair<
    typename PqGraph::out_edge_iterator,
    typename PqGraph::out_edge_iterator >
out_edges(
        PqGraph::vertex_descriptor u,
        const pggraph::GraphBase& g)
{
    return std::make_pair(g.edgeIter().begin(), g.edgeIter().end());
}

PqGraph::vertex_descriptor
source(
        PqGraph::edge_descriptor e,
        const pggraph::GraphBase& /*g*/)
{
    return e.source();
}

PqGraph::vertex_descriptor
target(
        PqGraph::edge_descriptor e,
        const pggraph::GraphBase& /*g*/)
{
    return e.target();
}




} // namespace boost


#endif // PGGRAPH_ADAPTOR_H
