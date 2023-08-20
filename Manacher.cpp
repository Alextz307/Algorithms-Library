const int NMAX = 1e6;
int dp[NMAX][2], l[2], r[2];
 
void Manacher() {
  string s;
  cin >> s;

  int N = s.size();
  long long ans = 0;
  r[0] = r[1] = -1;
  
  for (int i = 0; i < N; ++i)
    for (int par = 0; par < 2; ++par) {
      int flag = !par;
      int k = (i > r[par]) ? par : min(dp[l[par] + r[par] + flag - i][par], r[par] - i + 1);
      
      while (0 <= i - k - flag && i + k < N && s[i - k - flag] == s[i + k]) {
        ++k;
      }
      
      ans += k;
      dp[i][par] = k--;
      
      if (i + k > r[par]) {
        l[par] = i - k - flag, r[par] = i + k;
      }
    }
  cout << ans << '\n';
}
