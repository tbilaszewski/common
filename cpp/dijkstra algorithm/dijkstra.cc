/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>


#define MAX 99999

int findMIN(std::list<int> Q, std::vector<int> d) {
    int min_vec;
    int min_cost = MAX;

    for( auto index: Q) {
        if( d.at(index) < min_cost ) {
            min_vec = index;
            min_cost = d.at(index);
        }
    }

    std::cout << "found min cost " << min_cost << " at " << min_vec << std::endl;
    return min_vec;
}

bool contains(std::list<int> Q, int index) {

    for( auto el: Q) {
        if( el == index ) {
            std ::cout << "Q contains " << index << std::endl;
            return true;

        }
    }

    return false;
}

bool hasConnection(std::vector<std::vector<int>> vec, int index1, int index2) {

    if( vec[index1][index2] != -1) {
        std ::cout << "connection between  " << index1 << " and " << index2 << std::endl;
        return true;
    }
    else
        return false;

}

std::vector<int> findPath(std::vector<int> p, int destination) {

    std::vector<int> path{destination};
    int vertex=destination;
    while( vertex != 0 ) {
        vertex = p.at(vertex);
        path.push_back(vertex);
    }

    return path;
}


int main()
{
    std::vector<std::vector<int>> vec{
        {0, 3, -1, -1, 3,-1  },
        {3, 0, 1, -1, -1, -1 },
        {-1, 1, 0, 3, -1, 1  },
        {-1, -1, 3, 0, -1, 1},
        {3, -1, -1, -1, 0, 2 },
        {-1, -1, 1, 1, 2, 0  }
    };

    std::list<int> Q{ 0, 1, 2, 3, 4, 5};
    std::list<int> S{};

    std::vector<int> d { 0, MAX, MAX, MAX, MAX, MAX};
    std::vector<int> p { -1, -1, -1, -1, -1, -1 };

    while( Q.size() ) {

        int minVertexIndex = findMIN( Q, d);
        S.push_back(minVertexIndex);
        Q.remove(minVertexIndex);

        for( int i=0; i<6; i++) {
            if( contains( Q, i) && hasConnection(vec, minVertexIndex, i)) {
                int cost =  d[minVertexIndex] + vec[minVertexIndex][i];
                if( d[i] > cost ) {
                    std::cout << "d[i] > cost | " << d[i] << ">" << cost<< std::endl;
                    d[i] = cost;
                    p[i] = minVertexIndex;

                }


            }
        }
        std:: cout <<"d ";
        for ( auto el: d) {
        std:: cout << el << " ";
        }
        std::cout << std::endl;
        std:: cout <<"p ";
        for ( auto el: p) {
            std:: cout << el << " ";
        }
        std::cout << std::endl;

    }
    int vertex;
    std::cout << "Podaj wierzcholek do ktorego chcesz dojsc: "<< std::endl;
    std::cin >> vertex;

    std::vector<int> path = findPath(p, vertex);

    std::cout << "Shortest path :";
    for( auto el: path) {
        std::cout << el << "->";
    }
    std::cout << std::endl;

    std::cout << "Total Cost: " << d[vertex] << std::endl;

    return 0;
}
