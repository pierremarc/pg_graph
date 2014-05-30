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


#include "vertexbase.hxx"

namespace pggraph {

const unsigned int dui(0);
const unsigned long dul(0);

VertexBase::VertexBase()
    :typeId(dui), entityId(dul)
{
}

VertexBase::VertexBase(unsigned int tid, unsigned long eid)
    :typeId(tid), entityId(eid)
{

}

VertexBase::VertexBase(const VertexBase& other)
{
    typeId = other.typeId;
    entityId = other.entityId;
}


VertexBase VertexBase::transform(const pqxx::result& res,
                                 vertex_transform_side vts)
{
    if(TRANSFORM_TARGET == vts)
    {
        return VertexBase(res[0][4].as(dui), res[0][5].as(dul));
    }
    return VertexBase(res[0][2].as(dui), res[0][3].as(dul));
}

} // namespace pggraph
