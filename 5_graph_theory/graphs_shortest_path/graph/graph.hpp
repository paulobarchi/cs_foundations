#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <iterator>

template <class T> struct classComp;
template <class T> struct classComp;

//****************************************************************************//

template <class T> struct classComp
{
    bool operator() (const std::pair<T, double>& p1, const std::pair<T, double>& p2) const  
    {
      return p1.first < p2.first;
    }
};

//****************************************************************************//

template<class T> class graph
{
  public:
    graph();
    graph(bool kind);
    void addVertex(const T& v);
    void addEdge(const T& v, const T& u);
    void addEdge(const T& v, const T& u, const double& weight);

    void removeVertex(const T& v);
    void removeEdge(const T& v, const T& u);

    bool searchByEdge(const T& v, const T&u);

    // ainda não descobri como remover funções friend usando template de 
    // dentro da classe, descobri que precisa usar forward declaration
    // mas não entedi os exemplos
    friend std::ostream& operator<<(std::ostream& output, const graph<T>& aux)
    {
      output << "   Graph    " << std::endl;

      auto it = aux.graphContainer_.begin();
      auto end = aux.graphContainer_.end();

      while(it != end)
      {
	output << it->first << " => ";
	auto itSet = it->second->begin();
	auto endSet = it->second->end();

	while(itSet != endSet)
	{
	  output << "(" << itSet->first << ", " << itSet->second << ")";
	  output << " ";

	  ++itSet;
	}

	output << std::endl;
	++it;
      }

      return output;
    }

  private:
    // if type_ = false, você tem um grafo direcionado
    // if type_ = true, você tem um grafo não direcionado
    bool type_; 
    std::map< T, std::set< std::pair<T,double>, classComp<T> >* > graphContainer_;
};

//****************************************************************************//

template<class T> graph<T>::graph():type_(false){}

template<class T> graph<T>::graph(bool kind):type_(kind){}

template<class T> void graph<T>::addVertex(const T& v)
{
  std::set< std::pair<T, double>, classComp<T> >* newPair = new std::set< std::pair<T, double>, classComp<T> >;
  graphContainer_[v] = newPair;
}

template<class T> void graph<T>::addEdge(const T& v, const T& u)
{
  addEdge(v, u, 1);
}

template<class T> void graph<T>::addEdge(const T& v, const T&u, const double& weight)
{
  graphContainer_[v]->insert(std::make_pair(u, weight));

  // cuida da inserção em um grafo não direcionado do par (u, v)
  if(type_)
  {
    graphContainer_[u]->insert(std::make_pair(v, weight));
  }
}

template<class T> void graph<T>::removeVertex(const T& v)
{
  // remove o vertice v
  graphContainer_.erase(v);

  // busca o vertice v na lista de arestas e remove
  auto it = graphContainer_.begin();
  auto end = graphContainer_.end();
  while( it != end )
  {
   // uma vez que a buscar é feita somente no primeiro parametro do vértice
   // tanto faz o peso do vertice
   auto itRemove = it->second->find(std::make_pair(v, 1));
   
   if(itRemove != it->second->end())
     it->second->erase(itRemove);
   
   ++it;
  }
}

template<class T> void graph<T>::removeEdge(const T& v, const T& u)
{
  auto itRemove = graphContainer_[v]->find(std::make_pair(u, 1));
  graphContainer_[v]->erase(itRemove);

  if(type_)
  {
    auto itRemove = graphContainer_[u]->find(std::make_pair(v, 1));
    graphContainer_[u]->erase(itRemove);
  }
}

template<class T> bool graph<T>::searchByEdge(const T& v, const T&u)
{
  bool ret;
  
  auto it = graphContainer_.find(v);
  if(it == graphContainer_.end())
    ret = false;
  else
  {
    auto itSet = it->second->find(std::make_pair(u, 1));
    if(itSet == it->second->end())
      ret = false;
    else 
      ret = true;
  }

  if(type_)
  {
    auto it = graphContainer_.find(u);
    if(it == graphContainer_.end())
      ret = false;
    else
    {
      auto itSet = it->second->find(std::make_pair(v, 1));
      if(itSet == it->second->end())
	ret = false;
      else
	ret = true;
    }
  }

  return ret;
}
#endif // _GRAPH_HPP_
