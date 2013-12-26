
#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>

#include "edgeSelection.hpp"

EdgeSelection::EdgeSelection( LCC_3* lcc, int nbVertices )
{
  m_lcc = lcc;
  m_nbVertices = nbVertices ;
}

EdgeSelection::~EdgeSelection()
{
  
}

void EdgeSelection::selectEdgesRandom()
{
  //m_nbVertices;
}

void EdgeSelection::selectEdgesMetric()
{
  //m_nbVertices;
}
