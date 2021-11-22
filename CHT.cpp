struct line {
  ld start;
  int m, b;
 
  int eval(int x) {
    return m * x + b;
  }
};
 
struct CHT {
  line hull[kN];
  int l = 0, r = -1;
 
  ld findIntersection(int m1, int b1, int m2, int b2) {
    return (ld)(b2 - b1) / (m1 - m2);
  }
 
  void addLine(int m, int b) {
    while (l <= r) {
      line l = hull[r];
      if (l.m * l.start + l.b > m * l.start + b) {
        if (l.m != m) {
          hull[++r] = {findIntersection(l.m, l.b, m, b), m, b};
        }
        return;
      }
      --r;
    }
    hull[++r] = {INF, m, b};
  }
 
  int query(int x) {
    while (l + 1 <= r && hull[l].eval(x) <= hull[l + 1].eval(x)) {
      ++l;
    }
    return hull[l].eval(x);
  }
};
