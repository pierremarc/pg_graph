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


#include "iterators.hxx"


namespace pggraph {


boost::uuids::random_generator CursorHolder::tgenerator;
boost::hash<boost::uuids::uuid> CursorHolder::tuuid_hasher;

CursorProvider *CursorProvider::instance = 0;

void
CursorProvider::create(const std::string &dn)
{
    if(!instance){
        instance = new CursorProvider(dn);
    }
    else{
        throw ConnectionCreatedException();
    }
}

CursorProvider&
CursorProvider::getInstance()
{
    if(!instance){
        throw ConnectionNotCreatedException();
    }
    return *instance;
}

CursorHolder
CursorProvider::getCursor(const std::string& query)
{
     const CursorHolder c(getInstance().m_work, query);
     std::cerr << "CursorProvider::getCursor <= @"<< &c << std::endl;
     return c;
}


} // namespace pggraph

