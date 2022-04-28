//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 09           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 31/03/2017                            //
//==================================================//

#include <cmath>
#include <iostream>

using namespace std;

// classe point (ponto)
class point
{
public:
  // construtor
  point(double xval, double yval) 
    : x(xval), y(yval) 
  {      
  }
  // destrutor
  ~point() 
  {    
  }
  // método para acesso ao valor de x do ponto
  double getX() const
  {
    return x;
  }
  // método para acesso ao valor de y do ponto
  double getY() const
  {
    return y;
  }
// atributos privados
private:  
  double x;
  double y;
};

// função formaNormalDeHesseanParaRetas
// calcula a distância de um ponto a uma reta, dados dois pontos pertecentes a ela
double formaNormalDeHesseanParaRetas(const point& p1, const point& p2, const point& p3)
{    
  // cálculo da equação por partes
  double dy = p2.getY() - p1.getY();
  double dx = p2.getX() - p1.getX();

  double numerator = dy * (p3.getX() - p1.getX()) - (dx) * (p3.getY() - p1.getY());

  double denominator = sqrt(pow(dx, 2) + pow(dy, 2));

  return (numerator / denominator);
}

// função distanciaDePontoAReta 
// retorna o valor absoluto da função formaNormalDeHesseanParaRetas
double distanciaDePontoAReta(const point& p1, const point& p2, const point& p3) 
{
  return abs(formaNormalDeHesseanParaRetas(p1, p2, p3));
}

int main()
{
  // Enunciado do programa
  cout << "\nPrograma referente ao Exercicio 09 da Lista 1 - CAP241-4." << endl;
  cout << "Autor: Paulo Henrique Barchi." << endl;
  cout << "Cálculo da menor distância entre um ponto e uma reta." << endl;

  // declaração de variáveis: coordenadas dos pontos
  double p1_x, p1_y, p2_x, p2_y, p3_x, p3_y;

  cout << "\nPor favor, forneça as coordenadas de dois pontos pertencentes à reta." << endl;
  cout << " Ponto p1, coordenada x: ";
  cin >> p1_x;
  cout << " Ponto p1, coordenada y: ";
  cin >> p1_y;
  point p1(p1_x, p1_y);

  // atribuição e verificação do segundo ponto (p2): deve ser diferente de p1
  // para conseguirmos estabelecer uma reta e para não zerar o denominador
  // na equação de Hessean
  p2_x = p1_x;
  p2_y = p1_y;
  while (p1_x == p2_x && p1_y == p2_y)
  {
    cout << "\n Ponto p2, coordenada x: ";
    cin >> p2_x;
    cout << " Ponto p2, coordenada y: ";
    cin >> p2_y;
  }
  point p2(p2_x, p2_y);

  cout << "\nAgora, forneça as coordenadas do ponto para o qual a distância deve ser avaliada ";
  cout << "em relação à reta que passa pelos dois pontos anteriores." << endl;
  cout << " Ponto p3, coordenada x: ";
  cin >> p3_x;
  cout << " Ponto p3, coordenada y: ";
  cin >> p3_y;
  point p3(p3_x, p3_y);

  cout << "\nA distância do ponto p3 à reta dos pontos p1 e p2 é de ";
  cout << distanciaDePontoAReta(p1, p2, p3) << "." << endl;

  cout << "\nAté!\n" << endl;

  return 0;
}