//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 1 - Exercício 10           //
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
  // método para alteração dos valores x e y do ponto
  void setXY(double xval, double yval)
  {
    x = xval;
    y = yval;
  }
  // método que verifica se outro ponto é igual a este
  bool equals(point p2) 
  {
    return (x == p2.getX() && y == p2.getY()) ? true : false;
  }  
  // função formaNormalDeHesseanParaRetas
  // calcula a distância de um ponto a uma reta, dados dois pontos pertecentes a ela
  double formaNormalDeHesseanParaRetas(const point& p1, const point& p2)
  {    
    // cálculo da equação por partes
    double dy = p2.getY() - p1.getY();
    double dx = p2.getX() - p1.getX();

    double numerator = dy * (x - p1.getX()) - (dx) * (y - p1.getY());

    double denominator = sqrt(pow(dx, 2) + pow(dy, 2));

    return (numerator / denominator);
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
  // construtor sem parâmetros
  lineSegment() : p1(), p2()
  {   
  }
  // construtor com parâmetros
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
  // método para avaliação de intersecção entre segmentos adjacentes em um polinômio
  bool avaliaInterseccaoAdjacente(const lineSegment& T)
  {
    // Variável booleana que mantém controle sobre a avaliação da 
    // inserseptação dos segmentos de reta. É atribuído false inicialmente, 
    // e se algum caso de interptação além do caso si ^ si+1 = vi+1 for verificado, 
    // se_interceptam = true.
    bool se_interceptam = false;

    // variáveis para manipular os pontos
    point p3 = T.getP1();
    point p4 = T.getP2();

    // variáveis com resultados dos cálculos da forma normal de Hessean
    double formaNormalDeHessean_p1 = p1.formaNormalDeHesseanParaRetas(p3, p4);
    double formaNormalDeHessean_p2 = p2.formaNormalDeHesseanParaRetas(p3, p4);
    double formaNormalDeHessean_p3 = p3.formaNormalDeHesseanParaRetas(p1, p2);
    double formaNormalDeHessean_p4 = p4.formaNormalDeHesseanParaRetas(p1, p2);

    // variáveis booleanas para auxiliar nas verificações  
    bool p1_colinear_p3p4 = (formaNormalDeHessean_p1 == 0);
    bool p2_colinear_p3p4 = (formaNormalDeHessean_p2 == 0);

    bool p3_colinear_p1p2 = (formaNormalDeHessean_p3 == 0);
    bool p4_colinear_p1p2 = (formaNormalDeHessean_p4 == 0);


    bool p1_entre_p3_p4 = ( ( p1.getX() <= p3.getX() && p1.getX() >= p4.getX() ) || 
              ( p1.getX() <= p4.getX() && p1.getX() >= p3.getX() ) );
    bool p2_entre_p3_p4 = ( ( p2.getX() < p3.getX() && p2.getX() >= p4.getX() ) || 
              ( p2.getX() <= p4.getX() && p2.getX() > p3.getX() ) );

    bool p3_entre_p1_p2 = ( ( p3.getX() <= p1.getX() && p3.getX() > p2.getX() ) || 
              ( p3.getX() < p2.getX() && p3.getX() >= p1.getX() ) );
    bool p4_entre_p1_p2 = ( ( p4.getX() <= p1.getX() && p4.getX() >= p2.getX() ) || 
              ( p4.getX() <= p2.getX() && p4.getX() >= p1.getX() ) );


    bool p1ep2_opostos = 
      (formaNormalDeHessean_p1 * formaNormalDeHessean_p2 < 0);
    bool p3ep4_opostos = 
      (formaNormalDeHessean_p3 * formaNormalDeHessean_p4 < 0);

    // verifica se a única intersecção entre estes segmentos é o vértice que os conecta
    // para cada ponto, caso ele seja colinear ao outro segmento e esteja entre os pontos
    // do segmento, OU, caso cada par de pontos seja oposto em relação ao outro segmento:
    // os segmento se interceptam
    if ( !p2.equals(p3) ) {
      se_interceptam = true;
    }  else if ( (p1_colinear_p3p4 && p1_entre_p3_p4) || (p2_colinear_p3p4 && p2_entre_p3_p4) || 
        (p3_colinear_p1p2 && p3_entre_p1_p2) || (p4_colinear_p1p2 && p4_entre_p1_p2) || 
        (p1ep2_opostos && p3ep4_opostos) )
      
      se_interceptam = true;

    return se_interceptam;
  }

  // função avaliaInterseccaoNaoAdjacente: original do exercicio10
  // retorna true se há intersecção dos segmentos de reta; 
  // retorna false caso contrário
  bool avaliaInterseccaoNaoAdjacente(const lineSegment& T)
  {
    // Variável booleana que mantém controle sobre a avaliação da 
    // inserseptação dos segmentos de reta. É atribuído false inicialmente, 
    // e se algum caso de interptação for verificado, se_interceptam = true.
    bool se_interceptam = false;

    // variáveis para manipular os pontos
    point p3 = T.getP1();
    point p4 = T.getP2();

    // variáveis com resultados dos cálculos da forma normal de Hessean
    double formaNormalDeHessean_p1 = p1.formaNormalDeHesseanParaRetas(p3, p4);
    double formaNormalDeHessean_p2 = p2.formaNormalDeHesseanParaRetas(p3, p4);
    double formaNormalDeHessean_p3 = p3.formaNormalDeHesseanParaRetas(p1, p2);
    double formaNormalDeHessean_p4 = p4.formaNormalDeHesseanParaRetas(p1, p2);

    // variáveis booleanas para auxiliar nas verificações  
    bool p1_colinear_p3p4 = (formaNormalDeHessean_p1 == 0);
    bool p2_colinear_p3p4 = (formaNormalDeHessean_p2 == 0);

    bool p3_colinear_p1p2 = (formaNormalDeHessean_p3 == 0);
    bool p4_colinear_p1p2 = (formaNormalDeHessean_p4 == 0);


    bool p1_entre_p3_p4 = ( ( p1.getX() <= p3.getX() && p1.getX() >= p4.getX() ) || 
              ( p1.getX() <= p4.getX() && p1.getX() >= p3.getX() ) );
    bool p2_entre_p3_p4 = ( ( p2.getX() <= p3.getX() && p2.getX() >= p4.getX() ) || 
              ( p2.getX() <= p4.getX() && p2.getX() >= p3.getX() ) );

    bool p3_entre_p1_p2 = ( ( p3.getX() <= p1.getX() && p3.getX() >= p2.getX() ) || 
              ( p3.getX() <= p2.getX() && p3.getX() >= p1.getX() ) );
    bool p4_entre_p1_p2 = ( ( p4.getX() <= p1.getX() && p4.getX() >= p2.getX() ) || 
              ( p4.getX() <= p2.getX() && p4.getX() >= p1.getX() ) );


    bool p1ep2_opostos = 
      (formaNormalDeHessean_p1 * formaNormalDeHessean_p2 < 0);
    bool p3ep4_opostos = 
      (formaNormalDeHessean_p3 * formaNormalDeHessean_p4 < 0);


    // para cada ponto, caso ele seja colinear ao outro segmento e esteja entre os pontos
    // do segmento, OU, caso cada par de pontos seja oposto em relação ao outro segmento:
    // os segmento se interceptam
    if ( ( p1_colinear_p3p4 && p1_entre_p3_p4 ) || ( p2_colinear_p3p4 && p2_entre_p3_p4 ) || 
            ( p3_colinear_p1p2 && p3_entre_p1_p2 ) || ( p4_colinear_p1p2 && p4_entre_p1_p2 ) ||
            ( p1ep2_opostos && p3ep4_opostos ) )
      
      se_interceptam = true;

    return se_interceptam;
  }
// atributos privados
private:
  point p1;
  point p2;
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
  // método para impressão dos pontos do polinômio
  void printPolygon() 
  {
    cout << "\nPolígono formado pelos vértices:\n";
    for (size_t i = 0; i < numVertices; ++i)
    {
      cout << " (" << boundary[i].getX() << ", " << boundary[i].getY() << ")" << endl;
    }
  }
  // método para avaliação se o polinômio é simples
  bool avaliaPolinomioSimples()
  {
    // montando array de segmentos
    vector<lineSegment> polygonSegments(numVertices-1);
    for (size_t i = 0; i < numVertices-1; ++i)
    {
      polygonSegments[i] = lineSegment(boundary[i], boundary[i+1]);
    }
    
    // passa pelos pares de segmentos verificando se a única intersecção
    // (si ^ si+1 = vi+1) ocorre
    for (size_t i = 0; i < numVertices-2; ++i)
    {
      if (polygonSegments[i].avaliaInterseccaoAdjacente(polygonSegments[i+1])) 
      {
        return false;
      }
    }

    // verifica para cada segmento se há intersecção com seus segmentos não adjacentes
    // para cada segmento
    for (size_t i = 0; i < numVertices-1; ++i) 
    {
      // verifica se há intersecção com outros segmentos que não sejam ele próprio ou os adjacentes
      for (size_t j = 2; j < numVertices-1; ++j) 
      {
        if ( !(i == 0 && j == numVertices-2) && (j > i) && ( (i + 1 <= numVertices-1) && (j != i + 1) ) && 
          polygonSegments[i].avaliaInterseccaoNaoAdjacente(polygonSegments[j])) 
        {
          return false;
        }
      }
    }

    return true;
  }
  // função para calcular área do polígono
  double calculaAreaPoligono() 
  {
    double numerator = 0.0;

    for (size_t i = 0; i < numVertices - 1; ++i) 
    {
      numerator += (boundary[i].getX() * boundary[i+1].getY()) - (boundary[i].getY() * boundary[i+1].getX());
    }
    return abs(numerator / 2);
  }
// atributos privados
private:
  vector<point> boundary;
  size_t numVertices;
};

int main()
{
  // Enunciado do programa
  cout << "\nPrograma referente ao Exercicio 12 da Lista 1 - CAP241-4." << endl;
  cout << "Autor: Paulo Henrique Barchi." << endl;
  cout << "Computação da área de um polígono simples." << endl;

  // Como os casos de teste devem ser apresentados aqui no programa principal,
  // não há possibilidade de leitura de dados de entrada referente ao polígono.

  // Caso de teste 1: polígono simples
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
  simplePolygon polygon(boundary, numVertices);
  
  polygon.printPolygon();

  if (polygon.avaliaPolinomioSimples()) 
    cout << " A área deste polígono simples é de " << polygon.calculaAreaPoligono() << "." << endl;
  else
    cout << " Não é um polígono simples." << endl;

  cout << "\nAté!\n" << endl;

  return 0;
}