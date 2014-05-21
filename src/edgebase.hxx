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


#ifndef PGGRAPH_EDGEBASE_HXX
#define PGGRAPH_EDGEBASE_HXX

#include <pqxx/pqxx>
//#include "iterators.hxx"
#include "vertexbase.hxx"

namespace pggraph {



class EdgeBase
{
    unsigned int typeId;
    unsigned long entityId;

    Vertex m_source;
    Vertex m_target;

public:
    EdgeBase();
    EdgeBase(unsigned int tid, unsigned long eid,
             const Vertex& source, const Vertex& target);
    EdgeBase(const EdgeBase&);

    static EdgeBase transform(const pqxx::result&);

    Vertex source() const;
    Vertex target() const;

    bool operator==(const EdgeBase& other){
        return (entityId = other.entityId);
    }

    bool operator!=(const EdgeBase& other){
        return (entityId != other.entityId);
    }
};


//typedef PqIterator<EdgeBase> EdgeIterator;
//typedef PqIterator<EdgeBase const> EdgeIteratorConst;
typedef EdgeBase Edge;

} // namespace pggraph

#endif // PGGRAPH_EDGEBASE_HXX
