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

bool poda(int sumaParcial, int nuevo, int M)
{
  return sumaParcial + nuevo > M;
}

bool backSumaSub(list<int> restantes, list<int> solParcial, int sumaParcial, int M)
{
  if (sumaParcial == M) {
    mostrar_solucion(solParcial);
    return true;
  } else if (restantes.empty()) {
    return false;
  }
  list<int>::iterator i = restantes.begin();
  bool pode = false;
  bool sol = false;
  while (!pode && !restantes.empty()) {
    int v = restantes.front();
    restantes.pop_front();
    if (poda(sumaParcial, v, M))
      pode = true;
    else {
      solParcial.push_back(v);
      sol = backSumaSub(restantes, solParcial, sumaParcial + v, M) || sol;
      solParcial.pop_back();
    }
  }
  return sol;
}

bool sumaSub(list<int> L, int M)
{
  L.sort();
  list<int> parcial;
  return backSumaSub(L, parcial, 0, M);
}

int main(int argc, char *argv[])
{
  list<int> l;
  l.push_back(4);
  l.push_back(2);
  l.push_back(3);
  l.push_back(1);
  l.push_back(10);
  l.push_back(5);
  l.push_back(8);
  sumaSub(l, 13);
  return 0;
}

