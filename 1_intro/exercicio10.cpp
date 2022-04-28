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
  // função avaliaInterseccao
  // retorna true se há intersecção dos segmentos de reta; retorna false caso contrário
  bool avaliaInterseccao(const lineSegment& T)
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
    // os segmentos se interceptam
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

int main()
{
  // Enunciado do programa
  cout << "\nPrograma referente ao Exercicio 10 da Lista 1 - CAP241-4." << endl;
  cout << "Autor: Paulo Henrique Barchi." << endl;
  cout << "Avaliação se dois segmentos de reta se interceptam ou não." << endl;

  // declaração de variáveis: coordenadas dos pontos
  double p1_x, p1_y, p2_x, p2_y, p3_x, p3_y ,p4_x, p4_y;

  cout << "\nPor favor, forneça as coordenadas de dois pontos pertencentes à primeira reta." << endl;
  cout << " Ponto p1, coordenada x: ";
  cin >> p1_x;
  cout << " Ponto p1, coordenada y: ";
  cin >> p1_y;
  point p1(p1_x, p1_y);

  // atribuição e verificação do ponto p2: deve ser diferente de p1
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

  // Com estes dois primeiros pontos, temos o primeiro segmento de reta
  lineSegment S(p1, p2);

  cout << "\nPor favor, forneça as coordenadas de dois pontos pertencentes à segunda reta." << endl;
  cout << " Ponto p3, coordenada x: ";
  cin >> p3_x;
  cout << " Ponto p3, coordenada y: ";
  cin >> p3_y;
  point p3(p3_x, p3_y);

  // atribuição e verificação do ponto p4: deve ser diferente de p3
  // para conseguirmos estabelecer uma reta e para não zerar o denominador
  // na equação de Hessean
  p4_x = p3_x;
  p4_y = p3_y;
  while (p3_x == p4_x && p3_y == p4_y)
  {
    cout << "\n Ponto p4, coordenada x: ";
    cin >> p4_x;
    cout << " Ponto p4, coordenada y: ";
    cin >> p4_y;    
  }
  point p4(p4_x, p4_y);

  // Com estes outros dois pontos, temos o outro segmento de reta
  lineSegment T(p3, p4);

  // Chama função para avaliação de intersecção e exibe resultado
  if (S.avaliaInterseccao(T)) 
    cout << "\n Há intersecção entre os segmentos de retas dados pelos pontos fornecidos." << endl;
  else
    cout << "\n Não há intersecção entre os segmentos de retas dados pelos pontos fornecidos." << endl;

  cout << "\nAté!\n" << endl;

  return 0;
}