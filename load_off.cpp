/* ==========================================================================
   ========================================================================== */
#include <CGAL/Linear_cell_complex.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/IO/File_header_OFF.h>
#include <CGAL/IO/File_scanner_OFF.h>
#include <CGAL/Cartesian.h>
#include <iostream>
#include <fstream>

/* Projet classes */
#include "MeshSimplification/edgeCollapse.hpp"

/* If you do not want to use a viewer, you can comment the following file. */
#include "linear_cell_complex_3_viewer_qt.h"

/* ==========================================================================
   ========================================================================== */
typedef CGAL::Cartesian<double>                     Kernel;
typedef CGAL::Linear_cell_complex_traits<3, Kernel> Traits;
typedef CGAL::Linear_cell_complex<2, 3, Traits>     LCC_3;
typedef LCC_3::Dart_handle                          Dart_handle;
typedef LCC_3::Point                                Point;

/* ==========================================================================
   ========================================================================== */
template < class LCC >
void write_off(LCC& alcc, std::ostream& out)
{
  CGAL::File_header_OFF header(false);
  header.set_binary(CGAL::is_binary( out));
  header.set_no_comments(!CGAL::is_pretty( out));
  CGAL::File_writer_OFF writer( header);
  writer.header().set_polyhedral_surface(true);
  writer.header().set_halfedges( alcc.number_of_darts());
  
  std::vector<unsigned int> cells; cells.push_back(2);
  std::vector<unsigned int> res = alcc.count_cells(cells);

      // Print header.
  writer.write_header( out,
                       alcc.number_of_vertex_attributes(),
                       alcc.number_of_darts(),
                       res[2]);

  typedef typename LCC::Vertex_attribute_range::iterator VCI;
  VCI vit, vend = alcc.vertex_attributes().end();
  for ( vit = alcc.vertex_attributes().begin(); vit!=vend; ++vit )
  {
    writer.write_vertex( ::CGAL::to_double( vit->point().x()),
                         ::CGAL::to_double( vit->point().y()),
                         ::CGAL::to_double( vit->point().z()));
  }

  typedef CGAL::Inverse_index< VCI> Index;
  Index index( alcc.vertex_attributes().begin(),
               alcc.vertex_attributes().end());
  writer.write_facet_header();

  int m = alcc.get_new_mark();

  for ( typename LCC::Dart_range::iterator itall = alcc.darts().begin(),
          itallend = alcc.darts().end(); itall!=itallend; ++itall )
  {
    if ( !alcc.is_marked(itall, m) )
    {
      std::size_t n = 0;
      // First we count the number of vertices of the face.
      for ( typename LCC::template Dart_of_cell_range<2>::iterator
              itf=alcc.template darts_of_cell<2>(itall).begin(),
              itfend=alcc.template darts_of_cell<2>(itall).end();
            itf!=itfend; ++itf, ++n );

      CGAL_assertion( n>=3 );
      writer.write_facet_begin(n);

      // Second we write the indices of vertices.
      for ( typename LCC::template Dart_of_cell_range<2>::iterator
              itf=alcc.template darts_of_cell<2>(itall).begin(),
              itfend=alcc.template darts_of_cell<2>(itall).end();
            itf!=itfend; ++itf )
      {
        writer.write_facet_vertex_index( index[ VCI(alcc.vertex_attribute(itf))]);
        alcc.mark(itf, m);
      }
      writer.write_facet_end();
    }
  }
  writer.write_footer();
  alcc.free_mark(m);
}

/* ==========================================================================
   ========================================================================== */
int main(int narg, char** argv)
{
  if (narg<2 || (!strcmp(argv[1],"-h") || !strcmp(argv[1],"-?")) )
  {
    std::cout<<"Usage : load_off filename"<<std::endl   
             <<"   filename being an '.off' file."<<std::endl;
    return EXIT_FAILURE;
  }
  
  std::ifstream ifs(argv[1]);
  if ( ifs.fail() )
  {
    std::cout<<"Error : impossible to open file "<<argv[1]<<std::endl;
    return EXIT_FAILURE;
  }
  
  LCC_3 lcc;

  CGAL::load_off(lcc, ifs);
  
  lcc.display_characteristics(std::cout) << ", valid=" 
                                         << lcc.is_valid() << std::endl;

  EdgeCollapse* edgeCollapser = new EdgeCollapse( &lcc );
  int collapseRate = 10; // percentage of edges to remove
  edgeCollapser->collapseEdges( collapseRate );

  lcc.display_characteristics(std::cout) << ", valid="
                                         << lcc.is_valid() << std::endl;

  /* If you do not want to use a viewer, you can comment the following file. */
  display_lcc(lcc);

  // Print the corresponding off to stdout
  std::ofstream ofs("output_pig.off");
  if ( ofs.fail() )
  {
    std::cout<<"Error : impossible to open file "<<"output.off"<<std::endl;
    return EXIT_FAILURE;
  }
  write_off(lcc, ofs);
  
  return EXIT_SUCCESS;
}

