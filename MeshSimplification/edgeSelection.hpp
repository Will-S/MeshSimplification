#ifndef EDGESELECTION_H
#define EDGESELECTION_H

#include <vector>

#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>
#include <CGAL/Cartesian.h>

typedef CGAL::Cartesian<double>                     Kernel;
typedef CGAL::Linear_cell_complex_traits<3, Kernel> Traits;
typedef CGAL::Linear_cell_complex<2, 3, Traits>     LCC_3;

class EdgeSelection
{
public:
  EdgeSelection( LCC_3* lcc );
  ~EdgeSelection();
  std::vector<int> selectEdgesRandom(int collapseRate);
  std::vector<int> selectEdgesMetric(int collapseRate);
  
private:
  LCC_3* m_lcc;
};

#endif
