//#define MAX INT_MAX
#define MAX 9999999

class LogBuilder {

private:
  std::list<std::string> list{};
  std::string delimitter;
  std::string message;
  bool verbose;
public:

  LogBuilder(std::string _msg = "debug", std::string _del = "", bool _verbose = true ) :
    delimitter(_del),
    message(_msg),
    verbose(_verbose)
  {}

  LogBuilder( std::initializer_list<std::string> _list, std::string _msg = "debug", std::string _del = " ", bool _verbose = true ) :
    delimitter(_del),
    message(_msg),
    list(_list),
    verbose(_verbose)
  {}

  template<typename T>
  LogBuilder& add( T msg ) {
    if( msg >= MAX )
      list.push_back("MAX");
    else
      list.push_back( std::to_string(msg) );
    return *this;
  }

  LogBuilder& add( std::string msg ) {
    list.push_back( msg );
    return *this;
  }
  LogBuilder& add( const char* msg ) {
    list.push_back( std::string(msg) );
    return *this;
  }

  void print() {
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
};
