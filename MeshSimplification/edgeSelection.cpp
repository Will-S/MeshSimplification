
#include "time.h" // for srand(time(NULL));
#include <sstream>

#include <CGAL/Combinatorial_map.h>
#include <CGAL/Linear_cell_complex.h>

#include "edgeSelection.hpp"

EdgeSelection::EdgeSelection( LCC_3* lcc )
{
  m_lcc = lcc;
}

EdgeSelection::~EdgeSelection()
{}

int getNbEdges( LCC_3* lcc )
{
  std::ostringstream oss;
  lcc->display_characteristics(oss);
  std::string charac = oss.str();

  std::string edgestring;
  int i=0;
  while( charac.c_str()[i+9] != '\0' )
  {
    std::string subString = charac.substr(i, 9);
    if( subString == "#1-cells=" )
    {
      int j=0;
      while( charac.c_str()[i+9+j] != ',' )
      {
        j++;
      }
      edgestring = charac.substr(i+9, j);
      break;
    }
    i++;
  }

  return atoi(edgestring.c_str());
}

int getNbEdgesRemoved( LCC_3* lcc, int collapseRate )
{
  int nbEdgesRemoved = (int)getNbEdges(lcc)*(double)collapseRate/(double)100;
  return nbEdgesRemoved;
}

std::vector<int> EdgeSelection::selectEdgesRandom(int collapseRate)
{
  int nbEdgesRemoved = getNbEdgesRemoved(m_lcc, collapseRate);
  std::cout<< nbEdgesRemoved <<" edges will be removed randomly"<<std::endl;

  srand(time(NULL)); // initialize random nb generator with absolute time

  int nbEdges = getNbEdges(m_lcc);
  std::vector<int> edgesToRemove;
  edgesToRemove.resize(nbEdgesRemoved);
  for( int i=0; i<nbEdgesRemoved; i++ )
  {
    int edge = (int)nbEdges*float(rand())/RAND_MAX;
    // check if not already chosen:
    while( std::find(edgesToRemove.begin(), edgesToRemove.end(), edge) != edgesToRemove.end() )
    {
      edge = (int)nbEdges*float(rand())/RAND_MAX;
    }
    edgesToRemove[i] = edge;
  }
  return edgesToRemove;
}

std::vector<int> EdgeSelection::selectEdgesMetric(int collapseRate)
{
  int nbEdgesRemoved = getNbEdgesRemoved(m_lcc, collapseRate);
  std::cout<< nbEdgesRemoved <<" edges will be removed using a metric"<<std::endl;

  std::vector<int> edgesToRemove;
  edgesToRemove.resize(nbEdgesRemoved);
  return edgesToRemove;
}
