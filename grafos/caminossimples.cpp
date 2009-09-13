/* Ejercicio 5 de grafos:
   Escribir un algoritmo que, dado un grafo dirigido y dos
   vértices de este grafo, devuelva todos los caminos simples
   de un vertice a otro
*/

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

template <class C, class V>
void caminos_simples(const Grafo<V,C> & grafo, int origen, int destino,
		     vector<int> & descubierto, vector<int> & fin_desc, int & tiempo,
		     vector<bool> & visitado, list<list<int> > & caminos, list<int> & camino_parcial)
{
	if (!visitado[origen])
	{
		visitado[origen] = true;
		descubierto[origen] = tiempo;
		tiempo++;
	}
	camino_parcial.push_back(origen);
	if (origen == destino)
	{
		caminos.push_back(camino_parcial);
	}
	list<pair<int, C> > adyacentes;
	grafo.devolverAdyacentes(origen, adyacentes);
	typename list<pair<int, C> >::iterator ady;
	for (ady = adyacentes.begin(); ady != adyacentes.end(); ady++)
	{
		int v = ady->first;
		if (!visitado[v] || !es_arco_retroceso(origen, v, descubierto, fin_desc))
		{
			caminos_simples(grafo, v, destino, descubierto, fin_desc, tiempo,
					visitado, caminos, camino_parcial);
		}
		else if (v == destino)
		{
			camino_parcial.push_back(v);
			caminos.push_back(camino_parcial);
			camino_parcial.pop_back();
		}
	}
	if (fin_desc[origen] == NO_DESC)
	{
		fin_desc[origen] = tiempo;
		tiempo++;
	}
	camino_parcial.pop_back();		
}


template <class V, class C>
void mostrar_camino(const Grafo<V,C> & grafo, const list<int> & camino)
{
	list<int>::const_iterator v = camino.begin();
	while (v != camino.end())
	{
		cout << grafo.devolverVertice(*v) << " ";
		v++;
	}
	cout << endl;
}

template <class V, class C>
void mostrar_caminos(const Grafo<V,C> & grafo, const list<list<int> > & caminos)
{
	list<list<int> >::const_iterator it;
	for (it = caminos.begin(); it != caminos.end(); it++)
	{
		mostrar_camino(grafo, *it);
	}
}

int main(int argc, char **argv)
{
	GrafoMapa<string, int> g;
	enum {A, B, C, D, E, F, G};
	g.agregarVertice(A, "A");
	g.agregarVertice(B, "B");
	g.agregarVertice(C, "C");
	g.agregarVertice(D, "D");
	g.agregarVertice(E, "E");
	g.agregarVertice(F, "F");
	g.agregarVertice(G, "G");

	g.agregarArco(A, B, 1);
	g.agregarArco(A, C, 1);
	g.agregarArco(A, D, 1);
	g.agregarArco(B, F, 2);
	g.agregarArco(C, E, 3);	
	g.agregarArco(D, G, 4);
	g.agregarArco(E, F, 5);
	g.agregarArco(F, A, 1);

	list<int> camino_parcial;
	list<list<int> > caminos;
	int tiempo = 0;
	vector<bool> visitado(8, false);
	vector<int> descubierto(8, NO_DESC);
	vector<int> fin_desc(8, NO_DESC);
	caminos_simples(g, A, A,
			descubierto, fin_desc, tiempo,
			visitado, caminos, camino_parcial);
	mostrar_caminos(g, caminos);
	
	return 0;
}
