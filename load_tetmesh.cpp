/* ==========================================================================
   ========================================================================== */
#include <CGAL/Linear_cell_complex.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Cartesian.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/* If you do not want to use a viewer, you can comment the following file. */
#include "linear_cell_complex_3_viewer_qt.h"

/* ==========================================================================
   ========================================================================== */
typedef CGAL::Cartesian<double>                     Kernel;
typedef CGAL::Linear_cell_complex_traits<3, Kernel> Traits;
typedef CGAL::Linear_cell_complex<3, 3, Traits>     LCC_3;
typedef LCC_3::Dart_handle                          Dart_handle;
typedef LCC_3::Point                                Point;

/* ==========================================================================
   ========================================================================== */
bool read_mesh(LCC_3& lcc, const char* _filename)
{
  size_t i, num_vertices, num_tetras;
  std::vector<Point> points;
  std::string line;
  std::stringstream sStream;
  
  // try to open the file
  std::ifstream fin(_filename);
  if(!fin) return false;
  
  // load number of vertices

  // skip Vertices label
  std::getline(fin, line);
  
  std::getline(fin, line); // num_vertices x
  sStream << line;
  sStream >> num_vertices;
  sStream.clear();
  
  // reverse the order of the vertices
  points.reserve(num_vertices);
  
  for(i = 0; i < num_vertices; ++i)
  {
    float x, y, z;
    std::getline(fin, line);
    sStream << line;
    sStream >> x >> y >> z;
    std::getline(sStream, line);
    sStream.clear();
    
    points.push_back(LCC_3::Point(x,y,z));
  }
  
  // skip Tetrahedra label
  std::getline(fin, line);
  
  // read number of tetraeders
  std::getline(fin, line); // num_tetras x
  sStream << line;
  sStream >> num_tetras;
  sStream.clear();
  
  
  for(i = 0; i < num_tetras; ++i)
  {
    int v0,v1,v2,v3;
    std::getline(fin, line);
    sStream << line;
    sStream >> v0 >> v1 >> v2 >> v3;
    std::getline(sStream, line);
    sStream.clear();
    
    Dart_handle dart=
      lcc.make_tetrahedron(points[v0-1], points[v1-1], points[v2-1], points[v3-1]);
  }
  
  lcc.sew3_same_facets();
  
  fin.close();
  return true;
}
/* ==========================================================================
   ========================================================================== */
int main(int narg, char** argv)
{
  if (narg<2 || (!strcmp(argv[1],"-h") || !strcmp(argv[1],"-?")) )
  {
    std::cout<<"Usage : load_tetmesh filename"<<std::endl   
             <<"   filename being an '.tetmesh' file."<<std::endl;
    return EXIT_FAILURE;
  }

  LCC_3 lcc;
  
  if ( !read_mesh(lcc, argv[1]) )
  {
    std::cout<<"Error : problem reading file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
  }
  
  lcc.display_characteristics(std::cout) << ", valid=" 
                                         << lcc.is_valid() << std::endl;

  /* If you do not want to use a viewer, you can comment the following file. */
  // display_lcc(lcc);

  return EXIT_SUCCESS;
}

