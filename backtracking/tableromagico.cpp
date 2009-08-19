/*
  Tablero mágico: Dado un tablero de tamaño n x n, construir un
  algoritmo que ubique(si es posible) n x n números diferentes, entre
  1 y un cierto k, de manera tal que la suma de las columnas y de las
  filas sea S
 */

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
		 int sumasParcialesCols[], bool usados[], int fila, int col,
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
    if(!usados[j]) {
      if(poda(sumasParcialesFilas, sumasParcialesCols, fila,
	      col, j, S))
	pode = true;
      else {
	int prox_col, prox_fila;
	prox_fila = (col == n - 1) ? fila + 1 : fila;
	prox_col = (col == n - 1) ? 0 : col + 1;
	usados[j] = true;
	tablero[fila][col] = j;
	sumasParcialesFilas[fila] += j;
	sumasParcialesCols[col] += j;
	sol = backTablero(tablero, sumasParcialesFilas, sumasParcialesCols, 
			  usados, prox_fila, prox_col, K, S, n);
	usados[j] = false;
	tablero[fila][col] = 0;
	sumasParcialesFilas[fila] -= j;
	sumasParcialesCols[col] -= j;
      }
    }
    j++;
  }
  return sol;
}

int main(int argc, char *argv[])
{
  int k = 20;
  bool usados[k];
  int f1[] = {0,0,0};
  int f2[] = {0,0,0};
  int f3[] = {0,0,0};
  int *tablero[] = { f1, f2, f3};
  int sumfilas[] = {0,0,0};
  int sumcols[] = {0,0,0};
  for(int i = 1; i < k; i++)
    usados[i] = false;
  backTablero(tablero, sumfilas, sumcols, usados, 0, 0, k, 20, 3);
  return 0;
}
