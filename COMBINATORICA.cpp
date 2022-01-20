const int mod = 1e9 + 7;
const int kN = 1e5;
int f[1 + kN], invf[1 + kN];
 
/* int64_t nck(int N, int K) { Combinari in O(N)
  if (K < N - K)
    K = N - K;
  int64_t ans = 1;
  int p = 2;
  for (int i = K + 1; i <= N; ++i) {
    ans *= i;
    while (p <= N - K && ans % p ==0)
      ans /= p++;
  }
  return ans;
} */
 
void addSelf(int &x, const int &y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}
 
int add(int x, const int &y) {
  addSelf(x, y);
  return x;
}
 
void multSelf(int &x, const int &y) {
  x = (int64_t)x * y % mod;
}
 
int mult(int x, const int &y) {
  multSelf(x, y);
  return x;
}
 
int Pow(int x, int n) {
  int ans = 1;
  while (n) {
    if (n & 1) {
      multSelf(ans, x);
    }
    multSelf(x, x);
    n >>= 1;
  }
  return ans;
}
 
int invers(int x) {
  return Pow(x, mod - 2);
}
 
int nck(int n, int k) {
  if (n < k) {
    return 0;
  }
  if (n == k) {
    return 1;
  }
  return mult(f[n], mult(invf[k], invf[n - k]));
}
 
void computeFactorials(int n) {
  f[0] = f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    f[i] = mult(f[i - 1], i);
  }
  invf[n] = invers(f[n]);
  for (int i = n - 1; i >= 0; --i) {
    invf[i] = mult(invf[i + 1], i + 1);
  }
}
