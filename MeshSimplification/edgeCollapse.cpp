
#include "edgeCollapse.hpp"

#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>

EdgeCollapse::EdgeCollapse( LCC_3* lcc, int nbVertices )
{
  m_lcc = lcc;
  m_nbVertices = nbVertices;
  std::cout<<m_nbVertices<<" vertices output"<<std::endl;

  m_edgeSelector = new EdgeSelection( lcc, nbVertices ); 
}

EdgeCollapse::~EdgeCollapse()
{
  
}
  
void EdgeCollapse::collapseEdges()
{
  m_edgeSelector->selectEdgesRandom();
} 
