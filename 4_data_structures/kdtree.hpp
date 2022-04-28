#ifndef __CAP241_KDTREE_HPP__
#define __CAP241_KDTREE_HPP__

//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercício 06           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 08/05/2017                            //
//==================================================//

#include <iostream>
#include <vector>

// classe ponto
class point
{
public:
	point() : x(0), y(0) { }
	point(double xval, double yval) : x(xval), y(yval) { }
	~point() { }
	double getX() const { return x; }
	double getY() const { return y; }
	bool operator == (const point& p2) const
	{
		return (x == p2.getX() && y == p2.getY());
	}
private:  
	double x;
	double y;
};

// Estrutura de dados do tipo kdtree
class kdtree
{
public:

	// estrutura aninhada
	struct node
	{
	public:
		point pt;     	
	// os membros de dados das sub-árvores são privados
	private:
		node *left;
		node *right;
		
		node() : left(nullptr), right(nullptr) { }
		node(const point& p, node *l, node *r) : pt(p), left(l), right(r) { }
		
		// permite que funções membros da classe kdtree possam
		// acessar os membros de dados privados de um node
		friend class kdtree;
	};
  
	kdtree();     	               // construtor
	~kdtree();	                   // destrutor

	node* insert(const point& p);  // inserção

	node* find(point p) const;     // retorna o nó da árvore com o ponto p
	node* find(node* n, point p, bool isOddLevel) const;

	// retorna conjunto de nós da árvore contidos no retângulo de busca
	std::vector<node*>& search(double xmin, double xmax, 
	double ymin, double ymax, std::vector<node*>& vec) const;
	void search(node* n, double xmin, double xmax, 
	double ymin, double ymax, bool isOddLevel, std::vector<node*>& vec) const;

	void clear();               	 // limpa árvore
	void clear(node *n);
  
private:  
	// Tornando estes dois operadores privados, sem fornecer 
	// implementação, fará com que os objetos kdtree não possam ser copiáveis
	kdtree(const kdtree&);
	kdtree& operator=(const kdtree&);

	node *root_;
};

kdtree::kdtree()
: root_(nullptr)
{
}

kdtree::~kdtree()
{
	clear(); // destrutor chama clear()
}

// Método clear: limpa toda a árvore
void kdtree::clear()
{
	clear(root_);
}
// deleta nós da árvore com travessia pós-ordem
void kdtree::clear(node *n)
{
	if(n == nullptr)
		return;
	clear(n->left);
	clear(n->right);
	delete n;
}

// Método find: procura pelo elemento de chave v, ou, 
// caso não seja encontrado, retorna nulo.
typename kdtree::node*
kdtree::find(point p) const
{
	return find(root_, p, true);
}
// Método find recursivo com 2 parâmetros de entrada: nó e valor.
typename kdtree::node*
kdtree::find(node *n, point p, bool isOddLevel) const
{
	if(n == nullptr)
		return nullptr;
	if(p == n->pt)
		return n;
	if (isOddLevel)
		return (p.getX() < n->pt.getX()) ? 
			find(n->left, p, !isOddLevel) : find(n->right, p, !isOddLevel);

	return (p.getY() < n->pt.getY()) ? 
		find(n->left, p, !isOddLevel) : find(n->right, p, !isOddLevel);
}


// Método search: retorna o conjunto de todos os nós cujos pontos
// estão contidos no retângulo de busca.
std::vector<typename kdtree::node*>&
kdtree::search(double xmin, double xmax, double ymin, double ymax, 
	std::vector<node*>& vec) const
{
  std::cout << "\n Busca com xmin = " << xmin << ", xmax = " << xmax 
	<< ", ymin = " << ymin << ", ymax = " << ymax << std::endl;
  search(root_, xmin, xmax, ymin, ymax, true, vec);
  return vec;
}
// Método search recursivo
// std::vector<typename kdtree::node*>
void 
kdtree::search(node *n, double xmin, double xmax, double ymin, double ymax, 
	bool isOddLevel, std::vector<node*>& vec) const
{
	if(n != nullptr)
	{
		// em nível ímpar da árvore, verifica x
		if (isOddLevel) 
		{
			if(n->pt.getX() < xmin)
				search(n->right, xmin, xmax, ymin, ymax, !isOddLevel, vec);
	  
			else if(n->pt.getX() > xmax)
				search(n->left, xmin, xmax, ymin, ymax, !isOddLevel, vec);
	  
			// se x está no intervalo, verifica-se y
			// se y também estiver adiciona este nó ao conjunto
			else 
			{
				if(n->pt.getY() >= ymin && n->pt.getY() <= ymax)
					vec.push_back(n);
				search(n->left, xmin, xmax, ymin, ymax, !isOddLevel, vec);
				search(n->right, xmin, xmax, ymin, ymax, !isOddLevel, vec);
	  		}
		}
		// em nível par, verifica-se y
		else 
		{
			if(n->pt.getY() < ymin)
				search(n->right, xmin, xmax, ymin, ymax, !isOddLevel, vec);
	  
			else if(n->pt.getY() > ymax)
				search(n->left, xmin, xmax, ymin, ymax, !isOddLevel, vec);
	  
			// se y está no intervalo, verifica-se x
			// se x também estiver adiciona este nó ao conjunto
			else
			{
				if(n->pt.getX() >= xmin && n->pt.getX() <= xmax)
					vec.push_back(n);
				search(n->left, xmin, xmax, ymin, ymax, !isOddLevel, vec);
				search(n->right, xmin, xmax, ymin, ymax, !isOddLevel, vec);
			}
		}
	}
}

// Método insert: insere valor na árvore
typename kdtree::node*
kdtree::insert(const point& p)
{
	bool isOddLevel = false;
	// começando pela raiz
	node* n = root_;
	// guardar onde a busca parou
	node* parent = nullptr;
	// busca posição de inserção
	while (n != nullptr)
	{
		// não insere valores duplicados
		if(n->pt == p)
		{
			std::cout << "duplicated key!" << std::endl;
			return nullptr;
		}
		// nó anterior à próxima busca
		parent = n;

		isOddLevel = !isOddLevel;

		if (isOddLevel)
			n = (p.getX() < n->pt.getX()) ? n->left : n->right;
		else 
			n = (p.getY() < n->pt.getY()) ? n->left : n->right;
	}
	// cria-se o novo nó
	node* nn = new node(p, nullptr, nullptr);
	// se a árvore estiver vazia
	if(parent == nullptr)
		root_ = nn;
  	else if (isOddLevel) 
	{
		if(p.getX() < parent->pt.getX())
			parent->left = nn;
		else
			parent->right = nn;
	}
	else
	{
		if(p.getY() < parent->pt.getY())
			parent->left = nn;
		else
			parent->right = nn; 
	}
	return nn;
}

#endif // __CAP241_KDTREE_HPP__