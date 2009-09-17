#include "Grafo.h"
#include "Lista.h"

#include <iostream>

using namespace std;

#define NO_DESC -1

bool es_arco_retroceso(int u, int v, const int descubierto[],
		       const int fin_desc[])
{
	return (descubierto[u] >= descubierto[v] &&
		fin_desc[v] == NO_DESC);
}


template <typename C>
bool tiene_ciclos(const Grafo<C> & grafo, int v, bool visitado[],
		  int descubierto[], int fin_desc[], int & tiempo)
{
	visitado[v] = true;
	descubierto[v] = tiempo;
	tiempo++;

	Lista<typename Grafo<C>::Arco> adyacentes;
	grafo.devolverAdyacentes(v, adyacentes);
	typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
	bool cicla = false;
	while (!ady.llegoAlFinal() && !cicla)
	{
		int w = ady.elementoActual().devolverAdyacente();
		if (!visitado[w])
		{
			cicla = tiene_ciclos(grafo, w, visitado, descubierto,
					     fin_desc, tiempo);
		}
		else
		{
			cicla = es_arco_retroceso(v, w, descubierto, fin_desc);			
		}
		ady.avanzar();
	}
	fin_desc[v] = tiempo;
	tiempo++;
	return cicla;
}

template <typename C>
bool tiene_ciclos_forest(const Grafo<C> & grafo)
{
	int tiempo = 0;
	const int n = grafo.devolverLongitud();
	//se asume que los vértices fueron numerados de 0 a n-1
	bool visitado[n];
	int descubierto[n];
	int fin_desc[n];
	for (int i = 0; i < n; i++)
	{
		visitado[i] = false;
		descubierto[i] = fin_desc[i] = NO_DESC;
	}
	Lista<int> vertices;
	grafo.devolverVertices(vertices);
	Lista<int>::Iterador vert = vertices.devolverIterador();
	bool cicla = false;
	while (!vert.llegoAlFinal() && !cicla)
	{
		int v = vert.elementoActual();
		if (!visitado[v])
		{
			cicla = tiene_ciclos(grafo, v, visitado,
					     descubierto, fin_desc, tiempo);
		}
		vert.avanzar();
	}
	return cicla;
}

int main(int argc, char **argv)
{
	Grafo<int> g;
	enum {A, B, C, D, E, F, G};
	g.agregarVertice(A);
	g.agregarVertice(B);
	g.agregarVertice(C);
	g.agregarVertice(D);
	g.agregarVertice(E);
	g.agregarVertice(F);
	g.agregarVertice(G);

	g.agregarArco(A, B, 1);
	g.agregarArco(A, C, 1);
	g.agregarArco(A, D, 1);
	g.agregarArco(B, F, 1);
	g.agregarArco(C, E, 1);	
	g.agregarArco(D, E, 1);
	g.agregarArco(E, A, 1);
	g.agregarArco(E, F, 1);

	if (tiene_ciclos_forest(g)) 
	{
		cout << "El grafo tiene ciclos" << endl;
	}
	else
	{
		cout << "El grafo no tiene ciclos" << endl;
	}
	return 0;
}

