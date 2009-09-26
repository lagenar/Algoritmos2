#include "unionfind.h"
#include <cassert>

UnionFind::UnionFind(int n)
{
	assert(n >= 0);
	
	cant_subconjuntos = n;
	cant_elementos = n;

	padre = new int[n];
	rank = new int[n];
	
	for (int i = 0; i < n; i++)
	{
		padre[i] = i;
		rank[i] = 0;
	}
}

UnionFind::~UnionFind()
{
	delete[] padre;
	delete[] rank;
}

int UnionFind::find(int n) const
{
	assert(n < cant_elementos);
	
	int i = n;
	// Se busca el elemento representativo del subconjunto
	while (padre[i] != i)
		i = padre[i];
	
	int raiz = i;
	i = n;
	// Se actualiza el padre de cada elemento del subconjunto
	// para que la próxima busqueda sea más rápida.
	while (i != raiz)
	{
		int sig = padre[i];
		padre[i] = raiz;		
		i = sig;
	}
	
	return raiz;
}

void UnionFind::union_s(int id_s1, int id_s2)
{
	assert(id_s1 < cant_elementos);
	assert(id_s2 < cant_elementos);

	if (id_s1 == id_s2)
		return;
	
	if (rank[id_s1] > rank[id_s2])
	{
		padre[id_s2] = id_s1;
	}
	else if (rank[id_s2] > rank[id_s1])
	{
		padre[id_s1] = id_s2;
	}
	else
	{
		rank[id_s1] += 1;
		padre[id_s2] = id_s1;
	}
	--cant_subconjuntos;
}
	
int UnionFind::cantidad_subconjuntos() const
{
	return cant_subconjuntos;
}
