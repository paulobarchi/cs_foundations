#ifndef __CAP241_MWTREE_HPP__
#define __CAP241_MWTREE_HPP__

//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercício 01           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 05/05/2017                            //
//==================================================//

#include <iostream>
#include <vector>
#include <algorithm> 	// find
#include <memory>  		// unique_ptr

// Estrutura de dados do tipo árvore (multivias)
// mwtree (multiway tree)
template <class T>
class mwtree
{
public:
	mwtree() : parent(nullptr) { }
	mwtree(const T& v) : data(v), parent(nullptr) { }
	~mwtree();

	bool has_parent() const;
	mwtree*	get_parent() const;
	bool has_children() const;
	size_t get_children_count() const;
	size_t get_descendants_count() const;
	mwtree*	get_child(size_t i) const;
	void push_back(mwtree *child);
	void insert(std::size_t	i, mwtree *child);
	// std::unique_ptr<mwtree> erase(size_t i);
	bool is_sibling(const mwtree* item) const;
	bool operator == (const mwtree<T> &t2) const;
	void disconnect();

	T data;

private:
	mwtree* parent;
	std::vector<mwtree*> children;
      
	// Tornando estes dois operadores privados, sem fornecer 
	// implementação, fará com que os objetos mwtree não possam ser copiáveis
	mwtree(const mwtree&);
	mwtree& operator=(const mwtree&);
};

template<class T>
mwtree<T>::~mwtree()
{
	disconnect();
}

template<class T>
bool mwtree<T>::has_parent() const
{
	if (this == nullptr || this->parent == nullptr)
		return false;	
	return true;
}

template<class T>
mwtree<T>*
mwtree<T>::get_parent() const
{
	if (this == nullptr || !this->has_parent())
		return nullptr;	
	return this->parent;
}

template<class T>
bool mwtree<T>::has_children() const
{
	if (this == nullptr)
		return false;
	return this->children.empty() ? false : true;
}

template<class T>
size_t mwtree<T>::get_children_count() const
{
	if (this == nullptr || !this->has_children())
		return 0;
	return this->children.size();
}

template<class T>
size_t mwtree<T>::get_descendants_count() const
{
	if (this == nullptr)
		return 0;
	size_t descendants = this->get_children_count();
	// my children + recursive(children's children)
	for (mwtree<T> *c : this->children)
		descendants += c->get_children_count();
	return descendants;
}

template<class T>
mwtree<T>*
mwtree<T>::get_child(size_t	i) const
{
	if (this == nullptr || !this->has_children())
		return nullptr;
	return this->children.at(i);
}

template<class T>
void mwtree<T>::push_back(mwtree<T>	*child)
{
	this->children.push_back(child);
	child->parent = this;
}

template<class T>
void mwtree<T>::insert(std::size_t i, mwtree<T> *child)
{
	this->children.insert(this->children.begin() + i, child);
	child->parent = this;
}

// template<class T>
// std::unique_ptr<mwtree<T>> 
// mwtree<T>::erase(size_t i)
// {
// 	std::unique_ptr<mwtree> aux(this->get_child(i));
// 	aux->parent = nullptr;
// 	auto it = std::find(this->children.begin(), this->children.end(), this->get_child(i));
// 	if (it != this->children.end())
// 	{
// 		aux->parent = nullptr;
// 		it = this->children.erase(it);
// 	}
// 	return aux;
// }

template<class T>
bool mwtree<T>::is_sibling(const mwtree<T>* item) const
{
	if (this->has_parent() && item->has_parent())
		return this->parent->data == item->parent->data;
	return false;
}

template<class T>
bool mwtree<T>::operator == (const mwtree<T> &t2) const
{
	// false if null trees
	if ( this == nullptr || t2 == nullptr || 
		// if do not have parents and data is diff
		(!this->has_parent() && !t2->has_parent() && this->data != t2->data) ||
		// or if one has parent the other does not
		(this->has_parent() && !t2->has_parent()) ||
		(!this->has_parent() && t2->has_parent()) ||
		// or if they have diff parents
		(this->has_parent() && t2->has_parent() && (this->parent->data != t2->parent->data)) ||
		// or same parents and diff data
		(this->data != t2->data) )
			return false;
	// else, same parents and data
	return true;	
}

template<class T>
void mwtree<T>::disconnect()
{
  	// disconnect from parent
  	this->parent->children.erase(
  		std::remove(this->parent->children.begin(), this->parent->children.end(), this), 
  			this->parent->children.end());
  	this->parent = nullptr;
  	delete this;
}

#endif // __CAP241_MWTREE_HPP__ 