#include "GrafoMapa.h"
#include <iostream>
#include <set>
#include <string>
#include <queue>

using namespace std;

template <class V, class C>
void bfs(const Grafo<V,C> & grafo, list<int> & recorrido)
{
	recorrido.clear();
	
	list<int> vertices;
 	grafo.devolverVertices(vertices);
	if (!vertices.empty())
	{
		queue<int> abiertos;
		set<int> cerrados;
		abiertos.push(vertices.front());
		while (!abiertos.empty())
		{
			int actual = abiertos.front();
			abiertos.pop();
			if (cerrados.find(actual) == cerrados.end())
			{
				recorrido.push_back(actual);
				cerrados.insert(actual);
				list<pair<int,C> > adyacentes;
				grafo.devolverAdyacentes(actual, adyacentes);
				typename list<pair<int,C> >::iterator ady = adyacentes.begin();
				while (ady != adyacentes.end())
				{
					abiertos.push(ady->first);
					ady++;
				}
			}
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
	bfs(g, recorrido);
	mostrarRecorridoGrafo(g, recorrido);
	
	return 0;
}
