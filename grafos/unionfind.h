#ifndef UNIONFIND_H
#define UNIONFIND_H

class UnionFind
{
public:
	// Crea un union find con n subconjuntos disjuntos (0 .. n-1)
	UnionFind(int n);
	~UnionFind();

	int find(int n) const;
	int cantidad_subconjuntos() const;

	void union_s(int id_s1, int id_s2);
	
private:
	int cant_subconjuntos;
	int cant_elementos;
	
	int * padre;
	int * rank;
};

#endif
