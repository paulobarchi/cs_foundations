#ifndef __CAP241_BSTREE_HPP__
#define __CAP241_BSTREE_HPP__

//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercícios 01-05     //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 08/05/2017                            //
//==================================================//

#include <iostream>

// Estrutura de dados do tipo bstree
template <class T>
class bstree
{
public:
	// estrutura aninhada
	struct node
	{
	public:
		T data;
	// os membros de dados das sub-árvores são privados
	private:
		node *left;
		node *right;
		
		node() : left(nullptr), right(nullptr) { }
		node(const T& v, node *l, node *r) : data(v), left(l), right(r) { }

	// permite que funções membros da classe bstree possam
	// acessar os membros de dados privados de um node
	friend class bstree;
	};

	bstree();                                        // construtor
	explicit bstree(std::initializer_list<T> init);  // construtor com lista
	~bstree();                                       // destrutor

	void clear();                                    // limpa árvore
	node* find(T v) const;                           // busca
	node* findParent(node* n) const;                 // busca pai
	node* insert(const T& v);                        // inserção
	void erase(T v);                                 // remoção
	// travessias
	template<class Functor> void preOrder(Functor f) const;
	template<class Functor> void postOrder(Functor f) const;
	template<class Functor> void inOrder(Functor f) const;
	int height();                                    // altura da árvore

private:  
	// Tornando estes dois operadores privados, sem fornecer 
	// implementação, fará com que os objetos bstree não possam ser copiáveis
	bstree(const bstree&);
	bstree& operator=(const bstree&);

	void clear(node *n);
	node* find(node *n, T v) const;
	node* findParent(node *r, node *n) const;
	template<class Functor>
	void preOrder(const node *n, Functor f) const;
	template<class Functor>
	void postOrder(const node *n, Functor f) const;
	template<class Functor>
	void inOrder(const node *n, Functor f) const;
	int height(const node *n) const;

	node *root_;
};

template<class T>
bstree<T>::bstree()
: root_(nullptr)
{  
}

template<class T>
bstree<T>::bstree(std::initializer_list<T> init)
: root_(nullptr)
{
	for(const T& v : init)
		insert(v);
}

template<class T>
bstree<T>::~bstree()
{
	clear(); // destrutor chama clear()
}

// Método clear: limpa toda a árvore
template<class T> 
void bstree<T>::clear()
{
	clear(root_);
}
// deleta nós da árvore com travessia pós-ordem
template<class T> 
void bstree<T>::clear(node *n)
{
	// alterar para postOrder(delete(n))?
	if(n == nullptr)
		return;
	clear(n->left);
	clear(n->right);
	delete n;
}

// Método find: procura pelo elemento de chave v, ou, 
// caso não seja encontrado, retorna nulo.
template<class T> 
typename bstree<T>::node*
bstree<T>::find(T v) const
{
	return find(root_, v);
}
// Método find recursivo com 2 parâmetros de entrada: nó e valor.
template<class T> 
typename bstree<T>::node*
bstree<T>::find(node *n, T v) const
{
	if(n == nullptr)
		return nullptr;
	if(n->data == v)
		return n;
  	return (v < n->data) ? find(n->left, v) : find(n->right, v);
}

// Método findParent recursivo: busca pai do nó passado como parâmetro.
template<class T> 
typename bstree<T>::node*
bstree<T>::findParent(node *n) const
{
	return findParent(root_, n);
}
template<class T> 
typename bstree<T>::node*
bstree<T>::findParent(node *r, node *n) const
{
	if (r->left && r->left->data == n->data || r->right && r->right->data == n->data)
		return r;
	return (n->data < r->data) ? findParent(r->left, n) : findParent(r->right, n);  
}

