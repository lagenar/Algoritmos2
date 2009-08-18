/* dado un conjunto de n enteros se desea encontrar
   , si existe, una partición en dos subconjuntos disjuntos
   , tal que la suma de sus elementos sea la misma
*/

#include <iostream>
#include <list>

using namespace std;

int sumaLista(list<int> L)
{
  list<int>::const_iterator i;
  int suma = 0;
  for(i = L.begin(); i != L.end(); i++)
    suma += *(i);
  return suma;
}

void mostrar_solucion(list<int> L)
{
  list<int>::const_iterator i = L.begin();
  cout << "{";
  while(i != L.end()) {
    cout << (*i);
    i++;
    if (i != L.end())
      cout << ", ";
  }
  cout << "}" << endl;
}

bool poda(int sumaPart1, int sumaPart2, int paso)
{
  return sumaPart1 + paso > sumaPart2 + paso;
}

bool backSumaPart(list<int> part1, list<int> part2,
		  int sumaPart1, int sumaPart2)
{
  if(part2.empty())
    return false;
  else if (sumaPart1 == sumaPart2) {
    mostrar_solucion(part1); mostrar_solucion(part2);
    return true;
  }
  bool sol = false;
  bool pode = false;
  list<int>::iterator i = part2.begin();
  while(!sol && !pode && i != part2.end()) {
    list<int>::iterator tmp_it = i;
    int v = (*i);
    tmp_it++;
    part2.erase(i);
    part1.push_back(v);
    if (poda(sumaPart1, sumaPart2, v))
      pode = true;
    else 
      sol = backSumaPart(part1, part2, sumaPart1 + v, sumaPart2 - v);
    part1.pop_back();
    part2.insert(tmp_it, v);
    i = tmp_it;
  }
  return sol;
}

bool sumaPart(list<int> L)
{
  L.sort();
  list<int> p1;
  return backSumaPart(p1, L, 0, sumaLista(L));
}

int main(int argc, char *argv[])
{
  list<int> l;
  l.push_back(4);
  l.push_back(2);
  l.push_back(16);
  l.push_back(7);
  l.push_back(17);
  sumaPart(l);
  return 0;
}

