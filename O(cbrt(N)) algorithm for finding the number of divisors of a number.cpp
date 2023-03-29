#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int int64;

const int kMax = 1e6;
bitset<kMax / 2> sieve;
vector<int> primes;

void precompute() {
  for (int i = 3; i * i < kMax; i += 2) {
    if (!sieve[(i - 1) / 2]) {
      for (int j = i * i; j < kMax; j += 2 * i) {
        sieve[(j - 1) / 2] = true;
      }
    }
  }

  primes.emplace_back(2);

  for (int i = 1; i < kMax / 2; ++i) {
    if (!sieve[i]) {
      primes.emplace_back(i * 2 + 1);
    }
  }
}

int64 multiply(int64 a, int64 b, int64 mod) {
  int64 res(0);

  while (b) {
    if (b & 1) {
      res += a;
      if (res >= mod) {
        res -= mod;
      }
    }

    a <<= 1;
    if (a >= mod) {
      a -= mod;
    }

    b >>= 1;
  }

  return res;
}

int64 powLog(int64 a, int64 b, int64 mod) {
  int64 res(1);

  while (b) {
    if (b & 1) {
      res = multiply(res, a, mod);
    }

    a = multiply(a, a, mod);

    b >>= 1;
  }

  return res;
}

bool isPrime(int64 n) {
  if (n < 2) {
    return false;
  }

  if (n == 2 || n == 3 || n == 5) {
    return true;
  }

  if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {
    return false;
  }

  int64 d(n - 1);
  while (d % 2 == 0) {
    d >>= 1;
  }

  for (int i = 1; i <= 2; ++i) {
    bool ch(true);

    int64 a = 2 + rand() % (n - 4), temp(d);
    int64 x = powLog(a, temp, n);

    if (x == 1 || x == n - 1) {
      continue;
    }

    while (temp != n - 1) {
      x = multiply(x, x, n);

      temp <<= 1;

      if (x == 1) {
        return false;
      }

      if (x == n - 1) {
        ch = false;
        break;
      }
    }

    if (ch) {
      return false;
    }
  }

  return true;
}

bool pSquare(int64 N) {
  int64 root = sqrtl(N);

  if (root * root != N) {
    return false;
  }

  return isPrime(root);
}

int solve(int64 n)  {
  if (n == 1) {
    return 1;
  }

  int ans = 1;

  for (const int &d : primes) {
    if ((int64_t)d * d * d > n) {
      break;
    }

    int e = 0;

    while (n % d == 0) {
      e += 1;
      n /= d;
    }

    ans *= e + 1;
  }

  if (isPrime(n)) {
    ans <<= 1;
  } else if (pSquare(n)) {
    ans *= 3;
  } else if (n != 1) {
    ans <<= 2;
  }

  return ans;
}

void testCase() {
  int64 n;
  cin >> n;

  cout << solve(n) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tests;
  cin >> tests;

  precompute();

  for (int tc = 0; tc < tests; ++tc) {
    testCase();
  }

  return 0;
}
