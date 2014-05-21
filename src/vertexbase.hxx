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


#ifndef PGGRAPH_VERTEXBASE_HXX
#define PGGRAPH_VERTEXBASE_HXX

#undef PQXX_BROKEN_ITERATOR
#include <pqxx/pqxx>

namespace pggraph {


class VertexBase
{
    unsigned int typeId;
    unsigned long entityId;
public:

    enum vertex_transform_side{TRANSFORM_SOURCE, TRANSFORM_TARGET};

    VertexBase();
    VertexBase(unsigned int tid, unsigned long eid);
    VertexBase(const VertexBase&);

    static VertexBase transform(const pqxx::result&, vertex_transform_side vts = TRANSFORM_SOURCE);

    bool operator==(const VertexBase& other){
        return ((typeId == other.typeId)
                && (entityId = other.entityId));
    }

    bool operator!=(const VertexBase& other){
        return !((*this) == other);
    }
};

typedef VertexBase Vertex;

} // namespace pggraph

#endif // PGGRAPH_VERTEXBASE_HXX
