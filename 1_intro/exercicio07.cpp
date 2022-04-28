//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 07           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 31/03/2017                            //
//==================================================//

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// classe point (ponto)
class point
{
public:
  // construtor sem parâmetros, atribui coordenadas (0,0)
  point() : x(0), y(0)
  {
  }
  // construtor com parâmetros
  point(double xval, double yval) : x(xval), y(yval) 
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
  // método para alteração do valor x do ponto
  void setX(double xval)
  {
    x = xval;
  }
  // método para acesso ao valor de y do ponto
  double getY() const
  {
    return y;
  }
  // método para alteração do valor x do ponto
  void setY(double yval)
  {
    y = yval;
  }
  // método para alteração dos valores x e y do ponto
  void setXY(double xval, double yval)
  {
    x = xval;
    y = yval;
  }
// atributos privados
private:  
  double x;
  double y;
};

// classe lineSegment (segmento de linha)
class lineSegment 
{
public:
  // construtor
  lineSegment(point point1, point point2) : p1(point1), p2(point2) 
  {    
  }
  // destrutor
  ~lineSegment() 
  {    
  }
  // método para acesso do ponto p1
  point getP1() const 
  {
    return p1;
  }
  // método para acesso do ponto p2
  point getP2() const 
  {
    return p2;
  }
// atributos privados
private:
  point p1;
  point p2;
};

// classe lineString (linha poligonal)
class lineString
{
public:
  // construtor
  lineString(vector<point> verts, size_t numVerts) : vertices(verts), numVertices(numVerts) 
  {      
  }
  // destrutor
  ~lineString() 
  {    
  }
  // método para acesso a vertices
  vector<point> getVertices()
  {
    return vertices;
  }
  // método para acesso a num_vertices
  size_t getNumVertices() const
  {
    return numVertices;
  }
// atributos privados
private:
  vector<point> vertices;
  size_t numVertices;
};

// classe simple_polygon (polígono simples)
class simplePolygon 
{
public:
  // construtor 
  simplePolygon(vector<point> boundaryPoints, size_t numVerts) : boundary(boundaryPoints), numVertices(numVerts)
  {
  }
  // destrutor
  ~simplePolygon()
  {
  }
  // método para acesso a boundary
  vector<point> getBoundary() const
  {
    return boundary;
  }
  // método para acesso a numVertices
  size_t getNumVertices() const
  {
    return numVertices;
  }
  void printPolygon() 
  {
    cout << "\nPolígono formado pelos vértices:\n";
    for (size_t i = 0; i < numVertices; ++i)
    {
      cout << " (" << boundary[i].getX() << ", " << boundary[i].getY() << ")" << endl;
    }
  }
// atributos privados
private:
  vector<point> boundary;
  size_t numVertices;
};

int main()
{ 
  // Enunciado do programa
  cout << "\nPrograma referente ao Exercicio 07 da Lista 1 - CAP241-4." << endl;
  cout << "Autor: Paulo Henrique Barchi." << endl;
  cout << "Criação de estruturas para elementos geométricos: pontos, segmentos de linha, ";
  cout << "linhas poligonais e polígonos simples. É calculado o perímetro de um polígono ";
  cout << "para teste destas classes." << endl;

  // Vamos calcular o perímetro de um polígono simples. Para isso, precisamos criar 
  // o polígono simples, e, para criá-lo, precisamos da quantidade de vertices,
  // e do vetor de vértices.
  size_t numVertices = 6;
  vector<point> boundary = 
  {
    point(3.0, 5.0),
    point(2.8, 4.0),
    point(4.0, 2.5),
    point(2.0, 1.0),
    point(1.0, 3.0),
    point(3.0, 5.0)
  };

  // Criação do polígono com estes elementos
  simplePolygon poly(boundary, numVertices);
  
  poly.printPolygon();
  
  // Declaração e atribuição inicial do perímetro
  double perimetro = 0.0;

  // Cálculo do perímetro deste polígono
  for(size_t i = 0; i < (poly.getNumVertices() - 1); ++i)
  {
    double dx = poly.getBoundary()[i].getX() - poly.getBoundary()[i + 1].getX();
    double dy = poly.getBoundary()[i].getY() - poly.getBoundary()[i + 1].getY();

    perimetro += sqrt(pow(dx, 2) + pow(dy, 2));
  }

  // impressão do perímetro
  cout << "\n Perímetro: " << perimetro << endl;

  cout << "\nAté!\n" << endl;

  return 0;
}