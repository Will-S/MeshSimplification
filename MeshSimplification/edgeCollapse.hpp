#ifndef EDGECOLLAPSE_H
#define EDGECOLLAPSE_H

#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Cartesian.h>

typedef CGAL::Cartesian<double>                     Kernel;
typedef CGAL::Linear_cell_complex_traits<3, Kernel> Traits;
typedef CGAL::Linear_cell_complex<2, 3, Traits>     LCC_3;

#include "edgeSelection.hpp"

class EdgeCollapse
{
public:
  EdgeCollapse( LCC_3* lcc );
  ~EdgeCollapse();
  void collapseEdges(int collapseRate);
  
private:
  LCC_3* m_lcc;
  EdgeSelection* m_edgeSelector;
};

#endif
