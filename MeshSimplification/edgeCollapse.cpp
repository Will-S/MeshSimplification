
#include "edgeCollapse.hpp"

#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>

EdgeCollapse::EdgeCollapse( LCC_3* lcc )
{
  m_lcc = lcc;
  m_edgeSelector = new EdgeSelection( lcc ); 
}

EdgeCollapse::~EdgeCollapse()
{
  delete m_edgeSelector;
}

void removeEdge( LCC_3* lcc, int edge )
{
  //std::cout<<edge<<std::endl; // show edge to remove
  // TODO: remove edge #edge
}

void EdgeCollapse::collapseEdges(int collapseRate)
{
  std::vector<int> edgesToRemove = m_edgeSelector->selectEdgesRandom(collapseRate);

  for( int i=0; i<edgesToRemove.size(); i++ )
  {
    removeEdge( m_lcc, edgesToRemove[i] );
  }
} 
