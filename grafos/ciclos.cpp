#include "GrafoMapa.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define NO_DESC -1

bool es_arco_retroceso(int u, int v, const vector<int> & descubierto,
		       const vector<int> & fin_desc)
{
	return (descubierto[u] >= descubierto[v] &&
		fin_desc[v] == NO_DESC);
}


template <class V, class C>
bool tiene_ciclos(const Grafo<V,C> & grafo, int v, vector<bool> & visitado,
		  vector<int> & descubierto, vector<int> & fin_desc, int & tiempo)
{
	visitado[v] = true;
	descubierto[v] = tiempo;
	tiempo++;

	list<pair<int, C> > adyacentes;
	grafo.devolverAdyacentes(v, adyacentes);
	typename list<pair<int, C> >::iterator ady = adyacentes.begin();
	bool cicla = false;
	while (ady != adyacentes.end() && !cicla)
	{
		int w = ady->first;
		if (!visitado[w])
		{
			cicla = tiene_ciclos(grafo, w, visitado, descubierto,
					     fin_desc, tiempo);
		}
		else
		{
			cicla = es_arco_retroceso(v, w, descubierto, fin_desc);			
		}
		ady++;
	}
	fin_desc[v] = tiempo;
	tiempo++;
	return cicla;
}

template <class V, class C>
bool tiene_ciclos_forest(const Grafo<V,C> & grafo, int n)
{
	int tiempo = 0;
	vector<bool> visitado(n, false);
	vector<int> descubierto(n, NO_DESC);
	vector<int> fin_desc(n, NO_DESC);

	list<int> vertices;
	grafo.devolverVertices(vertices);
	list<int>::iterator vert = vertices.begin();
	bool cicla = false;
	while (vert != vertices.end() && !cicla)
	{
		if (!visitado[*vert])
		{
			cicla = tiene_ciclos(grafo, *vert, visitado,
					     descubierto, fin_desc, tiempo);
		}
		vert++;
	}
	return cicla;
}

int main(int argc, char **argv)
{
	GrafoMapa<string, int> g;

	g.agregarVertice(1, "A");
	g.agregarVertice(2, "B");
	g.agregarVertice(3, "C");
	g.agregarVertice(4, "D");
	g.agregarVertice(5, "E");
	g.agregarVertice(6, "F");
	g.agregarVertice(7, "G");

	g.agregarArco(1, 2, 1);
	g.agregarArco(1, 3, 1);
	g.agregarArco(1, 4, 1);
	g.agregarArco(2, 6, 2);
	g.agregarArco(3, 5, 3);	
	g.agregarArco(4, 7, 4);
	g.agregarArco(5, 1, 1);
	g.agregarArco(5, 6, 5);

	if (tiene_ciclos_forest(g, 8)) 
	{
		cout << "El grafo tiene ciclos" << endl;
	}
	else
	{
		cout << "El grafo no tiene ciclos" << endl;
	}
	return 0;
}

