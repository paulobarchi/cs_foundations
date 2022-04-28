//==================================================//
//   CAP-241-4 - Computação Aplicada 1              //
//   Lista de exercícios 2 - Exercício 03           //
//   Prof: Gilberto Ribeiro                         //
//   Aluno: Paulo Henrique Barchi                   //
//   Curso: Doutorado - CAP (Computação Aplicada)   //
//   Entrega: 13/04/2017                            //
//==================================================//

// Biblioteca Padrão C++
#include <algorithm>
#include <chrono>
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
	// método para o operador "igual a" (==)
	bool operator == (const point& p2) const
	{
		return (x == p2.getX() && y == p2.getY());
	}
	// método para o operador "menor que" (<)
	bool operator < (const point& p2) const
    {
        return (x < p2.getX()) || (x == p2.getX() && y < p2.getY());
    }
	// função produtoVetorial
	// calcula o produto vetorial dos vetores formados por esses pontos (this, p1 e p2)
	// retorna valor positivo caso o ponto esteja à esquerda da reta, negativo se estiver
	// à direita, e 0 se for colinear.
	double produtoVetorial(const point& p1, const point& p2)
	{    
		// cálculo da equação por partes
		double dx = p2.getX() - p1.getX();
		double dy = p2.getY() - p1.getY();

		return (dx) * (y - p1.getY()) - (dy) * (x - p1.getX());
	}

	// atributos privados
private:  
	double x;
	double y;
};

// função para impressão de vetor de pontos
void printVectorOfPoints(const vector<point>& points)
{
	cout << " { ";
	for (point p : points)
	{
		cout << "(" << p.getX() << ", " << p.getY() << ") ";
	}
	cout << "}" << endl;
}

void defineRandomNPoints(vector<point>& points, size_t& n_points)
{
	// Semente para gerar números aleatórios definida pelo tempo atual,
	// para gerar sempre uma sequência diferente.
	srand(time(NULL));
	
	for(int i = 0; i < n_points; i++)
	{
		// Insere pontos de coordenadas aleatórias limitadas de 1 a 10
		points.insert(points.begin()+i, point(rand() % 10 + 1.0, rand() % 10 + 1.0));
	}	
}

// função para ordernar, remover duplicatas e ajustar tamanho de vetor de pontos
void removeDuplicates(vector<point>& points)
{	
	// ordena
	sort(points.begin(), points.end());
	// remove duplicatas
	points.erase(unique(points.begin(), points.end()), points.end());
}

// função para obter o envoltório convexo dos pontos points
vector<point> getConvexHull(vector<point>& points)
{
	size_t n = points.size();
	size_t convexIndex = 0;

	// caso + simples, com apenas 1 ponto
	// retorna o próprio vetor de pontos passado como parâmetro
	if (n == 1)	
		return points;
	
	// cria vetor de pontos com o envoltório convexo
	vector<point> convexHullPoints;
	convexHullPoints.reserve(2 * n);

	bool valid;

	// loop para primeiro ponto do produto vetorial
	for (size_t i = 0; i < n; ++i)
	{
		// loop para segundo ponto do produto vetorial
		for (size_t j = 0; j < n; ++j)
		{
			// caso sejam diferentes
			if (i != j && !(points[i] == points[j]))
			{
				valid = true;
				// loop para fazer cálculo do produto vetorial com pontos dos outros loops
				for (size_t k = 0; k < n; ++k)
				{
					// caso ponto esteja à esquerda
					if (points[k].produtoVetorial(points[i], points[j]) > 0) {
						valid = false;
						break;
					}
				}
				// insere pontos válidos para envoltório convexo
				if (valid) 
				{
					convexHullPoints.insert(convexHullPoints.begin()+convexIndex++, points[i]);
					convexHullPoints.insert(convexHullPoints.begin()+convexIndex++, points[j]);
				}
			}
		}
	}

	// chama função para remoção de pontos duplicados
	removeDuplicates(convexHullPoints);

	return convexHullPoints;
}

void enunciado()
{
	cout << "\nPrograma referente ao Exercicio 03 da Lista 2 - CAP241-4." << endl;
	cout << "Autor: Paulo Henrique Barchi." << endl;
	cout << "Computação do envoltório convexo de um conjunto de pontos." << endl;
}

int main()
{
	// Enunciado do programa
	enunciado();

	// Variáveis para medir tempo de processamento
	chrono::time_point<chrono::steady_clock> start, end;
	
	// tamanho do vetor de pontos (número de pontos)
	// é iniciado com 10, e, por 10 iterações, tem seu valor dobrado
	vector<size_t> n_points;
	n_points.reserve(10);
	
	n_points.insert(n_points.begin(), 10);

	for (size_t i = 1; i < 10; ++i)
	{
		n_points.insert(n_points.begin()+i, (2 * n_points[i-1] ));
	}

	for (size_t i = 0; i < 10; ++i)
	{

		start = chrono::steady_clock::now();

		// criação do vetor de pontos com reserva de tamanho n_points
		vector<point> points;
		points.reserve(n_points[i]);

		// definição aleatória das coordenadas dos n_points pontos
		defineRandomNPoints(points, n_points[i]);

		// impressão dos pontos 
		// comentado para não interferir na verificação de desempenho
		// cout << " Pontos definidos aleatoriamente: " << endl;
		// printVectorOfPoints(points);

		// obtenção do envoltório convexo
		vector<point> convexHull = getConvexHull(points);

		// impressão dos pontos 
		// comentado para não interferir na verificação de desempenho
		// cout << " Envoltório convexo: " << endl;		
		// printVectorOfPoints(convexHull);

		// obtenção do tempo final de processamento
		end = chrono::steady_clock::now();
		chrono::duration<double> elapsed_time = end - start;
		cout << " Para n = " << n_points[i] << ", tempo = " << elapsed_time.count() << "s\n" << endl;
	}

	cout << "\n Até!\n" << endl;

	return 0;
}