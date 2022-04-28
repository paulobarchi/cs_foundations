//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 05           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 31/03/2017                            //
//==================================================//

#include <iostream>
#include <cstdlib>

using namespace std;

void ordena(int A[], int n)
{
	for(int j = 0; j < n - 1; ++j)
	{
		int m = j;

		for(int i = j + 1; i < n; ++i)
		{
			if(A[i] > A[m])
				m = i;
		}

		std::swap(A[m], A[j]);
	}
}

int main()
{	
	// Enunciado do programa
	cout << "\nPrograma referente ao Exercicio 05 da Lista 1 - CAP241-4." << endl;
	cout << "Autor: Paulo Henrique Barchi." << endl;
	cout << "Alteração da função ordena para que ordene o vetor de forma decrescente." << endl;

	// Declaração de variáveis
	// Definição do tamanho do vetor pelo usuário
	size_t tamanho_vetor;
	cout << "\nPor favor, forneça o tamanho do vetor: ";
	cin >> tamanho_vetor; 
	// Como não foi especificado, o tipo do vetor foi considerado como int.	
	int vetor[tamanho_vetor];
	int soma = 0;
	// Semente para gerar números aleatórios definida pelo tempo atual,
	// para gerar sempre uma sequência diferente.
	srand(time(NULL));
	
	cout << "Elementos do vetor definidos aleatoriamente:" << endl;
	for(int i = 0; i < tamanho_vetor; i++)
	{
		// Valores aleatórios limitados de 1 a 100
		vetor[i] = rand()%10 + 1;
		cout << vetor[i] << endl; // Imprime valor gerado
	}
	
	// Chama função ordena
	ordena(vetor, tamanho_vetor);

	// Imprime vetor ordenado
	cout << "\nVetor ordenado de forma decrescente: " << endl;
	for(int i = 0; i < tamanho_vetor; i++)
	{
		cout << vetor[i] << endl;
	}

	cout << "Até!\n" << endl;

	return 0;
}