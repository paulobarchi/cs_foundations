//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 08           //
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

// constante PI para conversão de graus decimais para radianos
const double PI = atan(1) * 4;

// função para conversão de pontos em graus decimais para pontos em radianos
point pontoEmGrausDecimaisParaRadianos(point pontoEmGrausDecimais) {
    double radX, radY;
    radX = (pontoEmGrausDecimais.getX() * PI) / 180;
    radY = (pontoEmGrausDecimais.getY() * PI) / 180;
    point pontoEmRadianos(radX, radY);
    return pontoEmRadianos;
}

// função distanciaHaversine
// pontos como parâmetros por referência e constantes
double distanciaHaversine(const point& p, const point& q)
{
  // declaração e atribuição do raio da esfera em kilômetros
  const double r = 6371;

  point point1 = pontoEmGrausDecimaisParaRadianos(p);
  point point2 = pontoEmGrausDecimaisParaRadianos(q);
  
  // cálculo da equação por partes
  double firstPartOfSqrt = pow(sin((point2.getY() - point1.getY()) / 2), 2);
  double secondPartOfSqrt = cos(point1.getY()) * cos(point2.getY()) * 
                              pow(sin((point2.getX() - point1.getX()) / 2), 2);
  double sqroot = sqrt(firstPartOfSqrt + secondPartOfSqrt);
  double distHaversine = 2 * r * asin(sqroot);

  // retorno com valor da distancia de Haversine dos pontos p e q
  return distHaversine;
}

int main()
{
  // Enunciado do programa
  cout << "\nPrograma referente ao Exercicio 08 da Lista 1 - CAP241-4." << endl;
  cout << "Autor: Paulo Henrique Barchi." << endl;
  cout << "Cálculo da função de distância de Haversine entre dois pontos dados em coordenadas de ";
  cout << "latitude [-90 a 90] e longitude [-180 a 180], em grau-decimal." << endl;

  // Declaração de variáveis - coordenadas dos pontos a serem lidos
  // Atribuição inicial para funcionar loop que verifica o intervalo válido de valores
  double p1_x, p1_y, p2_x, p2_y;
  p1_x = p1_y = p2_x = p2_y = 181;

  // Entrada de dados com verificação de valores para latitude e longitude de cada ponto
  cout << "\nPor favor, forneça as coordenadas de latitude e longitude ";
  cout << "dos pontos, em grau-decimal. " << endl;

  while (p1_y < -90 || p1_y > 90) 
  {
    cout << " Ponto p1 - latitude: ";
    cin >> p1_y;
  }
  while (p1_x < -180 || p1_x > 180) 
  {
    cout << " Ponto p1 - longitude: ";
    cin >> p1_x;
  }
  // Criação do objeto p1
  point p1(p1_x, p1_y);

  while (p2_y < -90 || p2_y > 90) 
  {
    cout << " Ponto p2 - latitude: ";
    cin >> p2_y;
  }
  while (p2_x < -180 || p2_x > 180) 
  {
    cout << " Ponto p2 - longitude: ";
    cin >> p2_x;
  }
  // Criação do objeto p2
  point p2(p2_x, p2_y);

  // Cálculo e apresentação da distância de Haversine
  cout << "A distância de Haversine entre estes pontos é de ";
  cout << distanciaHaversine(p1, p2) << " km." << endl;

  cout << "\nAté!\n" << endl;

  return 0;
}