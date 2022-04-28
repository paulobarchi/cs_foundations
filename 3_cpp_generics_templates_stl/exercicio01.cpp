//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 3 - Exercício 01           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 17/04/2017                            //
//==================================================//

// STL
#include <algorithm>
#include <iostream>
#include <string>

// Exemplos
#include "list.hpp"

template<class T> void print(const list<T>& l)
{
	std::cout << "( ";

	typename list<T>::iterator it = l.begin();
  
	while(it != l.end())
	{
	    std::cout << *it << ", ";
	    
	    ++it;
	}

	std::cout << " )" << std::endl;
}

void teste_list_int()
{
	std::cout << "\n ## int Lists ##" << std::endl;
	list<int> l {2, 7, 3, 5};

	print(l);

	list<int>::iterator it = std::find(l.begin(), l.end(), 7);
  
	if(it != l.end())
	{
		std::cout << *it << std::endl;

		it = l.erase(it);

		std::cout << *it << std::endl;
	}

	print(l);

	it = std::find(l.begin(), l.end(), 5);
  
	if(it != l.end())
	{
	    it = l.insert(it, 8);
	    
	    std::cout << *it << std::endl;
	}

	print(l);

	l.insert(l.begin(), 9);
	print(l);

	// std::cout << std::boolalpha << l.empty() << std::endl;

	// l.clear();

	// std::cout << std::boolalpha << l.empty() << std::endl;

	print(l);

	// ## Operações adicionadas ##
	// é necessário checar se a lista não está vazia antes de chamar
	// operações que envolvem pop e front 
	if (!l.empty())
	{
		std::cout << " front() test: " << l.front() << std::endl;
		std::cout << " back() test: " << l.back() << std::endl;
		std::cout << " push_front() test: " << *(l.push_front(4)) << std::endl;
		std::cout << "Lista l: ";
  		print(l);
  		std::cout << " push_back() test: " << *(l.push_back(1)) << std::endl;
  		std::cout << "Lista l: ";
  		print(l);
  		std::cout << " pop_front() test: " << l.pop_front() << std::endl;
  		std::cout << "Lista l: ";
  		print(l);  	
  		std::cout << " pop_back() test: " << l.pop_back() << std::endl;
  		std::cout << "Lista l: ";
  		print(l);
  	}
	
	std::cout << " reverse() test: " << std::endl;
	l.reverse();
	std::cout << "Lista l: ";
	print(l);
	std::cout << " front() test: " << l.front() << std::endl;
	std::cout << " (re)reverse() test: " << std::endl;
	l.reverse();
	std::cout << "Lista l: ";
	print(l);

	list<double> l1{1, 4, 11};
 	std::cout << "Lista l1: ";
 	print(l1);
	// std::cout << " splice() test: " << std::endl;
	// l.splice(l1);
	// std::cout << "Lista l: ";
	// print(l);

	list<double> l2{3, 6, 9};
	std::cout << "Lista l2: ";
	print(l2);
	std::cout << " merge() test: " << std::endl;
	l1.merge(l2);
	std::cout << "Lista l1: ";
	print(l1);
	std::cout << "Lista l2: ";
	print(l2);
}

