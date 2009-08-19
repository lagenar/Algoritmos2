/*
  Tablero mágico: Dado un tablero de tamaño n x n, construir un
  algoritmo que ubique(si es posible) n x n números diferentes, entre
  1 y un cierto k, de manera tal que la suma de las columnas y de las
  filas sea S
 */

/*Nota: no consideré lo de que tienen que ser diferentes los n x n
 números, después lo cambio*/
#include <iostream>

using namespace std;

void mostrar_tablero(int *tablero[], int n)
{
  for(int i = 0; i < n; i++) {
    for(int k = 0; k < n; k++)
      cout << tablero[i][k] << " ";
    cout << endl;
  }
}

bool esSolucion(int sumasParcialesFilas[], int sumasParcialesCols[],
		 int n, int S)
{
  for(int i = 0; i < n; i++)
    if(sumasParcialesFilas[i] != S || sumasParcialesCols[i] != S)
      return false;
  return true;
}

bool poda(int sumasParcialesFilas[], int sumasParcialesCols[],
	  int fila, int col, int nuevo, int S)
{
  if(sumasParcialesFilas[fila] + nuevo > S ||
     sumasParcialesCols[col] + nuevo > S) {
    return true;
  }
  return false;
}

bool backTablero(int *tablero[], int sumasParcialesFilas[],
		 int sumasParcialesCols[], int fila, int col,
		 int K, int S, int n)
{
  if(fila >= n) {
    if(esSolucion(sumasParcialesFilas, sumasParcialesCols, n, S)) {
      mostrar_tablero(tablero, n);
      return true;
    } else {
      return false;
    }
  }
  bool sol = false;
  bool pode = false;
  int j = 1;
  while(!sol && !pode && j <= K) {
    if(poda(sumasParcialesFilas, sumasParcialesCols, fila,
	    col, j, S))
      pode = true;
    else {
      int prox_col, prox_fila;
      prox_fila = (col == n - 1) ? fila + 1 : fila;
      prox_col = (col == n - 1) ? 0 : col + 1;
      tablero[fila][col] = j;
      sumasParcialesFilas[fila] += j;
      sumasParcialesCols[col] += j;
      sol = backTablero(tablero, sumasParcialesFilas, sumasParcialesCols,
			prox_fila, prox_col, K, S, n);
      tablero[fila][col] = 0;
      sumasParcialesFilas[fila] -= j;
      sumasParcialesCols[col] -= j;
    }
    j++;
  }
  return sol;
}

int main(int argc, char *argv[])
{
  int f1[] = {0,0,0};
  int f2[] = {0,0,0};
  int f3[] = {0,0,0};
  int *tablero[] = { f1, f2, f3};
  int sumfilas[] = {0,0,0};
  int sumcols[] = {0,0,0};
  backTablero(tablero, sumfilas, sumcols, 0, 0, 2, 4, 3);
  return 0;
}
