#include "GrafoMapa.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <class V, class C>
void dfs(const Grafo<V,C> & grafo, list<int> & recorrido,
	 int v, vector<bool> & visitados)
{
	visitados[v] = true;

	list<pair<int, C> > adyacentes;
	grafo.devolverAdyacentes(v, adyacentes);
	typename list<pair<int, C> >::iterator ady;
	for (ady = adyacentes.begin(); ady != adyacentes.end(); ady++)
	{
		int w = ady->first;
		if (!visitados[w])
		{
			dfs(grafo, recorrido, w, visitados);
		}
	}
	recorrido.push_back(v);
}


template <typename V, typename C>
void mostrarRecorridoGrafo(const Grafo<V,C> & grafo, const list<int> & recorrido)
{
	list<int>::const_iterator v = recorrido.begin();
	while (v != recorrido.end())
	{
		cout << grafo.devolverVertice(*v) << "\n";
		v++;
	}
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
	g.agregarArco(5, 6, 5);

	list<int> recorrido;
	vector<bool> visitados(7, false);
	dfs(g, recorrido, 1, visitados);
	mostrarRecorridoGrafo(g, recorrido);
	
	return 0;
}

