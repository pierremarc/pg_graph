
#include "adaptor.hxx"
#include <boost/graph/graph_concepts.hpp>

namespace boost {

    BOOST_CONCEPT_ASSERT(( boost::concepts::IncidenceGraph<pggraph::GraphBase> )) ;

}
