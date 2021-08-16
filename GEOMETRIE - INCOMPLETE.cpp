struct point {
  int x, y;
 
  void read() {
    cin >> x >> y;
  }
 
  point operator - (const point &p) const {
    return point{x - p.x, y - p.y};
  }
 
  void operator -= (const point &p) {
    x -= p.x, y -= p.y;
  }
 
  int operator * (const point &p) const {
    return x * p.y - p.x * y;
  }
 
  int crossP(const point &A, const point &B) const {
    return (A - *this) * (B - *this);
  }
 
  bool operator < (const point &A) const { /// sortez dupa unghi
    return *this * A < 0;
  }
};