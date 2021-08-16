#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int int64;

int64 Multiply(int64 a, int64 b, int64 mod) {
  int64 res(0);
  while (b) {
    if (b & 1) {
      res += a;
      if (res >= mod)
        res -= mod;
    }
    a <<= 1;
    if (a >= mod)
      a -= mod;
    b >>= 1;
  }
  return res;
}

int64 Powlog(int64 a, int64 b, int64 mod) {
  int64 res(1);
  while (b) {
    if (b & 1)
      res = Multiply(res, a, mod);
    a = Multiply(a, a, mod);
    b >>= 1;
  }
  return res;
}

bool is_prime(int64 n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3 || n == 5)
    return true;
  if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
    return false;
  int64 d(n - 1);
  while (d % 2 == 0)
    d >>= 1;
  for (int i = 1; i <= 2; ++i) {
    bool ch(true);
    int64 a = 2 + rand() % (n - 4), temp(d);
    int64 x = Powlog(a, temp, n);
    if (x == 1 || x == n - 1)
      continue;
    while (temp != n - 1) {
      x = Multiply(x, x, n);
      temp <<= 1;
      if (x == 1)
        return false;
      if (x == n - 1) {
        ch = false;
        break;
      }
    }
    if (ch)
      return false;
  }
  return true;
}

bool Psquare(int64 N) {
  int64 root = sqrtl(N);
  if (root * root != N)
    return false;
  return is_prime(root);
}

int solve(int64 n)  {
  if (n == 1)
    return 1;
  int ans = 1;
  for (int d : {2, 3}) {
    int e = 0;
    while (n % d == 0) {
      ++e;
      n /= d;
    }
    ans *= e + 1;
  }
  int64 d = 5;
  while (d * d * d <= n) {
    int e = 0;
    while (n % d == 0)  {
      ++e;
      n /= d;
    }
    ans *= e + 1;
    d += 2;
    if (d * d * d > n)
      break;
    e = 0;
    while (n % d == 0)  {
      ++e;
      n /= d;
    }
    ans *= e + 1;
    d += 4;
  }
  if (is_prime(n))
    ans <<= 1;
  else
    if (Psquare(n))
      ans *= 3;
  else
    if (n != 1)
      ans <<= 2;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int64 n;
  cin >> n;
  cout << solve(n) << '\n';
  return 0;
}
