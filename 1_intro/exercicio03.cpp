//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 03           //
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
	cout << "\nPrograma referente ao Exercicio 03 da Lista 1 - CAP241-4." << endl;
	cout << "Autor: Paulo Henrique Barchi." << endl;
	cout << "Preenchimento de vetor de tamanho fixo com números aleatórios ";
	cout << "e soma dos elementos desse vetor. Vetor definido em tempo de compilação" << endl;

	// Declaração de variáveis.
	// Como não foi especificado, o tamanho do vetor adotado foi 10
	// e o tipo do vetor, int.
	const size_t tamanho_vetor = 10; // definição do tamanho fixo do vetor
	int vetor[tamanho_vetor];
	int soma = 0;
	// Semente para gerar números aleatórios definida em tempo de compilação,
	// para gerar sempre uma sequência diferente.	
	srand(time(SEMENTE));
	
	cout << "Elementos do vetor definidos aleatoriamente:" << endl;
	for(int i = 0; i < tamanho_vetor; i++)
	{
		// Valores aleatórios limitados de 1 a 100
		vetor[i] = rand()%100 + 1;
		cout << vetor[i] << endl; // Imprime valor gerado
		soma += vetor[i]; // Já adiciona elemento atual à soma total
	}
	
	cout << "Soma dos elementos do vetor: " << soma << endl;

	cout << "Até!\n" << endl;

	return 0;
}