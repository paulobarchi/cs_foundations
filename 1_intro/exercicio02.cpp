//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 02           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 31/03/2017                            //
//==================================================//

#include <iostream>
#include <string>

using namespace std;

int main()
{	
	// Enunciado do programa
	cout << "\nPrograma referente ao Exercicio 02 da Lista 1 - CAP241-4." << endl;
	cout << "Autor: Paulo Henrique Barchi." << endl;
	cout << "Leitura e avaliação de tamanho para os lados de um triângulo." << endl;

	// Declaração de variáveis
	// Não foi especificado o tipo de dado para os lados do triangulo, aqui definidos como float
	float lado1, lado2, lado3 = 0;	
	
	while (lado1 >= 0 && lado2 >= 0 && lado3 >= 0) 
	{
		// Entrada de dados
		cout << "\nPor favor, forneça o tamanho dos 3 lados do triângulo a serem avaliados." << endl;
		cout << "Para sair, forneça valores negativos (por exemplo, \"-1\") ";
		cout << "a qualquer momento (para qualquer lado)." << endl;
		cout << "\nLado 1: ";
		cin >> lado1;
		// Para cada entrada, verifica condição de saída
		if (lado1 < 0) 
			break;
		cout << "Lado 2: ";
		cin >> lado2;
		if (lado2 < 0) 
			break;
		cout << "Lado 3: ";
		cin >> lado3;
		if (lado3 < 0) 
			break;
		// Verificação se os lados formam um triângulo de fato
		if ((lado1 + lado2 > lado3) && (lado1 + lado3 > lado2) && (lado2 + lado3 > lado1))
		{
			// Classificação entre isósceles, escaleno ou equilátero
			cout << "\nTamanhos de lados fornecidos formam um triângulo ";

			// Equilátero: todos os lados iguais
			if ((lado1 == lado2) && (lado2 == lado3))
				cout << "equilátero." << endl;

			// Isósceles: dois lados iguais entre si e um diferente
			else if ((lado1 == lado2) || (lado1 == lado3) || (lado2 == lado3))
				cout << "isósceles." << endl;

			// Escaleno: todos os lados diferentes entre si
			else
				cout << "escaleno." << endl;
		} else 
			cout << "\nTamanhos de lados fornecidos não formam um triângulo." << endl;
	
	}

	cout << "Até!\n" << endl;

	return 0;
}