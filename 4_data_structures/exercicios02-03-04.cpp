//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercícios 02, 03, 04  //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 08/05/2017                            //
//==================================================//

// Exemplos
#include "bstree.hpp"

void print(int a)
{
	std::cout << a << " ";
}

template<class T>
void goThroughTree(bstree<T>& t)
{
	std::cout << "\n Escrita em pré-ordem: ";
	t.preOrder(print);
	std::cout << "\n Escrita em pós-ordem: ";
	t.postOrder(print);
	std::cout << "\n Escrita em in-ordem: ";
	t.inOrder(print);
	std::cout << "\n Árvore de altura: " << t.height() << std::endl;
}

void teste_bstree_int()
{
	std::cout << "\n ## int bstree ##" << std::endl;
	std::cout << " Inserindo elementos" << std::endl;
	bstree<int> t {15, 7, 22, 3, 13, 9, 20, 5, 11, 4, 30};
	goThroughTree(t);
	
	std::cout << "\n\n Procurando 7 na árvore..." << std::endl;
	t.find(7) ? std::cout << " Encontrado!" : std::cout << " Não encontrado.";
	std::cout << std::endl;

	std::cout << "\n Removendo 7 da árvore " << std::endl;
	t.erase(7);
	goThroughTree(t);

	std::cout << "\n Procurando 7 na árvore..." << std::endl;
	t.find(7) ? std::cout << " Encontrado!" : std::cout << " Não encontrado.";
	std::cout << std::endl;

	std::cout << "\n Removendo 22 da árvore " << std::endl;
	t.erase(22);
	goThroughTree(t);
	
	std::cout << "\n Removendo 11 da árvore " << std::endl;
	t.erase(11);
	goThroughTree(t);

	std::cout << "\n Removendo 15 da árvore " << std::endl;
	t.erase(15);
	goThroughTree(t);

	std::cout << "\n Removendo 4 da árvore " << std::endl;
	t.erase(4);
	goThroughTree(t);

}

void enunciado()
{
	std::cout << "\nPrograma referente aos Exercícios 02, 03 e 04 da Lista 4 - CAP241-4." << std::endl;
	std::cout << "Autor: Paulo Henrique Barchi." << std::endl;
	std::cout << "Operações em árvores binárias de pesquisa." << std::endl;
}

int main()
{
	// Enunciado do programa
	enunciado();

	teste_bstree_int();

	std::cout << "\n";

	return EXIT_SUCCESS;
}