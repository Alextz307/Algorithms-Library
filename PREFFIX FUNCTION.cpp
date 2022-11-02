vector<int> preffix_function(string s) { /// cel mai lung prefix care este si sufix(sirul complet este exclus)
  int n = s.length();
  vector<int> pi(n + 1);
  s = '#' + s;
  for (int i = 2, q = 0; i <= n; ++i) {
    while (q && s[q + 1] != s[i]) {
      q = pi[q];
    }
    if (s[q + 1] == s[i]) {
      ++q;
    }
    pi[i] = q;
  }
  return pi;
}
