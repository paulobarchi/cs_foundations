//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercícios 06          //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 08/05/2017                            //
//==================================================//

// Exemplos
#include "kdtree.hpp"

void printAndInsertPoint(const point& p, kdtree* t)
{
	std::cout << " Inserindo ponto";  
	std::cout << " (" << p.getX() << ", " << p.getY() << ")" << std::endl;
	t->insert(p);
}

void printPoints(std::vector<kdtree::node*> vec)
{
	std::cout << " Pontos encontrados: " << std::endl;
	for (kdtree::node* n : vec)
		std::cout <<  "\t(" << n->pt.getX() << ", " << n->pt.getY() << ")" << std::endl;
}

void teste_kdtree_int()
{
	std::cout << "\n ## kdtree ##" << std::endl;
	kdtree *t = new kdtree();
  
	point p1(10, 10);
	printAndInsertPoint(p1, t);

	point p2(8, 11);
	printAndInsertPoint(p2, t);

	point p3(14, 8);
	printAndInsertPoint(p3, t);

	point p4(9, 7);
	printAndInsertPoint(p4, t);

	point p5(5, 13);
	printAndInsertPoint(p5, t);

	point p6(11, 5);
	printAndInsertPoint(p6, t);

	point p7(12, 12);
	printAndInsertPoint(p7, t);

	point p8(6, 6);
	printAndInsertPoint(p8, t);

	point p9(13, 7);
	printAndInsertPoint(p9, t);

	point p10(7, 7);
	printAndInsertPoint(p10, t);

	std::cout << "\n Busca pelo ponto: (" << p6.getX() << ", " << p6.getY() << ")" << std::endl;
	if (t->find(p6) != nullptr && t->find(p6)->pt == p6) 
		std::cout << " Encontrado!" << std::endl;
	else 
		std::cout << " Não encontrado." << std::endl;

	point p11(13, 13);
	std::cout << "\n Busca pelo ponto: (" << p11.getX() << ", " << p11.getY() << ")" << std::endl;
	if (t->find(p11) != nullptr && t->find(p11)->pt == p11) 
		std::cout << " Encontrado!" << std::endl;
	else 
		std::cout << " Não encontrado." << std::endl;

	// busca com xmin = ymin = 5 e xmax = ymax = 9
	std::vector<kdtree::node*> vec;
	printPoints(t->search(5, 9, 5, 9, vec));
}

void enunciado()
{
	std::cout << "\nPrograma referente aos Exercícios 02, 03 e 04 da Lista 4 - CAP241-4." << std::endl;
	std::cout << "Autor: Paulo Henrique Barchi." << std::endl;
	std::cout << "Operações em kdtrees." << std::endl;
}

int main()
{
	// Enunciado do programa
	enunciado();

	teste_kdtree_int();

	std::cout << "\n";

	return EXIT_SUCCESS;
}