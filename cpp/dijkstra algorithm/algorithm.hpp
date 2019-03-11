#include <list>
#include <string>
#include <vector>
#include <map>

#include "logbuilder.hpp"

typedef unsigned uint;

class Connection {

private:
  uint vertex1;
  uint vertex2;
  uint cost;
  LogBuilder lb;

public:
  Connection();
  Connection(uint _vertex1, uint _vertex2, uint _cost);

  uint getVertex1();
  uint getVertex2();
  uint getCost();

};

class Graph {

private:
  std::list<Connection*> graph_connections;
  std::string name;
  std::vector<uint> vertexList;

public:

  Graph( std::string _name);

  Graph& addConnection( Connection* c );

  Graph& getRandom(uint connections, uint vertex_number, uint max_cost);

  void printConnections();

  bool hasConnection (Connection* other);

  uint getVertexNumber();

  bool newVertexCheck( uint vertex);

  std::vector<uint> getVertexList();

  std::list<Connection*> getGraphConnections();

  Connection* getConnection( uint vertex1, uint vertex2 );

  bool hasConnection( uint vertex1, uint vertex2 );

};

class DijkstraAlgorithm{

private:
  Graph graph;
  std::list<uint> Q;
  std::list<uint> S;
  std::vector<uint> vertexList;
  std::list<Connection*> connections;
  std::map<uint, int> d;
  std::map<uint, int> p;
  uint startVertex;
  uint endVertex;
  LogBuilder lb;
  LogBuilder li;

  int findMIN(std::list<uint> Q, std::map<uint,int> d);

  bool contains(std::list<uint> Q, int vector);

  bool contains(std::vector<uint> Q, int vector);

public:
  DijkstraAlgorithm(Graph g);

  DijkstraAlgorithm& configureStart();

  DijkstraAlgorithm& configureEnd();

  DijkstraAlgorithm& run();

  std::vector<uint> calculateShortestPath();

  DijkstraAlgorithm& showShortestPath();

  DijkstraAlgorithm& showCost();

  DijkstraAlgorithm& showCostArray();

};