void teste_list_double()
{
	std::cout << "\n ## double Lists ##" << std::endl;
	list<double> l{3.14, 2.71, 1.41, 1.73};

	print(l);

	list<double>::iterator it = std::find(l.begin(), l.end(), 1.73);

	if(it != l.end())
	{
		std::cout << *it << std::endl;

		it = l.erase(it);

		if(it == l.end())
			std::cout << "marcador de fim de lista!" << std::endl;
	}

	print(l);

	// ## Operações adicionadas ##
	// é necessário checar se a lista não está vazia antes de chamar
	// operações que envolvem pop e front 
	if (!l.empty())
	{
		std::cout << " front() test: " << l.front() << std::endl;
		std::cout << " back() test: " << l.back() << std::endl;
		std::cout << " push_front() test: " << *(l.push_front(2.5)) << std::endl;
		std::cout << "Lista l: ";
	  	print(l);
	  	std::cout << " push_back() test: " << *(l.push_back(1.33)) << std::endl;
	  	std::cout << "Lista l: ";
	  	print(l);
	  	std::cout << " pop_front() test: " << l.pop_front() << std::endl;
	  	std::cout << "Lista l: ";
	  	print(l);  	
	  	std::cout << " pop_back() test: " << l.pop_back() << std::endl;
	  	std::cout << "Lista l: ";
	  	print(l);
	}
	
	std::cout << " reverse() test: " << std::endl;
	l.reverse();
	std::cout << "Lista l: ";
	print(l);
	std::cout << " (re)reverse() test: " << std::endl;
	l.reverse();
	std::cout << "Lista l: ";
	print(l);

	list<double> l1{0.0, 1.4, 7.66};
 	std::cout << "Lista l1: ";
 	print(l1);
	// std::cout << " splice() test: " << std::endl;
	// l.splice(l1);
	// std::cout << "Lista l: ";
	// print(l);

	list<double> l2{0.3, 0.6, 0.9};
	std::cout << "Lista l2: ";
	print(l2);
	std::cout << " merge() test: " << std::endl;
	l1.merge(l2);
	std::cout << "Lista l1: ";
	print(l1);
	std::cout << "Lista l2: ";
	print(l2);

}

void teste_list_string()
{	
	std::cout << "\n ## string Lists ##" << std::endl;

	list<std::string> l{"Gilberto", "Sandra", "Celso", "Karine"};

	print(l);

	list<std::string>::iterator it = std::find(l.begin(), l.end(), "Sandra");

	if(it != l.end())
	{
		std::cout << *it << std::endl;

		it = l.erase(it);

		std::cout << *it << std::endl;
  	}

  	std::cout << "Lista l: ";
  	print(l);

  	// ## Operações adicionadas ##
	// é necessário checar se a lista não está vazia antes de chamar
	// operações que envolvem pop e front 
	if (!l.empty())
	{
		std::cout << " front() test: " << l.front() << std::endl;
		std::cout << " back() test: " << l.back() << std::endl;
		std::cout << " push_front() test: " << *(l.push_front("Paulo")) << std::endl;
		std::cout << "Lista l: ";
	  	print(l);
	  	std::cout << " push_back() test: " << *(l.push_back("Chomsky")) << std::endl;
	  	std::cout << "Lista l: ";
	  	print(l);
	  	std::cout << " pop_front() test: " << l.pop_front() << std::endl;
	  	std::cout << "Lista l: ";
	  	print(l);  	
	  	std::cout << " pop_back() test: " << l.pop_back() << std::endl;
	  	std::cout << "Lista l: ";
	  	print(l);
	}
	
	std::cout << " reverse() test: " << std::endl;
	l.reverse();
	std::cout << "Lista l: ";
	print(l);
	std::cout << " (re)reverse() test: " << std::endl;
	l.reverse();
	std::cout << "Lista l: ";
	print(l);

	list<std::string> l1{"Asimov", "Newton", "Turing"};
 	std::cout << "Lista l1: ";
 	print(l1);
	// std::cout << " splice() test: " << std::endl;
	// l.splice(l1);
	// std::cout << "Lista l: ";
	// print(l);

	list<std::string> l2{"Albert", "Bach", "Democritus"};
	std::cout << "Lista l2: ";
	print(l2);
	std::cout << " merge() test: " << std::endl;
	l1.merge(l2);
	std::cout << "Lista l1: ";
	print(l1);
	std::cout << "Lista l2: ";
	print(l2);
}

void enunciado()
{
	std::cout << "\nPrograma referente ao Exercicio 01 da Lista 3 - CAP241-4." << std::endl;
	std::cout << "Autor: Paulo Henrique Barchi." << std::endl;
	std::cout << "Operações em listas duplamente encadeadas." << std::endl;
}

int main()
{
	// Enunciado do programa
	enunciado();

	std::cout << sizeof(list_item<int>) << std::endl;
	std::cout << sizeof(list_item<double>) << std::endl;
	std::cout << sizeof(list_item<std::string>) << std::endl;

	teste_list_int();
	teste_list_double();
	teste_list_string();

	return EXIT_SUCCESS;
}