#ifndef LISTA_H_
#define LISTA_H_
#include <cassert>
#include <iostream>

using namespace std;

template <typename Elem> class Lista
{
private:
	class Nodo
	{
	public:
		Nodo(const Elem & elem, Nodo * ant, Nodo * sig);
	public:
		Elem elemento;
		Nodo * siguiente;
		Nodo * anterior;
	}; // class Nodo

public:
	// La clase Iterador permite rrecorrer los elementos de la lista.
	// A través del método "elementoActual" no solo es posible acceder a los valores,
	// si no también modificarlos (porque son devueltos como referencias).
	class Iterador
	{
		// La clase Lista es friend para poder crear instancias de la clase Iterador y acceder al cursor
		friend class Lista;
	public:
		// PRE CONDICION: !llegoAlFinal()
		Elem & elementoActual();
		// PRE CONDICION: !llegoAlFinal()
		void avanzar();
		bool llegoAlFinal() const;
	private:
		Iterador(Nodo * inicio);
	private:
		Nodo * cursor;
	}; // class Iterador

	// La clase ConstIterador permite rrecorrer los elementos de la lista.
	// A diferencia de la clase Iterador no permite modificar el valor de los elementos
	// solo leerlos (porque los valores son devueltos como referencias constantes).
	class ConstIterador
	{
		// La clase Lista es friend para poder crear instancias de la clase Iterador y acceder al cursor
		friend class Lista;
	public:
		// PRE CONDICION: !llegoAlFinal()
		const Elem & elementoActual() const;
		// PRE CONDICION: !llegoAlFinal()
		void avanzar();
		bool llegoAlFinal() const;
	private:
		ConstIterador(Nodo * inicio);
	private:
		Nodo * cursor;
	}; // class Iterador

public:
	Lista();
	Lista(const Lista & otraLista);

	~Lista();

	Lista & operator = (const Lista & otraLista);

	// Devuelve true si la cantidad de elementos es cero
	bool estaVacia() const;
	// Indica la cantidad de elementos de la lista
	int devolverLongitud() const;

	// Si no se encuentra el elemento devuelve un iterador al final (llegoAlFinal() debe devolver true siempre)
	ConstIterador buscar(const Elem & elem) const;
	Iterador buscar(const Elem & elem);


	void agregarPrincipio(const Elem & elem);
	void agregarFinal(const Elem & elem);

	// PRE CONDICION: !estaVacia() && (devolverLongitud() > 0)
	const Elem & devolverPrincipio() const;
	const Elem & devolverFinal() const;

	// PRE CONDICION: !estaVacia() && (devolverLongitud() > 0)
	Elem & devolverPrincipio();
	Elem & devolverFinal();

	void eliminarPrincipio();
	void eliminarFinal();

	void eliminar(const Iterador & pos);

	// Inserta a elem antes de la posición indicada por pos
	void insertar(const Iterador & pos, const Elem & elem);

	// Devuelve un iterador que permite recorrer la lista del principio al final
	ConstIterador devolverIterador() const;
	Iterador devolverIterador();

	void vaciar();

private:
	Nodo * inicio;
	Nodo * final;
	int longitud;
}; // class Lista


/*
 * Nodo
 */

template <typename Elem> Lista<Elem>::Nodo::Nodo(const Elem & elem, Nodo * ant, Nodo * sig)
{
	elemento = elem;
	anterior = ant;
	siguiente = sig;
}


/*
 * Iterador
 */

template <typename Elem> Lista<Elem>::Iterador::Iterador(Nodo * inicio)
{
	cursor = inicio;
}

template <typename Elem> Elem & Lista<Elem>::Iterador::elementoActual()
{
	return cursor->elemento;
}

template <typename Elem> void Lista<Elem>::Iterador::avanzar()
{
	cursor = cursor->siguiente;
}

template <typename Elem> bool Lista<Elem>::Iterador::llegoAlFinal() const
{
	return cursor == 0;
}


/*
 * ConstIterador
 */

template <typename Elem> Lista<Elem>::ConstIterador::ConstIterador(Nodo * inicio)
{
	cursor = inicio;
}

template <typename Elem> const Elem & Lista<Elem>::ConstIterador::elementoActual() const
{
	return cursor->elemento;
}

template <typename Elem> void Lista<Elem>::ConstIterador::avanzar()
{
	cursor = cursor->siguiente;
}

template <typename Elem> bool Lista<Elem>::ConstIterador::llegoAlFinal() const
{
	return cursor == 0;
}

/*
 * Lista
 */

template <typename Elem> Lista<Elem>::Lista()
{
	inicio = final = 0;
	longitud = 0;
}

template <typename Elem> Lista<Elem>::Lista(const Lista & otraLista)
{
	ConstIterador it = otraLista.devolverIterador();
	while (!it.llegoAlFinal())
	{
		agregarFinal(it.elementoActual());
		it.avanzar();
	}
}

