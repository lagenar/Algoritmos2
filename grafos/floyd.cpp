#include "Grafo.h"
#include "Lista.h"

#include <iostream>

using namespace std;

#define SIN_CAMINO -1
#define INT_MAX 1000

template <int N>
void floyd(const Grafo<int> & grafo, int distancia[N][N], int camino[N][N])
{	
     for (int i = 0; i < N; i++)
	     for (int k = 0; k < N; k++)
		     if (i == k)
		     {
			     distancia[i][k] = 0;
			     camino[i][k] = i;
		     }
		     else if (grafo.existeArco(i, k))
		     {
			     distancia[i][k] = grafo.costoArco(i, k);
			     camino[i][k] = k;
		     }
		     else
		     {
			     distancia[i][k] = INT_MAX;
			     camino[i][k] = SIN_CAMINO;
		     }

     for (int j = 0; j < N; j++)
	     for (int i = 0; i < N; i++)
		     for (int k = 0; k < N; k++) 
			     if (distancia[i][k] > distancia[i][j] + distancia[j][k])
			     {
				     distancia[i][k] = distancia[i][j] + distancia[j][k];
				     camino[i][k] = j;
			     }
}

int main()
{
	Grafo<int> g;
	enum {A, B, C};
	const int n = 3;
	g.agregarVertice(A);
	g.agregarVertice(B);
	g.agregarVertice(C);
	
	g.agregarArco(A, B, 10);
	g.agregarArco(A, C, 15);
	g.agregarArco(B, C, 3);
	
	int dist[n][n];
	int camino[n][n];
	
	const char impr[] = "ABC";
	floyd(g, dist, camino);
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
			if (dist[i][k] == INT_MAX)
			{
				cout << "oo ";
			}
			else
			{
				cout << dist[i][k] << " ";
			}
		cout << endl;
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
			if (camino[i][k] == SIN_CAMINO)
			{
				cout << "S ";
			}
			else
			{
				cout << impr[camino[i][k]] << " ";
			}
		cout << endl;
	}

			
	return 0;
}
