#ifndef GRAFOMAPA_H_
#define GRAFOMAPA_H_

#include "Grafo.h"

#include "cassert"
#include "map"

using namespace std;

/*
  La clase GrafoMapa hereda de la clase abstracta Grafo, por lo que cumple con
  la interfaz general que definimos para todos los grafos que utilizaremos.
  GrafoMapa utiliza en su estructura interna el contenedor map provisto por la
  STL, por lo que provee una buena eficiencia en todas las operaciones, al
  tiempo que mantiene el caracter dinámico de la representación de las listas
  de adyacencia.
*/
/*
  Un detalle importante de la implementación es la utilización de la función
  assert de C++ (provista por el encabezado "cassert"). Esta función valida que
  la expresión pasada como parámetro sea verdadera. En el caso de que la
  expresión sea falsa, se corta la ejecución del programa y se muestra un error
  por pantalla, indicando la línea correspondiente. El assert es una opción
  simple para la implementación de pre y pos condiciones, que se utiliza para
  los casos en donde el no cumplimiento de las mismas lleva a un error grave o
  irrecuperable.
*/

template <typename V, typename C> class GrafoMapa : public Grafo<V,C>
{
public:
	GrafoMapa();
	GrafoMapa(const GrafoMapa & otro);

	virtual ~GrafoMapa();

	bool operator == (const GrafoMapa & otro) const;
	bool operator != (const GrafoMapa & otro) const;

	bool existeVertice(int id) const;

	const V & devolverVertice(int id) const;

	bool existeArco(int origen, int destino) const;

	const C & costoArco(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<pair<int, C> > & adyacentes) const;

	GrafoMapa & operator = (const GrafoMapa & otro);

	V & devolverVertice(int id);

	void agregarVertice(int id, const V & vertice);

	void eliminarVertice(int id);

 	C & costoArco(int origen, int destino);

	void agregarArco(int origen, int destino, const C & costo);

	void eliminarArco(int origen, int destino);

private:
	map<int, V> vertices;
	map<int, map<int, C> > arcos;
};


template <typename V, typename C>
GrafoMapa<V,C>::GrafoMapa()
{
}

template <typename V, typename C>
GrafoMapa<V,C>::GrafoMapa(const GrafoMapa & otro)
{
	vertices = otro.vertices;
	arcos = otro.arcos;
}

template <typename V, typename C>
GrafoMapa<V,C>::~GrafoMapa()
{
}

template <typename V, typename C>
bool GrafoMapa<V,C>::operator == (const GrafoMapa & otro) const
{
	return (vertices == otro.vertices) && (arcos == otro.arcos);
}

template <typename V, typename C>
bool GrafoMapa<V,C>::operator != (const GrafoMapa & otro) const
{
	return !(*this == otro);
}

template <typename V, typename C>
bool GrafoMapa<V,C>::existeVertice(int id) const
{
	typename map<int, V>::const_iterator vertice = vertices.find(id);
	return (vertice != vertices.end());
}

template <typename V, typename C>
const V & GrafoMapa<V,C>::devolverVertice(int id) const
{
	assert(existeVertice(id));
	return vertices.find(id)->second;
}

template <typename V, typename C>
bool GrafoMapa<V,C>::existeArco(int origen, int destino) const
{
	assert(existeVertice(origen));
	assert(existeVertice(destino));
	typename map<int, map<int, C> >::const_iterator adyMap = arcos.find(origen);
	if (adyMap != arcos.end()) {
    	typename map<int, C>::const_iterator arco = adyMap->second.find(destino);
     	return (arco != adyMap->second.end());
    }
    return false;
}

template <typename V, typename C>
const C & GrafoMapa<V,C>::costoArco(int origen, int destino) const
{
	assert(existeArco(origen, destino));
	return arcos.find(origen)->second.find(destino)->second;
}

template <typename V, typename C>
void GrafoMapa<V,C>::devolverVertices(list<int> & resultado) const
{
	resultado.clear();
	typename map<int, V>::const_iterator vertice = vertices.begin();
	while (vertice != vertices.end()) {
		resultado.push_back(vertice->first);
		vertice++;
	}
}

template <typename V, typename C>
void GrafoMapa<V,C>::devolverAdyacentes(int origen, list<pair<int, C> > & adyacentes) const
{
	assert(existeVertice(origen));
	adyacentes.clear();
	typename map<int, map<int, C> >::const_iterator adyMap = arcos.find(origen);
	if (adyMap != arcos.end()) {
		typename map<int, C>::const_iterator adyacente = adyMap->second.begin();
		while (adyacente != adyMap->second.end()) {
			adyacentes.push_back(*adyacente);
			adyacente++;
		}
	}
}

template <typename V, typename C>
GrafoMapa<V,C> & GrafoMapa<V,C>::operator = (const GrafoMapa & otro)
{
	vertices = otro.vertices;
	arcos = otro.arcos;
	return *this;
}

template <typename V, typename C>
V & GrafoMapa<V,C>::devolverVertice(int id)
{
	assert(existeVertice(id));
	return vertices[id];
}

template <typename V, typename C>
void GrafoMapa<V,C>::agregarVertice(int id, const V & vertice)
{
	vertices[id] = vertice;
}

template <typename V, typename C>
void GrafoMapa<V,C>::eliminarVertice(int id)
{
	vertices.erase(id);
	arcos.erase(id);

	typename map<int, V>::const_iterator vertice = vertices.begin();
	while (vertice != vertices.end()) {
		typename map<int, map<int, C> >::iterator adyMap = arcos.find(vertice->first);
		if (adyMap != arcos.end()) {
			adyMap->second.erase(id);
		}
		vertice++;
	}
}

template <typename V, typename C>
C & GrafoMapa<V,C>::costoArco(int origen, int destino)
{
	assert(existeArco(origen, destino));
	return arcos.find(origen)->second.find(destino)->second;
}

template <typename V, typename C>
void GrafoMapa<V,C>::agregarArco(int origen, int destino, const C & costo)
{
	arcos[origen][destino] = costo;
}

template <typename V, typename C>
void GrafoMapa<V,C>::eliminarArco(int origen, int destino)
{
	typename map<int, map<int, C> >::iterator adyMap = arcos.find(origen);
	if (adyMap != arcos.end()) {
		adyMap->second.erase(destino);
	}
}


#endif /* GRAFOMAPA_H_ */
