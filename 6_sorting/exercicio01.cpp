//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 5 - Exercício 01           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 28/05/2017                            //
//==================================================//

#include <iostream>
#include <chrono>
#include "sort.hpp"

void getRandomVector(std::vector<int>& v, int n)
{	
	// Semente para gerar números aleatórios definida pelo tempo atual,
	// para gerar sempre uma sequência diferente.
	srand(time(NULL));
	
	for(int i = 0; i < n; i++)
		// Insere valores aleatórios limitadas de 1 a 100000
		v.push_back(rand() % 100000 + 1);
}

void getAscOrderedVector(std::vector<int>& v, int n)
{	
	for(int i = 1; i <= n; i++)
		v.push_back(i);
}

void getDescOrderedVector(std::vector<int>& v, int n)
{	
	for(int i = n; i <= 1; i--)
		v.push_back(i);
}

template<class Functor>
void sortVectors(Functor sortMethod, Functor generateVector)
{
	// Variáveis para medir tempo de processamento
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> elapsed_time;
	double sum_time;
	
	// vetor com tamanhos de vetores (n)
	// é iniciado com 8, e, por 10 iterações, tem seu valor dobrado
	std::vector<int> vec_size;
	vec_size.reserve(10);	
	vec_size.push_back(8);
	for (int i = 1; i < 10; ++i)
	{
		vec_size.push_back(2 * vec_size[i-1]);
	}

	std::cout << "\t\tn\t\tt medio (s)" << std::endl;

	// para cada tamanho de vetor guardado em vec_size
	for (int i = 0; i < 10; ++i)
	{
		sum_time = 0.0;
		// 100 execuções são feitas para obter o tempo médio 
		for (int j = 0; j < 100; ++j)
		{
			// tempo de início
			start = std::chrono::steady_clock::now();

			// criação do vetor de tamanho vec_size[i] a ser ordenado
			std::vector<int> vec;
			vec.reserve(vec_size[i]);

			// definição dos elementos do vetor
			generateVector(vec, vec_size[i] + 1);

			// sort
			sortMethod(vec, vec_size[i]);

			// obtenção do tempo final de processamento
			end = std::chrono::steady_clock::now();
			elapsed_time = end - start;
			sum_time += elapsed_time.count();
		}
		std::cout << "\t\t" << vec_size[i] << "\t\t" << sum_time/100 << std::endl;
	}
}

template<class Functor>
void sortTests(Functor sortMethod)
{	
	std::cout << "\n # Random Vectors #" << std::endl;
	sortVectors(sortMethod, getRandomVector);
	std::cout << "\n # Ordered Vectors - Ascending #" << std::endl;
	sortVectors(sortMethod, getAscOrderedVector);
	std::cout << "\n # Ordered Vectors - Descending #" << std::endl;
	sortVectors(sortMethod, getDescOrderedVector);
}

void enunc()
{
	std::cout << "\nPrograma referente aos Exercício 01 da Lista 5 - CAP241-4." << std::endl
		<< "Autor: Paulo Henrique Barchi." << std::endl
		<< "Ordenação.\n";
}

int menu()
{
	int opcao;
	std::cout << "\n Selecione o número do método de ordenação desejado (ou 99 para Sair):" << std::endl <<
		"  1. Selection Sort" << std::endl << 
		"  2. Insertion Sort" << std::endl << 
		"  3. Shell Sort" << std::endl << 
		"  4. Heap Sort" << std::endl << 
		"  5. Merge Sort" << std::endl << 
		"  6. Quick Sort" << std::endl << 
		"  7. std::sort" << std::endl << 
		"  8. std::stable_sort" << std::endl << 
		"  9. std::sort_heap" << std::endl << 
		"  99. Sair" << std::endl << 
		"\n  Opção: ";

	std::cin >> opcao;

	return opcao;
}

int main()
{
	enunc();

	int opcao = 0;

	while (opcao != 99)
	{
		opcao = menu();
		switch(opcao) {
			case 1:
				std::cout << "\n\t ### Selection Sort ###" << std::endl;
				sortTests(selectionSort);
				break;
			case 2:
				std::cout << "\n\t ### Insertion Sort ###" << std::endl;
				sortTests(insertionSort);
				break;
			case 3:
				std::cout << "\n\t ### Shell Sort ###" << std::endl;
				sortTests(shellSort);
				break;
			case 4:
				std::cout << "\n\t ### Heap Sort ###" << std::endl;
				sortTests(heapSort);
				break;
			case 5:
				std::cout << "\n\t ### Merge Sort ###" << std::endl;
				sortTests(mergeSort);
				break;
			case 6:
				std::cout << "\n\t ### Quick Sort ###" << std::endl;
				sortTests(quickSort);
				break;
			case 7:
				std::cout << "\n\t ### std::sort ###" << std::endl;
				sortTests(stdSort);
				break;				
			case 8:
				std::cout << "\n\t ### std::stable_sort ###" << std::endl;
				sortTests(stdStableSort);
				break;				
			case 9:
				std::cout << "\n\t ### std::sort_heap ###" << std::endl;
				sortTests(stdSortHeap);
				break;
			case 99:
				std::cout << std::endl;
				break;
			default:
				break;
		}
	}

	return EXIT_SUCCESS;
}