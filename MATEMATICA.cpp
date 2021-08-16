#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 1;
bitset<MAXN> compus;
vector<int> prime;
int fact[MAXN], F[MAXN];

bool is_prime(int x) { /// true - prim / false - compus
  if (x == 0 || x == 1)
    return false;
  if (x == 2 || x == 3)
    return true;
  if (x % 2 == 0 || x % 3 == 0)
    return false;
  int rad = sqrt(x);
  for (int d = 5; d <= rad; d += 6)
    if (x % d == 0 || x % (d + 2) == 0)
      return false;
  return true;
}

void linear_sieve() {
  compus[0] = compus[1] = true;
  for (int i = 2; i < MAXN; ++i) {
    if (!compus[i])
      prime.emplace_back(i);
    for (size_t j = 0; j < prime.size() && i * prime[j] < MAXN; ++j) {
      compus[i * prime[j]] = true;
      if (i % prime[j] == 0)
        break;
    }
  }
}

void sieve() {
  compus[0] = compus[1] = true;
  for (int i = 4; i < MAXN; i += 2)
    compus[i] = true;
  for (int i = 3; i * i < MAXN; i += 2)
    if (!compus[i])
      for (int j = i * i; j < MAXN; j += 2 * i)
        compus[j] = true;
}

void calc_fact() { /// fact[x] - cel mai mic divizor prim al lui x
  for (int i = 2; i < MAXN; ++i)
    if (fact[i] == 0) {
      fact[i] = i;
      if (i > 1000)
        continue;
      for (int j = i * i; j < MAXN; j += i)
        if (fact[j] == 0)
          fact[j] = i;
    }
}

vector<pair<int,int>> desc_small(int x) {
  vector<pair<int,int>> a;
  while (x > 1) {
    int d = fact[x];
    a.emplace_back(d, 0);
    while (x % d == 0) {
      ++a.back().second;
      x /= d;
    }
  }
  return a;
}

vector<pair<int,int>> desc_big(int x) {
  int d = 2;
  vector<pair<int,int>> a;
  while (x > 1) {
    int e = 0;
    while (x % d == 0) {
      ++e;
      x /= d;
    }
    if (e)
      a.emplace_back(d, e);
    if (d == 2)
      d = 3;
    else d += 2;
    if (d * d > x)
      d = x;
  }
  return a;
}

int cnt_div_small(int x) {
  int ans = 1;
  while (x > 1) {
    int d = fact[x], e = 0;
    while (x % d == 0) {
      ++e;
      x /= d;
    }
    ans *= e + 1;
  }
  return ans;
}

int cnt_div_big(int x) {
  int ans = 1, d = 2;
  while (x > 1) {
    int e = 0;
    while (x % d == 0) {
      ++e;
      x /= d;
    }
    ans *= e + 1;
    if (d == 2)
      d = 3;
    else d += 2;
    if (d * d > x)
      d = x;
  }
  return ans;
}

int phi(int x) { /// Indicatorul lui Euler in O(sqrt(n))
  int ans = x, d = 2;
  while (x > 1) {
    if (x % d == 0) {
      ans = ans / d * (d - 1);
      while (x % d == 0)
        x /= d;
    }
    if (d == 2)
      d = 3;
    else d += 2;
    if (d * d > x)
      d = x;
  }
  return ans;
}

void phi_sieve() {
  for (int i = 1; i < MAXN; ++i)
    F[i] = i;
  for (int i = 2; i < MAXN; ++i)
    if (F[i] == i)
      for (int j = 1; i * j < MAXN; ++j)
         F[i * j]= F[i * j] / i * (i - 1);
}

int Pow(int x, int n) {
  int ans = 1;
  while (n) {
    if (n & 1)
      ans *= x;
    x *= x;
    n >>= 1;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  /// linear_sieve();
  /// sieve();
  /// calc_fact();
  /// phi_sieve();
  return 0;
}
