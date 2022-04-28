//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 3 - Exercício 02           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 17/04/2017                            //
//==================================================//

// C++ Standard Library
#include <iostream>       // std::cout, std::cin, std::endl
#include <string>         // std::string
#include <sstream>        // std::ostringstream
#include <locale>         // std::locale, std::isdigit

// Pilha
#include "stack.hpp"

// função booleana para verificar se parâmetro char é operador
bool isOperator(char charToVerify)
{
  return (charToVerify == '+' || charToVerify == '-' || 
    charToVerify == '*' || charToVerify == '/');
}

// função booleana para verificar se parâmetro string é operador
bool isOperator(std::string charToVerify)
{
  return (charToVerify == "+" || charToVerify == "-" || 
    charToVerify == "*" || charToVerify == "/");
}

// função para obter precedência do operador
// pré-requisito: parâmetro char ser de fato um dos 4 operadores
int getPrecedence(char operador)
{
  return (operador == '+' || operador == '-') ? 0 : 1;
}

// função para obter precedência do operador
// pré-requisito: parâmetro string ser de fato um dos 4 operadores
int getPrecedence(std::string operador)
{
  return (operador == "+" || operador == "-") ? 0 : 1;
}

// função que recebe string com expressão infixa e 
// retorna string com expressão pós-fixa
std::string transformaInfixaEmPosFixa(std::string infixa)
{
  stack<std::string> s; // pilha
  std::string pos_fixa; // string a ser retornada com notação pós-fixa
  
  // enquanto não chegar ao fim da expressão
  for (std::string::size_type i = 0; i < infixa.length(); ++i)
  { 
    // caso seja dígito (operando)
    if (std::isdigit(infixa[i]))
    {
      // coloca dígito (operando) na expressão de saída
      pos_fixa += infixa[i];
    }
    // senão, caso seja operador
    else if (isOperator(infixa[i])) 
    {
      // caso a pilha esteja fazia ou tenha um parêntese esquerdo no topo
      // ou caso o operador tenha maior precedência que o top da pilha
      if ( ( s.empty() || s.top() == "(" ) || 
        (isOperator(s.top()) && getPrecedence(infixa[i]) > getPrecedence(s.top()) ) )
      {
        // empilha operador
        // s.push(std::string(1, infixa[i]));
        s.push(std::string(1, infixa[i]));
      }
      else 
      {
        // escreve operador do topo da pilha e desempilha
        pos_fixa.append(s.top());
        s.pop();
        // empilha operador lido
        s.push(std::string(1, infixa[i]));
      }
    }
    // senão, caso seja parêntese esquerdo
    else if(infixa[i] == '(')
      // empilha
      s.push(std::string(1, infixa[i]));
    // senão, caso seja parêntese direito
    else if(infixa[i] == ')')
    {
      // enquanto não aparecer 
      while (s.empty() || s.top() != "(")
      {
        // desempilha e imprime operador
        pos_fixa.append(s.top());
        s.pop();
      }
      s.pop(); // desempilha parêntese esquerdo correspondente
    }
  }
  // depois de ler toda a string de entrada, esvazia-se a pilha
  while(!s.empty())
  {
    if (isOperator(s.top())) pos_fixa.append(s.top());
    s.pop();
  }

  return pos_fixa;
}

double convertStringToDouble(std::string x)
{
  return atof(x.c_str());
}

// função que realiza operação dados os operandos e operador
std::string realizaOperacao(std::string op1,std::string op2, char operador)
{
  double resultado;
  switch(operador)
  {
    case '+':
      resultado = convertStringToDouble(op1) + convertStringToDouble(op2);
      break;

    case '-':
      resultado = convertStringToDouble(op1) - convertStringToDouble(op2);
      break;

    case '*':
      resultado = convertStringToDouble(op1) * convertStringToDouble(op2);
      break;

    case '/':
      resultado = convertStringToDouble(op1) / convertStringToDouble(op2);
      break;
      default:;
  }
  std::ostringstream resultado_stream;
  resultado_stream << resultado;
  return resultado_stream.str();
}

// função que avalia expressão pós-fixa
double avaliaExpressao(std::string pos_fixa)
{
  stack<std::string> s; // pilha
  double resultado; // resultado da avaliação a ser retornado
  std::string op1, op2;      // operandos das operações parciais

  // enquanto não chegar ao fim da expressão
  for (std::string::size_type i = 0; i < pos_fixa.length(); ++i)
  { 
    // caso seja dígito (operando)
    if (std::isdigit(pos_fixa[i]))
    {
      // empilha
      s.push(std::string(1, pos_fixa[i]));
    }
    // senão, caso seja operador
    else if (isOperator(pos_fixa[i])) 
    {
      // desempilha os operandos
      op2 = s.top();
      s.pop();
      op1 = s.top();
      s.pop();
      // empilha retorno da função realizaOperacao
      s.push(realizaOperacao(op1, op2, pos_fixa[i]));
    }
  }
  // ao fim da cadeia, haverá apenas o resultado final na pilha
  resultado = convertStringToDouble(s.top());
  s.pop();

  return resultado;
}

void enunciado()
{
  std::cout << "\nPrograma referente ao Exercicio 02 da Lista 3 - CAP241-4." << std::endl;
  std::cout << "Autor: Paulo Henrique Barchi." << std::endl;
  std::cout << "Calculadora aritmética com notação polonesa utilizando TAD Pilha." << std::endl;
}

int main()
{
  // Enunciado do programa
  enunciado();
  std::string expressao_infixa;

  std::cout << "\nPor favor, insira a expressão com notação infixa a ser avaliada:" << std::endl;
  std::getline (std::cin, expressao_infixa);

  std::string expressao_pos_fixa = transformaInfixaEmPosFixa(expressao_infixa);
  std::cout << "\n Expressão com notação pós-fixa: ";
  std::cout << expressao_pos_fixa << std::endl;

  std::cout << "\n Avaliação da expressão: " << avaliaExpressao(expressao_pos_fixa) << "\n" << std::endl;
   
  return 0;
}