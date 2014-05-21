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


#include "edgebase.hxx"

namespace pggraph {

const unsigned int dui(0);
const unsigned long dul(0);

EdgeBase::EdgeBase()
    :typeId(dui), entityId(dul)
{
}

EdgeBase::EdgeBase(unsigned int tid, unsigned long eid,
                   const Vertex& source, const Vertex& target)
    :typeId(tid), entityId(eid), m_source(source), m_target(target)
{
}

EdgeBase::EdgeBase(const EdgeBase& other)
{
    typeId = other.typeId;
    entityId = other.typeId;
    m_source = other.source();
    m_target = other.target();
}

Vertex EdgeBase::source() const{
    return m_source;
}

Vertex EdgeBase::target() const{
    return m_target;
}

EdgeBase EdgeBase::transform(const pqxx::result& res){
    Vertex s = Vertex::transform(res);
    Vertex t = Vertex::transform(res, Vertex::TRANSFORM_TARGET);
    return EdgeBase(res[0][1].as(dui), res[0][0].as(dul), s, t);
}

} // namespace pggraph
