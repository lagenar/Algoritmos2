#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

enum Tnivel {MIN, MAX};

#define INFINITO INT_MAX

int backFosforos(int n, Tnivel nivel)
{
  if(n <= 3)
    return (nivel == MIN) ? -n : n;
  int sol;
  if(nivel == MIN)
    sol = INFINITO;
  else
    sol = -INFINITO;
  for(int i = 1; i <= 3; i++) {
    if(nivel == MIN)
      sol = min(sol, backFosforos(n - i, MAX));
    else
      sol = max(sol, backFosforos(n - i, MIN));
  }
  return sol;
}


int main(int argc, char *argv[])
{
  int sol = backFosforos(6, MAX);
  if(sol > 0)
    cout << "Jugador MAX gana, puntaje: " << sol << endl;
  else
    cout << "Jugador MIN gana, puntaje: " << -sol << endl;
  return 0;
}

