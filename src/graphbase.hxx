/*
 *  Copyright (C)  2014  Pierre Marchand <pierremarc07@gmail.com>
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
 */


#ifndef PGGRAPH_GRAPHBASE_HXX
#define PGGRAPH_GRAPHBASE_HXX

#include "vertexbase.hxx"
#include "edgebase.hxx"
#include "iterators.hxx"
#include <boost/format.hpp>

namespace pggraph {


class GraphBase
{
    PqIterator<Edge>* m_edges;
    PqIterator<Vertex>* m_vertices;

public:

    static boost::format outEdgeQueryFormat;

    GraphBase();
    GraphBase(PqIterator<Edge> eit, PqIterator<Vertex> vit);

    PqIterator<Edge>& edgeIter() const { return *m_edges; }
    PqIterator<Vertex>& vertexIter() const { return *m_vertices; }
};

} // namespace pggraph

#endif // PGGRAPH_GRAPHBASE_HXX