// Método insert: insere valor na árvore
template<class T> 
typename bstree<T>::node*
bstree<T>::insert(const T& v)
{
	node* n = root_; // começando pela raiz
	node* parent = nullptr; // guardar onde a busca parou
	// busca posição de inserção
	while (n)
	{
		if(n->data == v) // não insere valores duplicados
		{
			// std::cout << "duplicated key!" << std::endl;
			return nullptr;
		}
		parent = n; // nó anterior à próxima busca

		n = (v < n->data) ? n->left : n->right;
	}
  
	node* nn = new node(v, nullptr, nullptr); // cria-se o novo nó
  
	if(parent == nullptr)		// se a árvore estiver vazia
		root_ = nn;
	else if(v < parent->data)	// valor menor que o valor do nó pai?
		parent->left = nn;		// insere-se à esquerda
	else						// senão, à direita
		parent->right = nn;

  return nn;
}

// Método erase: remove valor da árvore
// Alterar de cópia para referência de ponteiro???
template<class T> 
void bstree<T>::erase(T v) {
  
	node* n = find(v); // busca nó com valor v
  
	if(!n) { // verifica se nó realmente existe
		std::cout << "inexistent key!" << std::endl;
		return;
	}
  
	if(!n->left && !n->right) // nó folha?
	{    
		node* parent = findParent(n); // encontra-se o nó pai para remover link
		if (parent->data > n->data)
			parent->left = NULL;
		else
			parent->right = NULL;
		delete n;
	}  
	else if(n->left && !n->right) // possui apenas um nó descendente?
	{
		n = n->left;
		delete n->left;
		n->left = nullptr;
	}
	else if(!n->left && n->right)
	{
		n = n->right;
		delete n->right;
		n->right = nullptr;
	}
	// possui dois nós descendentes?
	// remove nó e coloca nó mais à direita da sub-árvore à esquerda
	// e realoca sub-árvores
	else
	{    
		node* naux = n->left; // naux recebe nó à esquerda de n
		while (naux->right)
		{
			naux = naux->right;
		} // naux contém o nó mais à direita da sub-árvore à esquerda
	
		node* parent_naux = findParent(naux); // parent_naux contém o nó pai de naux

		if (parent_naux->data > naux->data) 
		{ // parent_naux->left recebe sub-árvore à esquerda de naux
			if (!naux->left)
				parent_naux->left = nullptr;
			else
				parent_naux->left = naux->left;
		}
		else 
		{ // parent_naux->right recebe sub-árvore à esquerda de naux
			if (!naux->left)
				parent_naux->right = nullptr;
			else
				parent_naux->right = naux->left; 
		}	
		n->data = naux->data; // nó n recebe dado de naux
		delete naux;
	}
}

// Travessias
template<class T>
template<class Functor>
void bstree<T>::preOrder(Functor f) const
{
	preOrder(root_, f);
}

template<class T> 
template<class Functor>
void bstree<T>::preOrder(const node *n, Functor f) const
{
	if(n == nullptr)
		return;

	f(n->data);

	preOrder(n->left, f);
	preOrder(n->right, f);
}

template<class T> 
template<class Functor>
void bstree<T>::postOrder(Functor f) const
{
	postOrder(root_, f);
}

template<class T> 
template<class Functor>
void bstree<T>::postOrder(const node *n, Functor f) const
{
	if(n == nullptr)
		return;

	postOrder(n->left, f);
	postOrder(n->right, f);

	f(n->data);
}

template<class T> 
template<class Functor>
void bstree<T>::inOrder(Functor f) const
{
	inOrder(root_, f);
}

template<class T> 
template<class Functor>
void bstree<T>::inOrder(const node *n, Functor f) const
{
	if(n == nullptr)
		return;

	inOrder(n->left, f);

	f(n->data);

	inOrder(n->right ,f);
}

template<class T> 
int bstree<T>::height()
{
	return height(root_);
}

template<class T> 
int bstree<T>::height(const node *n) const
{  
	if(n == nullptr)
		return 0;
	return std::max(1 + height(n->left), 1 + height(n->right));
}

#endif // __CAP241_BSTREE_HPP__