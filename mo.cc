#include<bits/stdc++.h>
using namespace std;

struct State {
  const vector<int> &a;
  int l,r;
  long long ans;
  vector<int> count;

  State(const vector<int> &a) : a(a) {
    count = vector(int(2e5)+1, 0);
    l=0, r=0;
    count[a[0]]++;
    ans = 0;
  }

  long long nC3(long long n) { return n * (n-1) / 2 * (n-2) / 3; }

  void l_plus() { // [l,r]
    assert(l < a.size()-1);
    int x = a[l++];
    ans -= nC3(count[x]);
    count[x]--;
    ans += nC3(count[x]);
  }
  void l_minus() { // [l,r]
    assert(l > 0);
    int x = a[--l];
    ans -= nC3(count[x]);
    count[x]++;
    ans += nC3(count[x]);
  }
  void r_plus() { // [l,r]
    assert(r < a.size()-1);
    int x = a[++r];
    ans -= nC3(count[x]);
    count[x]++;
    ans += nC3(count[x]);
  }
  void r_minus() { // [l,r]
    assert(r > 0);
    int x = a[r--];
    ans -= nC3(count[x]);
    count[x]--;
    ans += nC3(count[x]);
  }

  long long mv(int L, int R) { // [L,R]
    assert(L <= R);
    while(R > r) r_plus();
    while(L < l) l_minus();
    while(R < r) r_minus();
    while(L > l) l_plus();
    return ans;
  }
};

int main() {
  // https://atcoder.jp/contests/abc293/tasks/abc293_g
  int n,q; cin >> n >> q;
  vector<int> a(n);
  for(int i=0; i<n; ++i) cin >> a[i];

  vector<pair<int,int>> lr(q);
  for(int i=0;i<q;++i) {
    int l,r; cin >> l >> r; --l, --r;
    lr[i] = {l,r};
  }

  int lr_range = n;
  int block_size = min(lr_range, int(sqrt(q)));
  vector<int> order(q);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) {
      int ablk = lr[a].first / block_size;
      int bblk = lr[b].first / block_size;
      if(ablk != bblk) return ablk < bblk;
      return ablk % 2
      ? lr[a].second > lr[b].second
      : lr[a].second < lr[b].second;
      });

  vector<long long> ans(q);
  State s(a);
  for(int i : order) {
    auto [l,r] = lr[i];
    ans[i] = s.mv(l,r);
  }

  for(int i=0; i<q; ++i) cout << ans[i] << '\n';
}
