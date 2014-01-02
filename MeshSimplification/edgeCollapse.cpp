
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
      // Add Barycenter
      LCC_3::Dart_handle barycenter_dh = lcc->insert_barycenter_in_cell<1>(it);
      LCC_3::Point barycenter_point = LCC_3::point(barycenter_dh);

      Dart_handle dhA = barycenter_dh->beta(1);

      //Add darts linking barycenter
     for  (LCC_3::Dart_of_cell_range<0>::iterator
                itA(lcc->darts_of_cell<0>(dhA).begin()),
                itAend(lcc->darts_of_cell<0>(dhA).end()); itA!=itAend; ++itA)
     {
         if(LCC_3::point(itA->beta(1))==LCC_3::point(it))
             continue;
         else
         {
             lcc->insert_dangling_cell_1_in_cell_2(barycenter_dh,LCC_3::point(itA->beta(1)));
             /*if(itA->beta(2)!=NULL)
             {
                 CGAL::remove_cell<LCC_3,1>(*lcc,itA->beta(2));
                 CGAL::remove_cell<LCC_3,1>(*lcc,itA);
             }
             else
                 CGAL::remove_cell<LCC_3,1>(*lcc,itA);*/
         }
     }

     for  (LCC_3::Dart_of_cell_range<0>::iterator
                itB(lcc->darts_of_cell<0>(it).begin()),
                itBend(lcc->darts_of_cell<0>(it).end()); itB!=itBend; ++itB)
     {
         if(LCC_3::point(itB->beta(1))==LCC_3::point(dhA))
             continue;
         else
         {
             lcc->insert_dangling_cell_1_in_cell_2(barycenter_dh,LCC_3::point(itB->beta(1)));
             /*if(itB->beta(2)!=NULL)
             {
                 CGAL::remove_cell<LCC_3,1>(*lcc,itB->beta(2));
                 CGAL::remove_cell<LCC_3,1>(*lcc,itB);
             }
             else
                 CGAL::remove_cell<LCC_3,1>(*lcc,itB);*/
         }
     }
      // Unmark dart
      lcc->unmark(it, mark);
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
