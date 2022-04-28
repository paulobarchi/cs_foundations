#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <cstdint>
#include <map>
#include <set>
#include <queue>
#include <utility>
#include <iterator>

const int INFINITE = 10000000;

template <class T> 
struct classComp
{
	bool operator() (const std::pair<T, double>& p1, const std::pair<T, double>& p2) const  
	{
		return p1.first < p2.first;
	}
};

template<class T> 
class graph
{
public:
	graph();
	graph(size_t);
	void addVertex(const T&);
	void addEdge(const T&, const T&);
	void addEdge(const T&, const T&, const double&);
	void removeVertex(const T&);
	void removeEdge(const T&, const T&);
	bool searchByEdge(const T&, const T&);
	double dist(const T&, const T&);
	std::deque<T> path(const T&, const T&);

	double distNeg(const T&, const T&);
	std::deque<T> pathNeg(const T&, const T&);
	std::pair<double, std::deque<T>> bellmanFord(const T&, const T&);

	friend std::ostream& operator<<(std::ostream& output, const graph<T>& aux)
	{
		output << "   Graph    " << std::endl;

		auto it = aux.graphContainer_.begin();
		auto end = aux.graphContainer_.end();

		while (it != end) {
			output << it->first << " => ";
			auto itSet = it->second->begin();
			auto endSet = it->second->end();

			while (itSet != endSet) {
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
	std::map<T, std::set<std::pair<T, double>, classComp<T>>*> graphContainer_;
};

template<class T> 
graph<T>::graph()
{
}

template<class T> 
graph<T>::graph(size_t V_)
{
}

template<class T> 
void graph<T>::addVertex(const T& v)
{
	std::set<std::pair<T, double>, classComp<T>> *newPair = new std::set<std::pair<T, double>, classComp<T>>;
	graphContainer_[v] = newPair;
}

template<class T> 
void graph<T>::addEdge(const T& v, const T& u)
{
	addEdge(v, u, 1);
}

template<class T> 
void graph<T>::addEdge(const T& v, const T&u, const double& weight)
{
	graphContainer_[v]->insert(std::make_pair(u, weight));
}

template<class T> 
void graph<T>::removeVertex(const T& v)
{
	graphContainer_.erase(v);

	auto it = graphContainer_.begin();
	auto end = graphContainer_.end();

	while (it != end) {
		auto itRemove = it->second->find(std::make_pair(v, 1));

		if (itRemove != it->second->end()) {
			it->second->erase(itRemove);
		}

		++it;
	}
}

template<class T> 
void graph<T>::removeEdge(const T& v, const T& u)
{
	auto itRemove = graphContainer_[v]->find(std::make_pair(u, 1));
	graphContainer_[v]->erase(itRemove);
}

template<class T> 
bool graph<T>::searchByEdge(const T& v, const T&u)
{
	bool ret;

	auto it = graphContainer_.find(v);

	if (it == graphContainer_.end()) {
		ret = false;
	} else {
		auto itSet = it->second->find(std::make_pair(u, 1));
		if (itSet == it->second->end()) {
			ret = false;
		} else {
			ret = true;
		}
	}

	return ret;
}

template <class T>
double graph<T>::dist(const T& orig, const T& dest)
{
	std::map<T, double> dist_;
	std::map<T, bool> visited_;

	std::priority_queue<std::pair<double, T>, std::vector<std::pair<double, T>>, std::greater<std::pair<double, T>>> pq;

	if (graphContainer_.find(orig) == graphContainer_.end() || 
		graphContainer_.find(dest) == graphContainer_.end()) {
		throw std::logic_error("The vertexs don't belong to the graph");
	}

	for (auto it = graphContainer_.begin(); it != graphContainer_.end(); ++it) {
		dist_[it->first] = INFINITE;
		visited_[it->first] = false;
	}

	dist_[orig] = 0.0;
	pq.push(std::make_pair(dist_[orig], orig));

	while (!pq.empty()) {
		auto p = pq.top();
		T v = p.second;
		pq.pop();

		if (!visited_[v]) {
			visited_[v] = true;

			auto it_vertex = graphContainer_.find(v);
			auto it_edge = it_vertex->second->begin();
			auto it_edge_end = it_vertex->second->end();

			for (; it_edge != it_edge_end; ++it_edge) {
				T u = it_edge->first;
				double weight = it_edge->second;

				if (dist_[u] > (dist_[v] + weight)) {
					dist_[u] = dist_[v] + weight;
					pq.push(std::make_pair(dist_[u], u));
				}
			}
		}
	}

	return dist_[dest];
}

template <class T>
std::deque<T> graph<T>::path(const T& orig, const T& dest)
{
	std::deque<T> ret;

	std::map<T, double> dist_;
	std::map<T, bool> visited_;
	std::map<T, T> path_;

	std::priority_queue<std::pair<double, T>, std::vector<std::pair<double, T>>, std::greater<std::pair<double, T>>> pq;

	if (graphContainer_.find(orig) == graphContainer_.end() || 
		graphContainer_.find(dest) == graphContainer_.end()) {
		throw std::logic_error("The vertexs don't belong to the graph");
	}

	for (auto it = graphContainer_.begin(); it != graphContainer_.end(); ++it) {
		dist_[it->first] = INFINITE;
		visited_[it->first] = false;
	}

	dist_[orig] = 0.0;
	pq.push(std::make_pair(dist_[orig], orig));

	while (!pq.empty()) {
		auto p = pq.top();
		T v = p.second;
		pq.pop();

		if (!visited_[v]) {
			visited_[v] = true;

			auto it_vertex = graphContainer_.find(v);
			auto it_edge = it_vertex->second->begin();
			auto it_edge_end = it_vertex->second->end();

			for (; it_edge != it_edge_end; ++it_edge) {
				T u = it_edge->first;
				double weight = it_edge->second;

				if (dist_[u] > (dist_[v] + weight)) {
					dist_[u] = dist_[v] + weight;
					pq.push(std::make_pair(dist_[u], u));
					path_[u] = v;
				}
			}
		}
	}

	for (T tmp = dest; tmp != orig; tmp = path_[tmp]) {
		ret.push_front(tmp);
	}
	ret.push_front(orig);

	return ret;
}

template <class T>
double graph<T>::distNeg(const T& orig, const T& dest)
{
	return bellmanFord(orig, dest).first;
}

template <class T>
std::deque<T> graph<T>::pathNeg(const T& orig, const T& dest)
{
	return bellmanFord(orig, dest).second;
}

template <class T> 
std::pair<double, std::deque<T>> graph<T>::bellmanFord(const T& orig, const T& dest)
{
	std::deque<T> path_;
	std::map<T, double> dist_;
	std::map<T, T> predecessor_;

	if(graphContainer_.find(orig) == graphContainer_.end() || 
			graphContainer_.find(dest) == graphContainer_.end())
		throw std::logic_error("The vertexs don't belong to the graph");

	auto it = graphContainer_.begin();
	auto end = graphContainer_.end();

	// passo 1 inicialização do grafo
	while(it != end)
	{
		dist_[it->first] = INFINITE;
		++it;
	}

	dist_[orig] = 0.0;

	// passo 2 relaxamento dos vertex
	for(std::size_t i = 0; i < graphContainer_.size(); ++i)
	{
		auto itVertex = graphContainer_.begin();
		auto endVertex = graphContainer_.end();

		while(itVertex != endVertex)
		{
			auto itEdge = itVertex->second->begin();
			auto endEdge = itVertex->second->end();

			T v = itVertex->first;

			while(itEdge != endEdge)
			{
				T u = itEdge->first;
				double weight = itEdge->second;

				if(dist_[v] + weight < dist_[u])
				{
					dist_[u] = dist_[v] + weight;
					predecessor_ [u] = v; 
				}

				++itEdge;
			}
			++itVertex;
		}
	}

	// passo 3 checagem por ciclos negativos
	auto itVertex = graphContainer_.begin();
	auto endVertex = graphContainer_.end();

	while(itVertex != endVertex)
	{
		auto itEdge = itVertex->second->begin();
		auto endEdge = itVertex->second->end();

		T v = itVertex->first;

		while(itEdge != endEdge)
		{
			T u = itEdge->first;
			double weight = itEdge->second;

			if(dist_[v] + weight < dist_[u])
				throw std::logic_error("Warning negative-weight cycle");

			++itEdge;
		}

		++itVertex;
	}

	for(T tmp = dest; tmp != orig; tmp = predecessor_[tmp])
		path_.push_front(tmp);

	path_.push_front(orig);

	return std::make_pair(dist_[dest], path_);
}

#endif
