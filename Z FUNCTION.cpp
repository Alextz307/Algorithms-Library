vector<int> z_function(const string &s) { /// z[i] - cea mai lunga subsecventa ce incepe pe pozitia i si este prefix al intregului sir
  int n = s.length();
  vector<int> z(n);
  for (int i = 0, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      l = i;
      r = i + z[i];
      ++z[i];
    }
  }
  return z;
}