
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

void removeEdge( LCC_3* lcc, unsigned int mark )
{
  //std::cout<<edge<<std::endl; // show edge to remove
  // TODO: remove edge #edge
  int nb=0;

  for (LCC_3::Dart_range::iterator it (lcc->darts().begin ());
         lcc->number_of_marked_darts (mark) > 0; ++it)
  {
    ++nb;
    if (lcc->is_marked (it, mark))
    {
      lcc->unmark(it, mark);
      // Add Barycenter
      lcc->insert_barycenter_in_cell<1>(it);
    }
  }
  CGAL_assertion (lcc->is_whole_map_unmarked (mark));
  CGAL_assertion (lcc->is_valid ());
  lcc->free_mark (mark);

}

void EdgeCollapse::collapseEdges(int collapseRate)
{
  std::vector<int> edgesToRemove = m_edgeSelector->selectEdgesRandom(collapseRate);

  unsigned int treated = m_lcc->get_new_mark ();

  for( int i=0; i<edgesToRemove.size(); i++ )
  {
      int nb=0;
      for(LCC_3::Dart_range::iterator it=m_lcc->darts().begin(),itend=m_lcc->darts().end();it!=itend;++it)
      {
          if(nb==edgesToRemove[i])
          {
              m_lcc->mark(it, treated);
          }
          nb++;
      }
  }

  removeEdge(m_lcc, treated);
} 
