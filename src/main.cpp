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

#include <iostream>

#include "adaptor.hxx"

int main(int, char*[])
{
    std::string dn("host=127.0.0.1 user=pierre password=plokplok dbname=geo0");

    pggraph::CursorProvider::create(dn);

    std::string edgesQuery("SELECT * from madein_connection;");
    std::string verticesQuery("select distinct on (content_type_left_id, object_id_left) * from madein_connection  ORDER BY content_type_left_id, object_id_left;");

    pggraph::PqIterator<pggraph::Edge> edgeIter(edgesQuery);
    pggraph::PqIterator<pggraph::Vertex> vertexIter(verticesQuery);


    pggraph::GraphBase g(edgeIter, vertexIter);
    std::cout << "Hello Graph!" << std::endl;
    return 0;
}

