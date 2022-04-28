//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercício 01           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 08/05/2017                            //
//==================================================//

// Exemplos
#include "mwtree.hpp"

void enunciado()
{
	std::cout << "\nPrograma referente aos Exercício 01 da Lista 4 - CAP241-4." << std::endl
		<< "Autor: Paulo Henrique Barchi." << std::endl
		<< "Árvores multivias." << std::endl;
}

void checkParent(const mwtree<int>* t)
{
  if (t->has_parent())
	std::cout << "Sim: " << t->get_parent()->data << std::endl;
  else 
	std::cout << "Não." << std::endl;
}

void checkDescendants(const mwtree<int>* t)
{
	if (t->has_children())
  		std::cout << "Sim. " << t->get_children_count() << " filho(s) e " 
			<< t->get_descendants_count() << " descendente(s)." << std::endl;
  	else 
		std::cout << "Não." << std::endl;
}

int main()
{
	// Enunciado do programa
	enunciado();

	std::cout << "\n ## int mwtree ##" << std::endl;

	std::cout << "\n Criação do elemento t1 = ";
	mwtree<int>* t1 = new mwtree<int>(5);
	std::cout << t1->data << std::endl;
	std::cout << " t1 tem pai? ";
	checkParent(t1);

	std::cout << "\n Criação do elemento t2 = " ;
	mwtree<int>* t2 = new mwtree<int>(13);
	t1->push_back(t2);
	std::cout << t2->data << std::endl << " t2 tem pai? ";
	checkParent(t2);

	std::cout << " t1 tem filhos? ";
	checkDescendants(t1);

	std::cout << "\n Inserção do elemento t3 = ";
	mwtree<int>* t3 = new mwtree<int>(16);
	t2->push_back(t3);
	std::cout << t3->data << std::endl << " t3 tem pai? ";
	checkParent(t3);

	std::cout << "\n Inserção do elemento t4 = ";
	int i = 0;
	mwtree<int>* t4 = new mwtree<int>(7);
	t2->insert(i, t4);
	std::cout << t2->get_child(i)->data << " na posição " << i << " dos filhos de t2"
	<< std::endl << " t4 tem pai? ";
	checkParent(t4);

	std::cout << " t2 tem filhos? ";
	checkDescendants(t2);

	std::cout << " t1 tem filhos? ";
	checkDescendants(t1);

	std::cout << "\n Inserção do elemento t5 = ";
	mwtree<int>* t5 = new mwtree<int>(16);
	t2->push_back(t5);
	std::cout << t5->data << std::endl << " t5 tem pai? ";
	checkParent(t5);

	std::cout << "\n t4 e t5";
	if (!t4->is_sibling(t5)) std::cout << " não";
	std::cout << " são irmãos." << std::endl;

	std::cout << "\n t2 tem filhos? ";
	checkDescendants(t2);

	std::cout << " t1 tem filhos? ";
	checkDescendants(t1);

	std::cout << "\n";

	return EXIT_SUCCESS;
}