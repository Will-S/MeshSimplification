#ifndef EDGESELECTION_H
#define EDGESELECTION_H

#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>
#include <CGAL/Cartesian.h>

typedef CGAL::Cartesian<double>                     Kernel;
typedef CGAL::Linear_cell_complex_traits<3, Kernel> Traits;
typedef CGAL::Linear_cell_complex<2, 3, Traits>     LCC_3;

class EdgeSelection
{
public:
  EdgeSelection( LCC_3* lcc, int nbVertices );
  ~EdgeSelection();
  void selectEdgesRandom();
  void selectEdgesMetric();
  
private:
  LCC_3* m_lcc;
  int m_nbVertices;
};

#endif
