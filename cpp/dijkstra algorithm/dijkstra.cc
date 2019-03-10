#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <climits>
#include <type_traits>

#include "algorithm.cc"

int main()
{

  Graph graph1("random");
  // uint v1, v2, v3;
  // for(uint i=0; i<100; i++) {
  //      v1 = rand() % 11;
  //      v2 = rand() % 11;
  //      v3 = rand() % 101;
  //      graph1.addConnection( new Connection(v1,v2,v3) );
  // }
  uint con, v, r;
  std::cout << "Enter connections number: ";
  std::cin >> con;
  std::cout << "Enter vertex number: ";
  std::cin>> v;
  std::cout << "Enter range of cost: ";
  std::cin >> r;

  graph1.getRandom(con, v, r);
  graph1.printConnections();
  DijkstraAlgorithm algorithm(graph1);
  algorithm.configureStart().run().showCostArray();

  algorithm.configureEnd().showShortestPath().showCost();

  // Graph graph1("grap1");
  // graph1.addConnection( new Connection(0,1,3))
  //       .addConnection( new Connection(0,4,3))
  //       //.addConnection( Connection(1,0,3))
  //       .addConnection( new Connection(1,2,1))
  //       //.addConnection( Connection(2,1,1))
  //       //.addConnection( Connection(2,4,3))
  //       //.addConnection( Connection(3,2,3))
  //       //.addConnection( Connection(3,5,1))
  //       //.addConnection( Connection(4,0,3))
  //       //.addConnection( Connection(5,2,1))
  //       .addConnection( new Connection(4,5,2))
  //       .addConnection( new Connection(5,3,1))
  //       //.addConnection( Connection(5,4,2))//;
  //       .addConnection( new Connection(5,0,6))
  //       .addConnection( new Connection(3,1,3))
  //       .addConnection( new Connection(2,5,1))
  //       .addConnection( new Connection(2,3,1))
  //       .addConnection( new Connection(1,2,1));

  // graph1.printConnections();
  // DijkstraAlgorithm algorithm(graph1);
  // algorithm.configureStart().configureEnd().run().showShortestPath().showCost();
}
