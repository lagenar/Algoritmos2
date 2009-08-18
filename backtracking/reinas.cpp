#include <iostream>
#include <cstdlib>

using namespace std;
#define ABS(j) (j >= 0 ? j : -j)
void mostrar_solucion(int R[], int n)
{
  for (int i = 0; i < n; i++)  {
    for (int j = 0; j < n; j++) {
      if (R[i] == j)
	cout << "X ";
      else
	cout << "- ";
    }
    cout << endl;
  }
}

bool poda(int R[], int i)
{
  int j = 0;
  while (j < i) {
    if (R[j] == R[i] || abs(i - j) == abs(R[i] - R[j])) {
      return true;
    }
    j++;
  }
  return false;
}

int backreinas(int Reinas[], int nroReina, int n)
{
  int sol = 0;
  if (nroReina == n) {
    mostrar_solucion(Reinas, n);
    return 1;
  } else {
    int col = 0;
    while (col < n && sol == 0) {
      Reinas[nroReina] = col;
      if (!poda(Reinas, nroReina))
	sol = backreinas(Reinas, nroReina + 1, n);
      col++;
    }
  }
  return sol;
}

int main(int argc, char *argv[])
{
  int Reinas[8];
  backreinas(Reinas, 0, 8);
  return 0;
}

