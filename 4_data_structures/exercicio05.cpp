//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 4 - Exercício 05           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 08/05/2017                            //
//==================================================//

// STL
#include <cmath>
#include <random>

// Exemplos
#include "bstree.hpp"

void enunciado()
{
	std::cout << "\nPrograma referente aos Exercícios 05 da Lista 4 - CAP241-4." << std::endl
		<< "Autor: Paulo Henrique Barchi." << std::endl
		<< "Verificação da altura em árvores binárias de pesquisa." << std::endl
	<< "Geração de números aleatórios com distribuições uniformes para inserções nas árvores. " 
	<< std::endl;
}

int main()
{
	// Enunciado do programa
	enunciado();
	std::cout << "\n\tn\t\theight\t\theight/log2n\n";
	// para sequências de tamanho n = 10^exp
	for (int exp = 0; exp < 6; ++exp)
	{ 
		int n = pow(10, (exp + 1));
		// criação de uma árvore vazia para cada sequência
		bstree<int> t;
		// gerador de números aleatórios com distribuição uniforme
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_int_distribution<int> distr(1, n);
		// gerando cada elemento de cada sequência
		for (int i = 0; i < n; ++i)
		{
			while (!t.insert(distr(generator)));
		}
		int h = t.height();
		std::cout << "\t" << n
			<< "\t\t  " << h
			<< "\t\t   " <<  h / (log(n) / log(2.0)) << std::endl;
  	}
	std::cout << "\n";

	return EXIT_SUCCESS;
}