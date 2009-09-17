#include "Grafo.h"
#include "Lista.h"
#include <iostream>

using namespace std;

template <typename C>
void sort_top(const Grafo<C> & grafo, Lista<int> & recorrido,
	      int v, bool visitado[])
{
	visitado[v] = true;

	Lista<typename Grafo<C>::Arco> adyacentes;
	grafo.devolverAdyacentes(v, adyacentes);
	typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
	while (!ady.llegoAlFinal())
	{
		int w = ady.elementoActual().devolverAdyacente();
		if (!visitado[w])
		{
			sort_top(grafo, recorrido, w, visitado);
		}
		ady.avanzar();
	}
	recorrido.agregarPrincipio(v);
}

template <typename C>
void sort_topologico(const Grafo<C> & grafo, Lista<int> & sort_t)
{
	int n = grafo.devolverLongitud();
	bool visitado[n];
	for (int i = 0; i < n; i++)
	{
		visitado[i] = false;
	}
	Lista<int> vertices;
  
	grafo.devolverVertices(vertices);
	Lista<int>::Iterador it_vert = vertices.devolverIterador();
	while (!it_vert.llegoAlFinal())
	{
		int v = it_vert.elementoActual();
		if (!visitado[v])
		{
			sort_top(grafo, sort_t, v, visitado);
		}
		it_vert.avanzar();
	}
}

template <typename C>
void mostrarRecorridoGrafo(const Grafo<C> & grafo, const Lista<int> & recorrido, const char impr[])
{
	Lista<int>::ConstIterador v = recorrido.devolverIterador();
	while (!v.llegoAlFinal())
	{
		cout << impr[v.elementoActual()] << "\n";
		v.avanzar();
	}
}

int main(int argc, char **argv) 
{
	Grafo<int> g;
	enum {C1, C2, C3, C4, C5};
	g.agregarVertice(C1);
	g.agregarVertice(C2);
	g.agregarVertice(C3);
	g.agregarVertice(C4);
	g.agregarVertice(C5);

	g.agregarArco(C1, C3, 1);
	g.agregarArco(C2, C3, 1);
	g.agregarArco(C2, C4, 1);
	g.agregarArco(C3, C5, 1);
	g.agregarArco(C4, C5, 1);	

	const char impr[] = "12345";
	Lista<int> sort_t;
	sort_topologico(g, sort_t);
	mostrarRecorridoGrafo(g, sort_t, impr);
	
	return 0;
}

