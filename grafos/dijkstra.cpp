#include "GrafoMapa.h"

#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

#define nil -1
#define oo INT_MAX

template<class T>
void list_a_set(const list<T> & lista, set<T> & conj)
{
	typename list<T>::const_iterator it_l;
	for (it_l = lista.begin(); it_l != lista.end(); it_l++)
	{
		conj.insert(*it_l);
	}
}

int vertice_mas_cercano(set<int> & Q, vector<int> & dist)
{
	assert(!Q.empty());
	set<int>::iterator it = Q.begin();
	int mas_cercano = *it;
	it++;
	while (it != Q.end())
	{
		if (dist[*it] < dist[mas_cercano])
		{
			mas_cercano = *it;
		}
		it++;
	}
	return mas_cercano;
}

template <typename V>
void dijkstra(const Grafo<V, int> & grafo, int origen,
	      vector<int> & dist, vector<int> & anterior)
{
	list<int> vertices;
	grafo.devolverVertices(vertices);
	list<int>::iterator it_v;
	for (it_v = vertices.begin(); it_v != vertices.end(); it_v++)
	{
		dist[*it_v] = oo;
		anterior[*it_v] = nil;
	}
	dist[origen] = 0;
	set<int> Q;
	list_a_set(vertices, Q);
	while (!Q.empty()) 
	{
		int u = vertice_mas_cercano(Q, dist);
		if (dist[u] == oo)
		{
			break;
		}		
		Q.erase(u);
		list<pair<int, int> > adyacentes;
		grafo.devolverAdyacentes(u, adyacentes);
		typename list<pair<int, int> >::iterator ady;
		for (ady = adyacentes.begin(); ady != adyacentes.end(); ady++)
		{
			int v = ady->first;
			int u_a_v = ady->second;
			int dist_por_u = dist[u] + u_a_v;
			if (dist_por_u < dist[v])
			{
				dist[v] = dist_por_u;
				anterior[v] = u;
			}
		}
		
		
	}
}

template <typename V>
void imprimir_camino_mas_corto(const Grafo<V,int> & grafo, int origen,
			       const vector<int> & dist, const vector<int> & anterior)
{
	list<int> vertices;
	grafo.devolverVertices(vertices);
	list<int>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it++)
	{
		int id = *it;
		V vert = grafo.devolverVertice(id);
		if (dist[id] == oo)
		{
			cout << "No hay camino hacia " << vert << endl;
		}
		else
		{
			list<int> camino;
			int ve = id;
			while (anterior[ve] != nil)
			{
				camino.push_front(ve);
				ve = anterior[ve];
			}
			cout << "Camino a " << vert << ": ";
			list<int>::iterator cam;
			for (cam = camino.begin(); cam != camino.end(); cam++)
			{
				V u = grafo.devolverVertice(*cam);
				cout << u << " ";
			}
			cout << endl << "Distancia: " << dist[id] << endl;
		}
	}
}


int main(int argc, char **argv)
{
	GrafoMapa<string, int> g;

	g.agregarVertice(1, "1");
	g.agregarVertice(2, "2");
	g.agregarVertice(3, "3");
	g.agregarVertice(4, "4");
	g.agregarVertice(5, "5");
	g.agregarVertice(6, "6");

	g.agregarArco(1, 2, 7);
	g.agregarArco(2, 1, 7);
	g.agregarArco(2, 3, 10);
	g.agregarArco(3, 2, 10);
	g.agregarArco(1, 3, 9);
	g.agregarArco(3, 1, 9);	
	g.agregarArco(1, 6, 14);
	g.agregarArco(6, 1, 14);
	g.agregarArco(2, 4, 15);
	g.agregarArco(4, 2, 15);
	g.agregarArco(3, 4, 11);
	g.agregarArco(4, 3, 11);
	g.agregarArco(3, 6, 2);
	g.agregarArco(6, 3, 2);
	g.agregarArco(4, 5, 6);
	g.agregarArco(5, 4, 6);
	g.agregarArco(5, 6, 9);
	g.agregarArco(6, 5, 9);

	vector<int> dist(7);
	vector<int> anterior(7);
  
	dijkstra<string>(g, 1, dist, anterior);
	imprimir_camino_mas_corto<string>(g, 1, dist, anterior);
	return 0;
}
