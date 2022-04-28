#include "graph.hpp"

int main()
{
  graph<std::string> test;
 
  test.addVertex("a");
  test.addVertex("b");
  test.addVertex("c");
  test.addVertex("d");
  test.addVertex("e");
  test.addVertex("f");
  test.addEdge("a", "e", 22); 
  test.addEdge("c", "d", 12); 
  test.addEdge("a", "b", 42); 

  std::cout << test << std::endl;
  std::cout << "There is a edge between a and e: " 
    << ( test.searchByEdge("a", "e") ? "True" : "False") << std::endl;

  std::cout << std::endl;

  test.removeVertex("d");
  test.removeEdge("a", "e");
  test.removeVertex("f");

  std::cout << test << std::endl;


  return 0;
}
