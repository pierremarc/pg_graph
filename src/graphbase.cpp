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


#include "graphbase.hxx"

namespace pggraph {

boost::format
GraphBase::outEdgeQueryFormat = boost::format("SELECT * FROM madein_connection WHERE content_type_left_id = %1% AND object_id_left = %2%");

GraphBase::GraphBase()
{
}

GraphBase::GraphBase(PqIterator<Edge> eit, PqIterator<Vertex> vit)
    :m_edges(&eit), m_vertices(&vit)
{

}

} // namespace pggraph
