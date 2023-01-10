#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")

using namespace std;
using ld = long double;

ifstream fin("determinant.in");
ofstream fout("determinant.out");

const int kN = 10;
const ld EPS = 1e-10;
ld a[1 + kN][1 + kN];

int main() {
  int n;
  fin >> n;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      fin >> a[i][j];
    }
  }

  ld det = 1;
  for (int p = 1; p <= n; ++p) {
    int pivot = p;

    for (int i = p; i <= n; ++i) {
      if (abs(a[pivot][p]) < abs(a[i][p])) {
        pivot = i;
      }
    }

    if (abs(a[pivot][p]) < EPS) {
      det = 0;
      break;
    }

    if (p != pivot) {
      det = -det;
    }

    for (int j = p; j <= n; ++j) {
      swap(a[p][j], a[pivot][j]);
    }

    det *= a[p][p];

    for (int i = p + 1; i <= n; ++i) {
      ld f = a[i][p] / a[p][p];

      for (int j = p; j <= n; ++j) {
        a[i][j] -= f * a[p][j];
      }
    }
  }

  fout << fixed << setprecision(12) << det << '\n';

  fin.close();
  fout.close();
  return 0;
}
