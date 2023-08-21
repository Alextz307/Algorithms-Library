#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

ifstream fin("cmap.in");
ofstream fout("cmap.out");

struct point {
  int x, y;
};

int64_t sqr(int x) {
  return (int64_t)x * x;
}

int64_t dist(const point &p1, const point &p2) {
    return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}

int64_t smallest_distance(const vector<point> &points, const vector<point> &points_by_y) {
  int n = points.size();

  if (n < 2) {
    return 8e18L;
  }

  vector<point> left = vector<point>(points.begin(), points.begin() + n / 2);
  vector<point> right = vector<point>(points.begin() + n / 2, points.end());

  vector<point> left_by_y, right_by_y;

  for (const point &p : points_by_y) {
    if (make_pair(p.x, p.y) <= make_pair(left.back().x, left.back().y)) {
      left_by_y.emplace_back(p);
    }
    else {
      right_by_y.emplace_back(p);
    }
  }

  int64_t d1 = smallest_distance(left, left_by_y);
  int64_t d2 = smallest_distance(right, right_by_y);
  int64_t d = min(d1, d2);

  int middleX = left.back().x;
  vector<point> stripe;

  for (const point &p : points_by_y) {
    if (sqr(p.x - middleX) < d) {
      stripe.emplace_back(p);
    }
  }

  int m = stripe.size();

  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m && sqr(stripe[j].y - stripe[i].y) < d; ++j) {
      d = min(d, dist(stripe[i], stripe[j]));
    }
  }

  return d;
}

int main() {
  int n;
  fin >> n;

  vector<point> points(n);

  for (point &p : points) {
    fin >> p.x >> p.y;
  }

  sort(points.begin(), points.end(), [&](const point &A, const point &B) -> bool {
    return make_pair(A.x, A.y) < make_pair(B.x, B.y);
  });

  vector<point> ySorted = points;

  sort(ySorted.begin(), ySorted.end(), [&](const point &A, const point &B) -> bool {
    return A.y < B.y;
  });

  fout << fixed << setprecision(8) << sqrtl(smallest_distance(points, ySorted)) << '\n';

  fin.close();
  fout.close();
  return 0;
}
