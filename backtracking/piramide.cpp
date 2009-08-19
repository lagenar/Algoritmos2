/* Pirámide de números: dada una pirámide de números naturales
   , partiendo desde el tope de la pirámide, econtrar el camino
   que maximice la sumatoria hasta la base. La sumatoria deberá
   realizarse considerando solamente los números sobre los que
   se apoya el número de la fila anterior
*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

enum direccion {IZQ, DER};


void mostrar_camino(const vector<vector<int> > & piramide, list<direccion> camino)
{
  if (piramide.empty())
    return;
  int col = 0;
  int fila = 0;
  list<direccion>::const_iterator i;
  for(i = camino.begin(); i != camino.end(); i++) {
    cout << piramide[fila][col] << " ";
    if (*i == IZQ) 
      fila++;
    else {
      col++;
      fila++;
    }
  }
  cout << piramide[fila][col] << endl;
}

int backPiramide(const vector<vector<int> > & piramide, list<direccion> & camino,
		 int fila, int col)
{
  if (fila >= piramide.size())
    return 0;
  else if (fila == piramide.size() - 1)
    return piramide[fila][col];
  list<direccion> cam1, cam2;
  int r1 = backPiramide(piramide, cam1, fila + 1, col);
  int r2 = backPiramide(piramide, cam2, fila + 1, col + 1);
  if (r1 > r2) {
    camino = cam1;
    camino.push_front(IZQ);
    return r1 + piramide[fila][col];
  } else {
    camino = cam2;
    camino.push_front(DER);
    return r2 + piramide[fila][col];
  }
}

int main(int argc, char *argv[])
{
  int f1[] = {9};
  int f2[] = {3, 5};
  int f3[] = {7, 2, 4};
  int f4[] = {10, 8, 11, 30};
  int f5[] = {1, 5, 40, 6, 3};
  vector<vector<int> > piramide;
  piramide.push_back(vector<int> (f1, f1 + sizeof(f1) / sizeof(int)));
  piramide.push_back(vector<int> (f2, f2 + sizeof(f2) / sizeof(int)));
  piramide.push_back(vector<int> (f3, f3 + sizeof(f3) / sizeof(int)));
  piramide.push_back(vector<int> (f4, f4 + sizeof(f4) / sizeof(int)));
  piramide.push_back(vector<int> (f5, f5 + sizeof(f5) / sizeof(int)));
  list<direccion> camino;
  cout << "suma: " << backPiramide(piramide, camino, 0, 0) << endl;
  mostrar_camino(piramide, camino);
  return 0;
}

