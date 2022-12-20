/// MIN-HULL
const int kN = 1e5;
const int INF = -2e9;
 
struct line {
  ld start;
  int m, b;
 
  int64_t eval(int x) {
    return (int64_t)m * x + b;
  }
};
 
struct CHT {
  vector<line> hull;
  int l = 0, r = -1;
 
  CHT(int n) {
    hull.resize(n);
  }
 
  ld findIntersection(int m1, int b1, int m2, int b2) {
    return (ld)(b2 - b1) / (m1 - m2);
  }
 
  void addLine(int m, int b) {
    while (l <= r) {
      line l = hull[r];
      if ((int64_t)l.m * l.start + l.b < (int64_t)m * l.start + b) {
        if (l.m != m) {
          hull[++r] = {findIntersection(l.m, l.b, m, b), m, b};
        }
        return;
      }
      --r;
    }
    hull[++r] = {INF, m, b};
  }
  
  int64_t query(int x) {
    while (l + 1 <= r && hull[l + 1].eval(x) <= hull[l].eval(x)) {
      ++l;
    }
    return hull[l].eval(x);
  }
 
  /* int64_t query(int x) {
    line ln = *--upper_bound(hull.begin() + l, hull.begin() + r + 1, x, [](int y, line ll) -> bool {
      return y < ll.start;
    });
    return ln.eval(x);
  } */
};
