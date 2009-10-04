#include "Grafo.h"
#include "Lista.h"

#include <iostream>

bool poda(bool visitado[], int v, int inicio, int visitados, int n)
{
     return visitado[v] && (visitados < n || v != inicio);
}

template<typename T>
bool ciclo_hamilton(const Grafo<T> & g, int inicio,
		    bool visitado[], int visitados, int v)
{
     if (visitados == g.devolverLongitud())
	  return true;
     
     visitados++;
     visitado[v] = true;
     Lista<typename Grafo<T>::Arco> adyacentes;
     g.devolverAdyacentes(v, adyacentes);
     typename Lista<typename Grafo<T>::Arco>::Iterador ady = adyacentes.devolverIterador();
     bool hay_ciclo =  false;
     while (!hay_ciclo && !ady.llegoAlFinal()) {
	  int u = ady.elementoActual().devolverAdyacente();
	  if (!poda(visitado, u, inicio, visitados, g.devolverLongitud()))
	       hay_ciclo = ciclo_hamilton(g, inicio, visitado, visitados, u);
	  ady.avanzar();
     }
     visitado[v] = false;
     
     return hay_ciclo;
}
     
int main(int argc, char *argv[])
{
     const int n = 3;
     enum {A, B, C};
     Grafo<int> g;
     g.agregarVertice(A);
     g.agregarVertice(B);
     g.agregarVertice(C);

     g.agregarArco(A, B, 1);
     g.agregarArco(B, C, 1);
     g.agregarArco(C, A, 1);

     bool visitado[n];
     bool hay_ciclo =  false;
     int i = 0;
     while (!hay_ciclo && i < n) {
	  for (int k = 0; k < n; k++)
	       visitado[k] = false;

	  hay_ciclo = ciclo_hamilton(g, i, visitado, 0, i);
	  i++;
     }
     if (hay_ciclo)
	  cout << "hay ciclo de hamilton" << endl;
     else
	  cout << "no hay ciclo de hamilton" << endl;
     return 0;
}
