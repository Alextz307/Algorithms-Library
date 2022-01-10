const int mod = 1e9 + 7;
int L;
int64_t p2[64];
vector<vector<vector<int>>> powers;

vector<vector<int>> mul(const vector<vector<int>> &a, const vector<vector<int>> &b) {
  int n = a.size(), m = b[0].size();
  vector<vector<int>> sol(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < (int)b.size(); ++k) {
        sol[i][j] += (int64_t)a[i][k] * b[k][j] % mod;
        if (sol[i][j] >= mod) {
          sol[i][j] -= mod;
        }
      }
    }
  }
  return sol;
}

vector<vector<int>> sqr(const vector<vector<int>> &M) {
  vector<vector<int>> sol(L, vector<int>(L));
  for (int i = 0; i < L; ++i) {
    for (int j = 0; j < L; ++j) {
      for (int k = 0; k < L; ++k) {
        sol[i][j] += (int64_t)M[i][k] * M[k][j] % mod;
        if (sol[i][j] >= mod) {
          sol[i][j] -= mod;
        }
      }
    }
  }
  return sol;
}

void powers_of_two() {
  p2[0] = 1;
  for (int i = 1; i < 64; ++i) {
    p2[i] = p2[i - 1] << 1LL;
  }
}

void precompute() {
  vector<vector<int>> M(L, vector<int>(L));
  for (int i = 0; i < L - 1; ++i) {
    M[i][i + 1] = 1;
  }
  for (int i = 0; i < L; ++i) {
    M[L - 1][i] = a[i];
  }
  powers.clear();
  powers.push_back(M);
  for (int i = 1; i < 64; ++i) {
    powers.push_back(sqr(powers.back()));
  }
}

vector<int> multiply(const vector<int> &v, const vector<vector<int>> &M) {
  vector<int> sol(L);
  for (int i = 0; i < L; ++i) {
    for (int j = 0; j < L; ++j) {
      sol[i] += (int64_t)v[j] * M[i][j] % mod;
      if (sol[i] >= mod) {
        sol[i] -= mod;
      }
    }
  }
  return sol;
}

void compute(vector<int> &v, const int64_t &expo) {
  for (int bit = 0; p2[bit] <= expo; ++bit) {
    if (expo & p2[bit]) {
      v = multiply(v, powers[bit]);
    }
  }
}
