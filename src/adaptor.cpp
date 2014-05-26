
#include "adaptor.hxx"
#include <boost/graph/graph_concepts.hpp>

namespace boost {

std::string edgesQueryString(unsigned int tid, unsigned long eid){
    pggraph::GraphBase::outEdgeQueryFormat % tid % eid;
    return pggraph::GraphBase::outEdgeQueryFormat.str();
}


typename PqGraph::vertices_size_type
num_vertices(const pggraph::GraphBase& g)
{
    return g.vertexIter().end().getPos();
}


typename PqGraph::vertex_descriptor
source(
        PqGraph::edge_descriptor e,
        const pggraph::GraphBase& /*g*/)
{
    return e.source();
}

typename PqGraph::vertex_descriptor
target(
        PqGraph::edge_descriptor e,
        const pggraph::GraphBase& /*g*/)
{
    return e.target();
}

typename PqGraph::degree_size_type
out_degree(
        PqGraph::vertex_descriptor u,
           const pggraph::GraphBase& g)
{
    pggraph::PqIterator<PqGraph::vertex_descriptor> iter(edgesQueryString(u.getType(), u.getEntity()));
    return iter.end().getPos();
}



//    BOOST_CONCEPT_ASSERT(( boost::concepts::IncidenceGraph<pggraph::GraphBase> )) ;
//    BOOST_CONCEPT_ASSERT(( boost::concepts::VertexListGraph<pggraph::GraphBase> )) ;

}
