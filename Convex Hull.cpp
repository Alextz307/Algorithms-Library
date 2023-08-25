#include <bits/stdc++.h>
#define sz(x) static_cast<int>((x).size())
#define pd pair<double, double>
#define x first
#define y second

using namespace std;

ifstream fin("infasuratoare.in");
ofstream fout("infasuratoare.out");

const double EPS = 1e-12;

bool check(pd O, pd A, pd B) {
  return ((A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y)) < EPS;
}

int main() {
  int n;
  fin >> n;
  
  vector<pd> a(n);
  
  for (pd &x : a) {
    fin >> x.x >> x.y;
  }
  
  sort(a.begin(), a.end());
  
  vector<int> S{0, 1};
  vector<bool> viz(n);
  viz[1] = true;
  
  for (int i = 0, add = 1; i >= 0; i += (add = (i == n - 1 ? -add : add))) {
    if (viz[i]) {
      continue;
    }
    
    while (sz(S) > 1 && check(a[S[sz(S) - 2]], a[S.back()], a[i])) {
      viz[S.back()] = false;
      S.pop_back();
    }
    
    S.emplace_back(i);
    viz[i] = true;
  }
  
  fout << sz(S) - 1 << '\n' << fixed << setprecision(12);
  
  for (int i = 0; i < sz(S) - 1; ++i) {
    fout << a[S[i]].x << ' ' << a[S[i]].y << '\n';
  }
  
  fin.close();
  fout.close();
  return 0;
}
