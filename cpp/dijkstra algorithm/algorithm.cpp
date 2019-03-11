#include "algorithm.hpp"

typedef unsigned uint;

#define DEBUG_LOG 0

// #if DEBUG_LOG
// LogBuilder lb("debug", " ", true);
// LogBuilder li("debug", " ", true);
// #else
LogBuilder lb("lb ", " ", false);
LogBuilder li("li ", " ", false);
// #endif

Connection::Connection(uint _vertex1, uint _vertex2, uint _cost) :
  vertex1(_vertex1),
  vertex2(_vertex2),
  cost(_cost)
  {
    lb.add("new connection c-tor (")
      .add(vertex1)
      .add(",")
      .add(vertex2)
      .add(") cost")
      .add(cost)
      .print();
  }

  uint Connection::getVertex1() {
    return this->vertex1;
  }
  uint Connection::getVertex2() {
    return this->vertex2;
  }
  uint Connection::getCost() {
    return this->cost;
  }

  Graph::Graph( std::string _name) :
    name(_name)
    {
      lb.add("Grap c-tor").print();
    }

  Graph& Graph::addConnection( Connection* c ) {
    newVertexCheck( c->getVertex1() );
    newVertexCheck( c->getVertex2() );
    if( !hasConnection(c) ) {
      graph_connections.push_back( c );
      lb.add("adding connection to graph")
        .add(name)
        .print();
    }
    return *this;
  }

  Graph& Graph::getRandom(uint connections, uint vertex_number, uint max_cost) {
    uint v1, v2, v3;
    for(uint i=0; i<connections; i++) {
         v1 = rand() % vertex_number+1;
         v2 = rand() % vertex_number+1;
         v3 = rand() % max_cost+1;
         if( v1 == v2 ) {
           i--;
           continue;
         }
         addConnection( new Connection(v1,v2,v3) );
    }
    return *this;
  }

  void Graph::printConnections() {
    LogBuilder connectionInfo("added connection", " ");
    for( auto connection: graph_connections) {
      connectionInfo.add(connection->getVertex1())
        .add("->")
        .add(connection->getVertex2())
        .add("cost = ")
        .add(connection->getCost())
        .print();
    }
  }

  bool Graph::hasConnection ( Connection* other) {
    for( auto connection: graph_connections) {
      if( connection->getVertex1() == other->getVertex1() &&
          connection->getVertex2() == other->getVertex2() )
          return true;
    }
    return false;
  }

  uint Graph::getVertexNumber() {
    return vertexList.size();
  }

  bool Graph::newVertexCheck( uint vertex) {
    for ( auto connection: graph_connections ) {
      if ( vertex == connection->getVertex1() || vertex == connection->getVertex2() ) {
        lb.add("new vertex NOT added").add(vertex).print();
        return false;
      }
    }
    vertexList.push_back(vertex);
    lb.add("new vertex added").add(vertex).print();
    return true;
  }

  std::vector<uint> Graph::getVertexList() {
    return vertexList;
  }

  std::list<Connection*> Graph::getGraphConnections() {
    return graph_connections;
  }

  Connection* Graph::getConnection( uint vertex1, uint vertex2 ) {
    for( auto el : graph_connections ) {
      if( el->getVertex1() == vertex1 && el->getVertex2() == vertex2 )
        return el;
    }
  }

  bool Graph::hasConnection( uint vertex1, uint vertex2 ) {
    for( auto &el : graph_connections ) {
      if( el->getVertex1() == vertex1 && el->getVertex2() == vertex2 )
        return true;
    }
    return false;
  }

  int DijkstraAlgorithm::findMIN(std::list<uint> Q, std::map<uint,int> d) {

      int min_vec = *Q.begin();
      int min_cost = MAX;
      lb.add("Q contains: ");
      for( auto vector: Q) {

          lb.add( vector ).add("|");
          li.add( "d.at(").add(vector).add(")=").add(d.at(vector)).add("min_cost=").add(min_cost).print();
          if( d.at(vector) <= min_cost ) {
              min_vec = vector;
              min_cost = d.at(vector);
          }
      }
      if(min_vec == -1)
        lb.add("min cost not found").print();
      else
      lb.add("found min cost").add(min_cost).add("at").add(min_vec).print();
      lb.add("min_vec=").add(min_vec).print();
      return min_vec;
  }

  bool DijkstraAlgorithm::contains(std::list<uint> Q, int vector) {
      for( auto el: Q) {
          if( el == vector ) {
              lb.add("Q contains").add(vector).print();
              return true;
          }
      }
      return false;
  }

  bool DijkstraAlgorithm::contains(std::vector<uint> Q, int vector) {
      for( auto el: Q) {
          if( el == vector ) {
              lb.add("Q contains").add(vector).print();
              return true;
          }
      }
      return false;
  }

  DijkstraAlgorithm::DijkstraAlgorithm(Graph g) :
    graph(g)
  {
    vertexList = graph.getVertexList();
    for( auto vertex: vertexList ) {
      Q.push_back(vertex);
      d[vertex] = MAX;
      p[vertex] = -1;
    }
    if(vertexList.size())
      startVertex = vertexList.at(0);
    connections = graph.getGraphConnections();
  }

  DijkstraAlgorithm& DijkstraAlgorithm::configureStart() {

    LogBuilder addStartVertex( "Enter existing starting vertex" , " ");
    do {
      addStartVertex.print();
      std::cin >> startVertex;
    } while( !contains(Q, startVertex) );

    return *this;
  }

  DijkstraAlgorithm& DijkstraAlgorithm::configureEnd() {

    LogBuilder addEndVertex( "Enter existing ending vertex" , " ");
    do {
      addEndVertex.print();
      std::cin >> endVertex;
    } while( !contains(vertexList, endVertex) );

    return *this;
  }

  DijkstraAlgorithm& DijkstraAlgorithm::run() {
    lb.add("...run...").print();
    LogBuilder aLog("Algortihm", " ");
    aLog.add("started").print();

    double perc = 0;
    uint all = Q.size()*vertexList.size();
    std::cout<< "all combinations = " << all << std::endl;
    d.at(startVertex) = 0;
    while( Q.size() ) {

        perc = 100 * (double)vertexList.size() * (double)S.size() / (double) all;
        std::cout << "completed in: " << perc << "%" << std::endl;
        uint minVertexIndex = findMIN( Q, d);
        S.push_back(minVertexIndex);
        Q.remove(minVertexIndex);

        for( auto vertex : vertexList) {

            if( contains( Q, vertex ) && graph.hasConnection( minVertexIndex, vertex ) ) {
              Connection* con = graph.getConnection( minVertexIndex, vertex );
                int cost =  d.at(minVertexIndex) + con->getCost();
                if( d.at(vertex) > cost ) {
                    lb.add("d > cost |").add(d.at(vertex)).add(">").add(cost).print();
                    d.at(vertex) = cost;
                    p.at(vertex)  = minVertexIndex;
                }
            }
        }
    }
    return *this;
  }

  std::vector<uint> DijkstraAlgorithm::calculateShortestPath() {
    std::vector<uint> path{endVertex};
      if( d.at(endVertex) != MAX ) {
      uint vertex = endVertex;
      while(vertex != startVertex ) {
          vertex = p.at(vertex);
          path.push_back(vertex);
      }
    }
    return path;
  }

  DijkstraAlgorithm& DijkstraAlgorithm::showShortestPath() {
    LogBuilder shortestPathInfo("Shortest path", " ");
    shortestPathInfo.add("from").add(startVertex).add("to").add(endVertex);

    if( d.at(endVertex) == MAX )
      shortestPathInfo.add("does not exist").print();
    else {
      std::vector<uint> path = calculateShortestPath();
      shortestPathInfo.add("vertex1 -(cost)-> vertex2\n");
      for(auto it= path.rbegin(); it!=path.rend()-1; it++) {
        Connection* con = graph.getConnection( *(it), *(it+1) );
        shortestPathInfo.add(*it).add("-(").add(con->getCost()).add(")->");
        //std::cout << *it << " -("<< con->getCost() << ")-> ";
      }
      shortestPathInfo.add( *(path.rend()-1) ).print();
    //  std::cout << *(path.rend()-1) << std::endl;
    }
    return *this;
  }

  DijkstraAlgorithm& DijkstraAlgorithm::showCost() {
    LogBuilder costInfo("Total cost:", " ");
    costInfo.add( d.at(endVertex) ).print();
    //std::cout << "Total cost: " << d.at(endVertex) << std::endl;
    return *this;
  }

  DijkstraAlgorithm& DijkstraAlgorithm::showCostArray() {
    LogBuilder costArr("Cost array:");
    costArr.add("\nvertex | cost\n");
    for(auto it=d.begin(); it!=d.end(); it++) {
      costArr.add(it->first).add("|").add(it->second).add("\n");
      //std::cout  << it->first << " : " << it->second << " | ";
    }
    costArr.print();
    //std::cout << std::endl;
    return *this;
  }
