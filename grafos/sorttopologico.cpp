#include "GrafoMapa.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

template <class V, class C>
void sort_top(const Grafo<V,C> & grafo, list<int> & recorrido,
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
			sort_top(grafo, recorrido, w, visitados);
		}
	}
	recorrido.push_front(v);
}

template <class V, class C>
void sort_topologico(const Grafo<V,C> & grafo, list<int> & sort_t, int n)
{
	vector<bool> visitados(n, false);
	list<int> vertices;
  
	grafo.devolverVertices(vertices);
	list<int>::iterator it_vert;
	for (it_vert = vertices.begin(); it_vert != vertices.end(); it_vert++)
	{
		int v = *it_vert;
		if (!visitados[v])
		{
			sort_top(grafo, sort_t, v, visitados);
		}
	}
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

	g.agregarVertice(1, "C1");
	g.agregarVertice(2, "C2");
	g.agregarVertice(3, "C3");
	g.agregarVertice(4, "C4");
	g.agregarVertice(5, "C5");

	g.agregarArco(1, 3, 1);
	g.agregarArco(2, 3, 1);
	g.agregarArco(2, 4, 1);
	g.agregarArco(3, 5, 1);
	g.agregarArco(4, 5, 1);	

	list<int> sort_t;
	sort_topologico(g, sort_t, 5);
	mostrarRecorridoGrafo(g, sort_t);
	
	return 0;
}

