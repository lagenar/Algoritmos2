#include <iostream>
#include "Grafo.h"
#include "Lista.h"
#include "unionfind.h"

using namespace std;

struct arco {
     int orig;
     int dest;
     int costo;
};

int cmp_arco(arco a1, arco a2)
{
     if (a1.costo == a2.costo)
	  return 0;
     else if (a1.costo > a2.costo)
	  return 1;
     else
	  return -1;
}

template<typename T>
int particion(int p, int q, T A[], int (*cmp) (T, T))
{
     T x = A[p];
     
     int i = p;
     int j = q + 1;
     while (i < j) {
	  do {
	       j--;
	  } while (cmp(A[j], x) > 0);
	  do {
	       i++;
	  } while (cmp(A[i], x) < 0);

	  if (i < j) {
	       T tmp = A[i];
	       A[i] = A[j];
	       A[j] = tmp;
	  }
     }
     
     T tmp = A[j];
     A[j] = x;
     A[p] = tmp;

     return j;     
}
			

// ordenamiento incremental basado en quicksort
template<typename T>
T IQS(int k, Lista<int> & pivots, T A[], int (*cmp) (T, T))
{
     if (k == pivots.devolverPrincipio()) {
	  pivots.eliminarPrincipio();
	  return A[k];
     }
     else {
	  int p = particion(k, pivots.devolverPrincipio() - 1, A, cmp);
	  pivots.agregarPrincipio(p);
	  return IQS(k, pivots, A, cmp);
     }
}

void arcos_a_arreglo(const Grafo<int> & g, arco E[])
{
     Lista<int> vertices;
     g.devolverVertices(vertices);
     Lista<int>::Iterador it_v = vertices.devolverIterador();
     int i = 0;
     while (!it_v.llegoAlFinal()) {
	  int v = it_v.elementoActual();
	  Lista<Grafo<int>::Arco> adyacentes;
	  g.devolverAdyacentes(v, adyacentes);
	  
	  Lista<Grafo<int>::Arco>::Iterador ady = adyacentes.devolverIterador();
	  while (!ady.llegoAlFinal()) {
	       arco a;
	       a.orig = v;
	       a.dest = ady.elementoActual().devolverAdyacente();
	       a.costo = ady.elementoActual().devolverCosto();	       
	       E[i] = a;
	       i++;
	       ady.avanzar();
	  }
	  it_v.avanzar();
     }
}

void kruskal(const Grafo<int> & g, Grafo<int> & g_dest)
{
     arco E[g.devolverCantArcos()];
     arcos_a_arreglo(g, E);

     UnionFind C(g.devolverLongitud());
     Lista<int> P;
     P.agregarPrincipio(g.devolverCantArcos());
     int i = 0;
     while (C.cantidad_subconjuntos() > 1) {
	  IQS(i, P, E, &cmp_arco);
	  arco a = E[i];
	  int id_orig = C.find(a.orig);
	  int id_dest = C.find(a.dest);
	  if (id_orig != id_dest) {
	       C.union_s(id_orig, id_dest);
	       g_dest.agregarArco(a.orig, a.dest, a.costo);
	  }
	  i++;
     }
}

void imprimir_grafo(const Grafo<int> & g, const char impr[])
{
     Lista<int> vertices;
     g.devolverVertices(vertices);
     Lista<int>::Iterador it_v = vertices.devolverIterador();
     while (!it_v.llegoAlFinal()) {
	  int v = it_v.elementoActual();
	  Lista<Grafo<int>::Arco> adyacentes;
	  g.devolverAdyacentes(v, adyacentes);
	  Lista<Grafo<int>::Arco>::Iterador ady = adyacentes.devolverIterador();
	  cout << impr[v] << ":";
	  while (!ady.llegoAlFinal()) {
	       Grafo<int>::Arco a = ady.elementoActual();
	       cout << "(" << impr[a.devolverAdyacente()] << ", " << a.devolverCosto() << ")";
	       ady.avanzar();
	  }
	  cout << endl;
	  it_v.avanzar();
     }
}

int main(int argc, char *argv[])
{
     enum {A, B, C};
     Grafo<int> g;
     Grafo<int> g_dest;
     g.agregarVertice(A);
     g.agregarVertice(B);
     g.agregarVertice(C);
     g_dest.agregarVertice(A);
     g_dest.agregarVertice(B);
     g_dest.agregarVertice(C);
     
     g.agregarArco(A, B, 10);
     g.agregarArco(B, C, 10);
     g.agregarArco(C, A, 5);
     
     kruskal(g, g_dest);
     imprimir_grafo(g_dest, "ABC");
     return 0;
}
