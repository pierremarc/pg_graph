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
    pqxx::connection c("host=127.0.0.1 user=pierre password=plokplok dbname=geo0");
    pqxx::work w(c);


    std::string edgesQuery("SELECT * from madein_connection;");
    std::string verticesQuery("select distinct on (content_type_left_id, object_id_left) * from madein_connection  ORDER BY content_type_left_id, object_id_left;");

    std::string n1("orce");
    std::string n2("orcv");

    pggraph::OwnedReadCursor edgesCursor(w, edgesQuery, n1, false);
    pggraph::OwnedReadCursor verticesCursor(w, verticesQuery, n2, false);
    pggraph::PqIterator<pggraph::Edge> edgeIter(edgesCursor, 1000);
    pggraph::PqIterator<pggraph::Vertex> vertexIter(verticesCursor, 1000);
    pggraph::GraphBase g(edgeIter, vertexIter);
    std::cout << "Hello Graph!" << std::endl;
    return 0;
}

