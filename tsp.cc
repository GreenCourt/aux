#include<bits/stdc++.h>
using namespace std;

int main() {
  // https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_2_A
  int n,m; cin >> n >> m;
  constexpr int INF=1e9;
  vector<vector<int>> dist(n, vector<int>(n, INF));

  for(int i=0; i<m; ++i) {
    int s,t,d; cin >> s >> t >> d;
    dist[s][t] = d;
  }

  // dp[現在頂点vにいる][訪問済み頂点集合のbitset]
  vector dp(n, vector<int>(1<<n, INF));

  // 出発点には戻るのでどこから出発しても同じ。
  // なので、出発点vを0決め打ちにする。
  // TSPの亜種問題で出発点が決まっている場合は適当に変える。
  int start = 0;

  // 最後にstartにもどらないといけないのでdp[start][1<<start]でなくdp[start][0]をゼロ初期化。
  // 亜種問題で最後にスタート点に戻らなくていい場合は、dp[start][1<<start]をゼロ初期化。
  dp[start][0] = 0;

  for(int visited=0; visited<(1<<n); ++visited) {
    for(int v=0; v<n; ++v) {
      for(int u=0; u<n; ++u) if((visited & (1<<u)) == 0) {
        // v --> u の有向辺。配るDP。
        if(dist[v][u] == INF) continue;
        int ubit = 1<<u;
        dp[u][visited | ubit] = min(dp[u][visited | ubit], dp[v][visited] + dist[v][u]);
      }
    }
  }

  // TSPの亜種問題でゴールが決まっている場合は ans = dp[goal][(1<<n)-1] のようにする。
  int ans = dp[start][(1<<n)-1];
  if(ans == INF) ans = -1;
  cout << ans << '\n';
}
