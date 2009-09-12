#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>

using namespace std;

/*
  La clase abstracta Grafo nos permite definir una interfaz básica, común a
  todos los grafos que utilizaremos, sin importar las estructuras que se
  utilizan internamente para implementarla.
*/

template <class V, class C> class Grafo
{
public:
	virtual bool existeVertice(int id) const = 0;
     
	// PRE CONDICION: existeVertice(id)
	virtual const V & devolverVertice(int id) const = 0;

	virtual bool existeArco(int origen, int destino) const = 0;

	// PRE CONDICION: existeArco(origen, destino)
	virtual const C & costoArco(int origen, int destino) const = 0;
    
	virtual void devolverVertices(list<int> & vertices) const = 0;

	virtual void devolverAdyacentes(int origen, list<pair<int, C> > & adyacentes) const = 0;

	// PRE CONDICION: existeVertice(id)
	virtual V & devolverVertice(int id) = 0;

	virtual void agregarVertice(int id, const V & vertice) = 0;

	virtual void eliminarVertice(int id) = 0;

	// PRE CONDICION: existeArco(origen, destino)
	virtual C & costoArco(int origen, int destino) = 0;

	virtual void agregarArco(int origen, int destino, const C & costo) = 0;

	virtual void eliminarArco(int origen, int destino) = 0;
};


#endif /* GRAFO_H_ */
