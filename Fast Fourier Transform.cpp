using ld = long double;
using cd = complex<ld>;

const ld PI = acos(-1);
const int kN = 1 << 16;
int p[kN];

void fft(vector<cd> &aux, const bool &inv) {
  int n = aux.size();
  vector<cd> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = aux[p[i]];
  }
  for (int level = 2; level <= n; level *= 2) {
    ld ang = 2 * PI / level;
    if (inv) {
      ang *= -1;
    }
    cd w(cos(ang), sin(ang));
    for (int i = 0; i < n; i += level) {
      cd pw(1);
      for (int j = 0; j < level / 2; ++j) {
        cd u = a[i + j], v = a[i + j + level / 2] * pw;
        a[i + j] = u + v;
        a[i + j + level / 2] = u - v;
        pw *= w;
      }
    }
  }
  if (inv) {
    for (cd &x : a) {
      x /= n;
    }
  }
  aux = a;
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < (int)a.size() + (int)b.size()) {
    n *= 2;
  }
  fa.resize(n);
  fb.resize(n);
  for (int i = 0; i < n; ++i) {
    p[i] = i;
  }
  int lg = 0;
  while ((1 << lg) < n) {
    lg += 1;
  }
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n / 2;
    while (j & bit) {
      j ^= bit;
      bit /= 2;
    }
    j ^= bit;
    if (i < j) {
      swap(p[i], p[j]);
    }
  }
  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; ++i) {
    fa[i] *= fb[i];
  }
  fft(fa, true);
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    c[i] = round(fa[i].real());
  }
  return c;
}
