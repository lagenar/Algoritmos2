/* Dados un grafo G con sus vértices rotulados con colores y dos vértices v1 y v2
   , escriba un algoritmo que encuentre un camino entre v1 y v2 tal que no pase por
   vértices rotulados con el color rojo

   -----
   Como se usa la clase grafo que no permite parametrizar los vértices se tienen
   que mantener los rótulos fuera de la clase en un arreglo.
   No hay más restricciones que la del color de los vértices del camino, por lo que
   se puede usar una modificación del dfs.
   También hay que considerar que el camino puede tener a v1 como origen y v2 destino
   ó v2 como origen y v1 destino.
*/

#include "Grafo.h"
#include "Lista.h"

#include <iostream>

using namespace std;

enum color { rojo, verde, azul, amarillo, cian };

template <typename C>
bool camino_sin_color(const Grafo<C> & grafo, int origen, int destino,
		      bool visitado[], Lista<int> & camino, const color colores[],
		      color prohibido=rojo)
{
	visitado[origen] = true;     

	if (colores[origen] == prohibido || colores[destino] == prohibido)
	{
		return false;
	}
	else
	{	    
		camino.agregarFinal(origen);
		if (origen == destino)
		{
			return true;
		}
		else
		{
			Lista<typename Grafo<C>::Arco> adyacentes ;
			grafo.devolverAdyacentes(origen, adyacentes);
			typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
			bool encontro_camino = false;

			while (!ady.llegoAlFinal() && !encontro_camino)
			{
				int w = ady.elementoActual().devolverAdyacente();
				if (!visitado[w])
				{
					encontro_camino = camino_sin_color(grafo, w, destino, visitado,
									   camino, colores, prohibido);
				}
				ady.avanzar();
			}
			if (!encontro_camino)
			{
				camino.eliminarFinal();
			}
			return encontro_camino;
		}
	}
}

void mostrar_camino(const Lista<int> & camino, const char impr[])
{
	Lista<int>::ConstIterador v = camino.devolverIterador();
	while (!v.llegoAlFinal())
	{
		cout << impr[v.elementoActual()] << "\n";
		v.avanzar();
	}
}

int main()
{
	enum {A, B, C, D};
	const color colores[] = {verde, rojo, azul, verde};
	const char impr[] = "ABCD";
	
	Grafo<int> g;
	g.agregarVertice(A);
	g.agregarVertice(B);
	g.agregarVertice(C);
	g.agregarVertice(D);

	g.agregarArco(A, B, 1);
	g.agregarArco(A, C, 1);
	g.agregarArco(B, C, 1);
	g.agregarArco(C, D, 1);
	
	bool visitado[] = {false, false, false, false };
	Lista<int> camino;

	camino_sin_color(g, A, D, visitado, camino, colores);
	mostrar_camino(camino, impr);

	return 0;
}
