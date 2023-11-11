#include<bits/stdc++.h>
using namespace std;

struct modint {

};

int main() {
  // https://atcoder.jp/contests/dp/tasks/dp_s
  string k; cin >> k;
  int D; cin >> D;
  int n = k.size();

  // dp[上から何桁目まで見たか][K以下であると確定しているか][問題固有の条件]
  // 今回の問題固有の条件は[各桁の総和をDで割ったあまり]を持っておけばよい。
  vector dp(n+1, vector(2, vector<modint>(D)));
  dp[0][0][0] = 1;

  // 配るDPで計算。
  for(int i=0; i<n; ++i) {
    int ki = k[i] - '0';
    for(int less=0; less<2; ++less) {
      for(int next=0; next <= (less ? 9 : ki); ++next)  {
        for(int d=0; d < D; ++d) {
          dp[i+1][less || (next < ki)][(next + d) % D] += dp[i][less][d];
        }
      }
    }
  }

  // 0は除外しないといけないので1引いている。
  cout << dp[n][0][0] + dp[n][1][0] - 1 << endl;
}
