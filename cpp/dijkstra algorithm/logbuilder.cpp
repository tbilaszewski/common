#include "logbuilder.hpp"

LogBuilder::LogBuilder(std::string _msg, std::string _del, bool _verbose) :
  delimitter(_del),
  message(_msg),
  verbose(_verbose)
{}

LogBuilder::LogBuilder(std::initializer_list<std::string> _list, std::string _msg, std::string _del, bool _verbose) :
  delimitter(_del),
  message(_msg),
  list(_list),
  verbose(_verbose)
{}

LogBuilder& LogBuilder::add( std::string msg ) {
  list.push_back( msg );
  return *this;
}
LogBuilder& LogBuilder::add( const char* msg ) {
  list.push_back( std::string(msg) );
  return *this;
}

void LogBuilder::print() {
  list.push_front(message);

  auto it = list.begin();
  auto last = --list.end();

  if(verbose) {
    for( ; it!=last; it++ ) {
      std::cout << *it << delimitter;
    }
    std::cout << *last << std::endl;
  }
  list.clear();
}
