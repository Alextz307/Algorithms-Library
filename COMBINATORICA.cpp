const int mod = 1e9 + 7;
/// const int mod = 666013;
const int MAXN = 1e5;
int f[1 + MAXN], invf[1 + MAXN];
 
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
 
int Pow(int x, int n) {
  int64_t ans = 1;
  while (n) {
    if (n & 1) {
      ans = ans * x % mod;
    }
    x = (int64_t)x * x % mod;
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
  return (int64_t)f[n] * invf[k] % mod * invf[n - k] % mod;
}

void compute_factorial() {
  f[0] = f[1] = 1;
  for (int i = 2; i <= MAXN; ++i) {
    f[i] = (int64_t)f[i - 1] * i % mod;
  }
  invf[MAXN] = invers(f[MAXN]);
  for (int i = MAXN - 1; i >= 0; --i) {
    invf[i] = (int64_t)invf[i + 1] * (i + 1) % mod;
  }
}

void add_self(int &x, const int &y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub_self(int &x, const int &y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}
