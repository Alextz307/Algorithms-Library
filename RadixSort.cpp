#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

ifstream fin("radixsort.in");
ofstream fout("radixsort.out");

#define get_byte(x) ((x >> (byte * 16)) & RADIX)

const int kN = 1e7;
const int RADIX = 65535;
const int RADIX_SIZE = 16;
int n, v[kN], temp[kN];

void countSort(int A[], int B[], int byte) {
  int counter[1 << RADIX_SIZE], index[1 << RADIX_SIZE];
  memset(counter, 0, sizeof(counter));

  for (int i = 0; i < n; ++i) {
    counter[get_byte(A[i])] += 1;
  }

  index[0] = 0;
  for (int i = 1; i < (1 << RADIX_SIZE); ++i) {
    index[i] = index[i - 1] + counter[i - 1];
  }

  for(int i = 0; i < n; ++i) {
    B[index[get_byte(A[i])]++] = A[i];
  }
}

int main () {
  int a, b, c;
  fin >> n >> a >> b >> c;

  v[0] = b % c;
  for (int i = 1; i < n; ++i) {
    v[i] = (1LL * a * v[i - 1] + b) % c;
  }
    
  countSort(v, temp, 0);
  countSort(temp, v, 1);

  for (int i = 0; i < n; i += 10) {
    fout << v[i] << ' ';
  }

  fin.close();
  fout.close();
  return 0;
}
