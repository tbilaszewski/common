#include <list>
#include <string>
#include <climits>
#include <type_traits>
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

#define MAX INT_MAX
//#define MAX 9999999

class LogBuilder {

private:
  std::list<std::string> list;
  std::string delimitter;
  std::string message;
  bool verbose;

public:

  LogBuilder(std::string _msg = "debug", std::string _del = "", bool _verbose = true);

  LogBuilder(std::initializer_list<std::string> _list, std::string _msg = "debug", std::string _del = " ", bool _verbose = true);

  template<typename T>
  LogBuilder& add( T msg ) {
    if( msg >= MAX )
      list.push_back("MAX");
    else
      list.push_back( std::to_string(msg) );
    return *this;
  }

  LogBuilder& add( std::string msg );
  LogBuilder& add( const char* msg );

  void print();
};
