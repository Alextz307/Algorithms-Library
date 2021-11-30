struct slopeTrick {
  int64_t f0 = 0;
  multiset<int64_t> points;
 
  void addAndMin(int x) {
    f0 += x;
    points.emplace(x);
    points.emplace(x);
    points.erase(prev(points.end()));
  }
 
  int64_t getMin() {
    int64_t slope = -points.size();
    int lastX = 0;
    for (int x : points) {
      f0 += slope * (x - lastX);
      ++slope;
      lastX = x;
    }
    return f0;
  }
};