template <typename Elem> Lista<Elem>::~Lista()
{
	vaciar();
}

template <typename Elem> Lista<Elem> & Lista<Elem>::operator = (const Lista & otraLista)
{
	ConstIterador it = otraLista.devolverIterador();
	while (!it.llegoAlFinal())
	{
		agregarFinal(it.elementoActual());
		it.avanzar();
	}
	return *this;
}

template <typename Elem> bool Lista<Elem>::estaVacia() const
{
	return longitud == 0;
}

template <typename Elem> int Lista<Elem>::devolverLongitud() const
{
	return longitud;
}

template <typename Elem> typename Lista<Elem>::ConstIterador Lista<Elem>::buscar(const Elem & elem) const
{
	Nodo * cursor = inicio;
	bool encontrado = false;
	while (!encontrado && (cursor != 0))
	{
		if (cursor->elemento == elem)
		{
			encontrado = true;
		}
		else
		{
			cursor = cursor->siguiente;
		}
	}
	return ConstIterador(cursor);
}

template <typename Elem> typename Lista<Elem>::Iterador Lista<Elem>::buscar(const Elem & elem)
{
	Nodo * cursor = inicio;
	bool encontrado = false;
	while (!encontrado && (cursor != 0))
	{
		if (cursor->elemento == elem)
		{
			encontrado = true;
		}
		else
		{
			cursor = cursor->siguiente;
		}
	}
	return Iterador(cursor);
}

template <typename Elem> void Lista<Elem>::agregarPrincipio(const Elem & elem)
{
	Nodo * nuevo = new Nodo(elem, 0, inicio);
	if (longitud == 0)
	{
		final = nuevo;
	}
	else
	{
		inicio->anterior = nuevo;
	}
	inicio = nuevo;
	longitud++;
}

template <typename Elem> void Lista<Elem>::agregarFinal(const Elem & elem)
{
	Nodo * nuevo = new Nodo(elem, final, 0);
	if (longitud == 0)
	{
		inicio = nuevo;
	}
	else
	{
		final->siguiente = nuevo;
	}
	final = nuevo;
	longitud++;
}

template <typename Elem> const Elem & Lista<Elem>::devolverPrincipio() const
{
	assert(!estaVacia());
	return inicio->elemento;
}

template <typename Elem> const Elem & Lista<Elem>::devolverFinal() const
{
	assert(!estaVacia());
	return final->elemento;
}

template <typename Elem> Elem & Lista<Elem>::devolverPrincipio()
{
	assert(!estaVacia());
	return inicio->elemento;
}

template <typename Elem> Elem & Lista<Elem>::devolverFinal()
{
	assert(!estaVacia());
	return final->elemento;
}

template <typename Elem> void Lista<Elem>::eliminarPrincipio()
{
	assert(!estaVacia());
	if (longitud == 1)
		final = 0;
	Nodo * tmp = inicio;
	inicio = inicio->siguiente;
	delete tmp;
	longitud--;
}

template <typename Elem> void Lista<Elem>::eliminarFinal()
{
	assert(!estaVacia());
	if (longitud == 1)
		inicio = 0;
	Nodo * tmp = final;
	final = final->anterior;
	delete tmp;
	longitud--;
}

template <typename Elem> void Lista<Elem>::eliminar(const Iterador & pos)
{
	Nodo * cursor = pos.cursor;
	if (cursor != 0)
	{
		Nodo * ant = cursor->anterior;
		Nodo * sig = cursor->siguiente;
		if (ant != 0)
		{
			ant->siguiente = sig;
		}
		else
		{
			inicio = sig;
		}
		if (sig != 0)
		{
			sig->anterior = ant;
		}
		else
		{
			final = ant;
		}
		delete cursor;

		longitud--;
	}
}

template <typename Elem> void Lista<Elem>::insertar(const Iterador & pos, const Elem & elem)
{
	Nodo * cursor = pos.cursor;
	if (cursor != 0)
	{
		Nodo * ant = cursor->anterior;
		Nodo * nuevo = new Nodo(elem, ant, cursor);
		if (ant != 0)
		{
			ant->siguiente = nuevo;
		}
		else
		{
			inicio = nuevo;
		}
		cursor->anterior = nuevo;

		longitud++;
	}
}

template <typename Elem> typename Lista<Elem>::ConstIterador Lista<Elem>::devolverIterador() const
{
	return ConstIterador(inicio);
}


template <typename Elem> typename Lista<Elem>::Iterador Lista<Elem>::devolverIterador()
{
	return Iterador(inicio);
}

template <typename Elem> void Lista<Elem>::vaciar()
{
	while (!estaVacia())
	{
		eliminarPrincipio();
	}
}


#endif /* LISTA_H_ */
