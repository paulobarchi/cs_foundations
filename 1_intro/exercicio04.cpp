//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 04           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 31/03/2017                            //
//==================================================//

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{	
	// Enunciado do programa
	cout << "\nPrograma referente ao Exercicio 04 da Lista 1 - CAP241-4." << endl;
	cout << "Autor: Paulo Henrique Barchi." << endl;
	cout << "Preenchimento de vetor com números aleatórios com tamanho do vetor ";
	cout << "definido pelo usuário. Apresentação da média dos elementos desse vetor." << endl;

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
		soma += vetor[i]; // Já adiciona elemento atual à soma total
	}
	// Feito cast de soma para float a fim de se obter a média como float
	cout << "Média dos elementos do vetor: " << (float)soma / tamanho_vetor << endl;

	cout << "Até!\n" << endl;

	return 0;
}