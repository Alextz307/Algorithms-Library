#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")

using namespace std;
using ld = long double;

ifstream fin("gauss.in");
ofstream fout("gauss.out");

const int kN = 300;
const ld EPS = 1e-10;
int where[1 + kN];
ld a[1 + kN][1 + kN + 1], sol[1 + kN];

int main() {
  int n, m;
  fin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m + 1; ++j) {
      fin >> a[i][j];
    }
  }

  for (int row = 1, col = 1; row <= n && col <= m; ++col) {
    int pivot = row;

    for (int i = row; i <= n; ++i) {
      if (abs(a[pivot][col]) < abs(a[i][col])) {
        pivot = i;
      }
    }

    if (abs(a[pivot][col]) < EPS) {
      continue;
    }

    where[col] = row;
    for (int j = col; j <= m + 1; ++j) {
      swap(a[row][j], a[pivot][j]);
    }

    for (int i = 1; i <= n; ++i) {
      if (i != row) {
        ld f = a[i][col] / a[row][col];

        for (int j = col; j <= m + 1; ++j) {
          a[i][j] -= f * a[row][j];
        }
      }
    }

    row += 1;
  }

  for (int j = 1; j <= m; ++j) {
    if (where[j]) {
      sol[j] = a[where[j]][m + 1] / a[where[j]][j];
    }
  }

  for (int i = 1; i <= n; ++i) {
    ld sum = 0;

    for (int j = 1; j <= m; ++j) {
      sum += sol[j] * a[i][j];
    }

    if (abs(sum - a[i][m + 1]) > EPS) {
      fout << "Imposibil\n";
      return 0;
    }
  }

  for (int j = 1; j <= m; ++j) {
    fout << fixed << setprecision(12) << sol[j] << ' ';
  }
  fout << '\n';

  fin.close();
  fout.close();
  return 0;
}
