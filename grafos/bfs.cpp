#include "Grafo.h"
#include "Lista.h"

#include <iostream>
#include <set>
#include <string>

using namespace std;

template <typename C>
void bfs(const Grafo<C> & grafo, Lista<int> & recorrido)
{
	recorrido.vaciar();
	
	Lista<int> vertices;
 	grafo.devolverVertices(vertices);
	if (!vertices.estaVacia())
	{
		Lista<int> abiertos;
		set<int> cerrados;
		abiertos.agregarFinal(vertices.devolverPrincipio());
		while (!abiertos.estaVacia())
		{
			int actual = abiertos.devolverPrincipio();
			abiertos.eliminarPrincipio();
			if (cerrados.find(actual) == cerrados.end())
			{
				recorrido.agregarFinal(actual);
				cerrados.insert(actual);
				Lista<typename Grafo<C>::Arco> adyacentes;
				grafo.devolverAdyacentes(actual, adyacentes);
				typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
				while (!ady.llegoAlFinal())
				{
					abiertos.agregarFinal(ady.elementoActual().devolverAdyacente());
					ady.avanzar();
				}
			}
		}
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
	g.agregarArco(D, G, 1);
	g.agregarArco(E, F, 1);

	Lista<int> recorrido;
	const char impr[] = "ABCDEFG";
	bfs(g, recorrido);
	mostrarRecorridoGrafo(g, recorrido, impr);
	
	return 0;
}
