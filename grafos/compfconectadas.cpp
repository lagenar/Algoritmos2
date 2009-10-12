#include <iostream>
#include "Grafo.h"
#include "Lista.h"

using namespace std;

template <typename C>
void traspuesta_grafo(const Grafo<C> & g, Grafo<C> & r)
{
     Lista<int> vertices;
     g.devolverVertices(vertices);
     Lista<int>::Iterador it_v = vertices.devolverIterador();
     while (!it_v.llegoAlFinal()) {
	  r.agregarVertice(it_v.elementoActual());
	  it_v.avanzar();
     }
     it_v = vertices.devolverIterador();
     while (!it_v.llegoAlFinal()) {
	  int v = it_v.elementoActual();
	  Lista<typename Grafo<C>::Arco> adyacentes;
	  g.devolverAdyacentes(v, adyacentes);
	  typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
	  while (!ady.llegoAlFinal()) {
	       r.agregarArco(ady.elementoActual().devolverAdyacente(),
			     v, ady.elementoActual().devolverCosto());
	       ady.avanzar();
	  }
	  it_v.avanzar();
     }
}
     
template <typename C>
void dfs_visit(const Grafo<C> & g, int v, bool visitado[], Lista<int> & recorrido)
{
     visitado[v] = true;
     
     Lista<typename Grafo<C>::Arco> adyacentes;
     g.devolverAdyacentes(v, adyacentes);
     typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
     while (!ady.llegoAlFinal()) {
	  int w = ady.elementoActual().devolverAdyacente();
	  if (!visitado[w])
	       dfs_visit(g, w, visitado, recorrido);
	  ady.avanzar();
     }
     
     recorrido.agregarPrincipio(v);
}

template <typename C>
void componentes_fuertes(const Grafo<C> & g, Lista<Lista<int> > & componentes)
{
     // se asume que los vertices fueron numerados de 0 a long-1
     bool visitado[g.devolverLongitud()];
     for (int i = 0; i < g.devolverLongitud(); i++)
	  visitado[i] =  false;
     
     Lista<int> vertices;
     Lista<int> recorrido;
     g.devolverVertices(vertices);
     Lista<int>::Iterador it_v = vertices.devolverIterador();
     while (!it_v.llegoAlFinal()) {
	  int v = it_v.elementoActual();
	  if (!visitado[v])
	       dfs_visit(g, v, visitado, recorrido);
	  it_v.avanzar();
     }

     Grafo<C> g_trasp;
     traspuesta_grafo(g, g_trasp);

     for (int i = 0; i < g.devolverLongitud(); i++)
	  visitado[i] =  false;
     
     it_v = recorrido.devolverIterador();
     while (!it_v.llegoAlFinal()) {
	  int v = it_v.elementoActual();
	  if (!visitado[v]) {
	       Lista<int> componente;
	       dfs_visit(g_trasp, v, visitado, componente);
	       componentes.agregarFinal(componente);
	  }
	  it_v.avanzar();
     }
}

void mostrar_componentes(Lista<Lista<int> > & componentes, const char impr[])
{
     Lista<Lista<int> >::Iterador it_comps = componentes.devolverIterador();
     while (!it_comps.llegoAlFinal()) {
	  Lista<int> vertices = it_comps.elementoActual();
	  Lista<int>::Iterador it_v = vertices.devolverIterador();
	  while (!it_v.llegoAlFinal()) {
	       cout << impr[it_v.elementoActual()] << " ";
	       it_v.avanzar();
	  }
	  it_comps.avanzar();
	  cout << endl;
     }
}

int main(int argc, char *argv[])
{
     enum {a, b, c, d, e, f, g, h};
     const int n = 8;

     Grafo<int> gr;
     for (int i = 0; i < n; i++)
	  gr.agregarVertice(i);
     
     gr.agregarArco(a, b, 1);
     gr.agregarArco(b, f, 1);
     gr.agregarArco(b, c, 1);
     gr.agregarArco(b, e, 1);
     gr.agregarArco(c, d, 1);
     gr.agregarArco(c, g, 1);
     gr.agregarArco(d, c, 1);
     gr.agregarArco(d, h, 1);
     gr.agregarArco(e, a, 1);
     gr.agregarArco(e, f, 1);
     gr.agregarArco(f, g, 1);
     gr.agregarArco(g, f, 1);
     gr.agregarArco(h, h, 1);
     
     Lista<Lista<int> > componentes;
     componentes_fuertes(gr, componentes);
     mostrar_componentes(componentes, "abcdefgh");
     return 0;
}
