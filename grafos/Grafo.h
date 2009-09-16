#ifndef GRAFO_H_
#define GRAFO_H_
#include <list>
#include "Lista.h"

using namespace std;

template <typename T, typename Z> class Par
{
public:
	Par() { }
	Par(const T & p, const Z & s)
	{
		primero = p;
		segundo = s;
	}
	Par & operator = (const Par & otroPar)
	{
		primero = otroPar.primero;
		segundo = otroPar.segundo;
		return *this;
	}
	T primero;
	Z segundo;
};

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;
	// Indica la cantidad de vértices del grafo
	int devolverLongitud() const;

	bool existeVertice(int vertice) const;

	bool existeArco(int origen, int destino) const;

	// PRE CONDICION: existeArco(origen, destino)
	const C & costoArco(int origen, int destino) const;

	void devolverVertices(Lista<int> & vertices) const;

	void devolverAdyacentes(int origen, Lista<Arco> & adyacentes) const;

	void agregarVertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminarVertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	C & costoArco(int origen, int destino);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregarArco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminarArco(int origen, int destino);

	void vaciar();

private:
	typedef Lista<Arco> ListaArc;
	typedef Lista<Par<int, ListaArc> > ListaVert;
	typedef typename ListaArc::ConstIterador ConstItArc;
	typedef typename ListaVert::ConstIterador ConstItVert;
	typedef typename ListaArc::Iterador ItArc;
	typedef typename ListaVert::Iterador ItVert;

	int cantidad_vertices;
	ListaVert vertices;
	
	ItVert _buscarVertice(int vertice);
	ConstItVert _buscarVertice(int vertice) const;
	void _eliminarArcoVertice(ListaArc & arcos, int destino);

}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{
	
}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
	vertice = adyacente;
	this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolverAdyacente() const
{
	return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolverCosto() const
{
	return costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
	cantidad_vertices = 0;
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
	
}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{

}

template <typename C> bool Grafo<C>::estaVacio() const
{
	return cantidad_vertices == 0;
}

template <typename C> int Grafo<C>::devolverLongitud() const
{
	return cantidad_vertices;
}

template <typename C> typename Grafo<C>::ItVert Grafo<C>::_buscarVertice(int vertice)
{
	ItVert it = vertices.devolverIterador();
	bool encontrado = false;
	while (!it.llegoAlFinal() && !encontrado)
	{
		int v = it.elementoActual().primero;
		if (v == vertice)
		{
			encontrado = true;
		}
		else
		{
			it.avanzar();
		}
	}
	return it;
}

template <typename C> typename Grafo<C>::ConstItVert Grafo<C>::_buscarVertice(int vertice) const
{
	ConstItVert it = vertices.devolverIterador();
	bool encontrado = false;
	while (!it.llegoAlFinal() && !encontrado)
	{
		int v = it.elementoActual().primero;
		if (v == vertice)
		{
			encontrado = true;
		}
		else
		{
			it.avanzar();
		}
	}
	return it;
}

template <typename C> bool Grafo<C>::existeVertice(int vertice) const
{
	return !(_buscarVertice(vertice).llegoAlFinal());
}

template <typename C> bool Grafo<C>::existeArco(int origen, int destino) const
{
	ConstItVert it_vert = _buscarVertice(origen);
	if (it_vert.llegoAlFinal())
	{
		return false;
	}
	else
	{
		ListaArc lista_arc = it_vert.elementoActual().segundo;
		ConstItArc it_arc = lista_arc.devolverIterador();
		bool existe = false;
		while (!it_arc.llegoAlFinal() && !existe)
		{
			existe = (it_arc.elementoActual().devolverAdyacente() == destino);
			it_arc.avanzar();
		}
		return existe;
	}
}

template <typename C> const C & Grafo<C>::costoArco(int origen, int destino) const
{
	ConstItVert it_vert = _buscarVertice(origen);
	
	ListaArc lista_arc = it_vert.elementoActual().segundo;
	ConstItArc it_arc = lista_arc.devolverIterador();
	while (!it_arc.llegoAlFinal() &&
	       it_arc->elementoActual().devolverAdyacente() != destino)
	{
		it_arc.avanzar();
	}
	return it_arc.elementoActual().devolverCosto();
}

template <typename C> void Grafo<C>::devolverVertices(Lista<int> & vertices) const
{
	vertices.vaciar();
	ConstItVert it_vert = this->vertices.devolverIterador();
	while (!it_vert.llegoAlFinal())
	{
		int v = it_vert.elementoActual().primero;
		vertices.agregarFinal(v);
		it_vert.avanzar();
	}
}

template <typename C> void Grafo<C>::devolverAdyacentes(int origen, Lista<Arco> & adyacentes) const
{
	ConstItVert it_vert = _buscarVertice(origen);
	assert(!it_vert.llegoAlFinal());

	adyacentes = it_vert.elementoActual().segundo;
}

template <typename C> void Grafo<C>::agregarVertice(int vertice)
{
	ListaArc arcos;
	vertices.agregarFinal(Par<int, ListaArc>(vertice, arcos));
	cantidad_vertices++;
}

template <typename C> void Grafo<C>::_eliminarArcoVertice(ListaArc & arcos, int destino)
{
	bool encontrado = false;
	ItArc it_arc = arcos.devolverIterador();
	while (!it_arc.llegoAlFinal() && !encontrado)
	{
		if (it_arc.elementoActual().devolverAdyacente() == destino)
		{
			encontrado = true;
		}
		else
		{
			it_arc.avanzar();
		}
	}
	if (encontrado)
	{
		arcos.eliminar(it_arc);
	}
}

template <typename C> void Grafo<C>::eliminarVertice(int vertice)
{
	ItVert it_vert = _buscarVertice(vertice);
	if (!it_vert.llegoAlFinal())
	{
		vertices.eliminar(it_vert);
		cantidad_vertices--;

		it_vert = vertices.devolverIterador();
		while (!it_vert.llegoAlFinal())
		{
			_eliminarArcoVertice(it_vert.elementoActual().segundo, vertice);
			it_vert.avanzar();
		}
	}
}

template <typename C> C & Grafo<C>::costoArco(int origen, int destino)
{

}

template <typename C> void Grafo<C>::agregarArco(int origen, int destino, const C & costo)
{
	Arco arc(destino, costo);
	ItVert it_vert = _buscarVertice(origen);
	it_vert.elementoActual().segundo.agregarFinal(arc);
}

template <typename C> void Grafo<C>::eliminarArco(int origen, int destino)
{
	ItVert it_vert = _buscarVertice(origen);
	_eliminarArcoVertice(it_vert.elementoActual().segundo, destino);
}

template <typename C> void Grafo<C>::vaciar()
{
	vertices.vaciar();
	cantidad_vertices = 0;
}

#endif /* GRAFO_H_ */
