#include<bits/stdc++.h>
using namespace std;

// 総和がx以下となる範囲(l,r)は何通りあるか？
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_C

template<typename T>
long long shakutori_count(vector<T> const &input, long long upper_limit) {
  /* O(n) */
  /* returns the number of sequences whose sum <= upper_limit. */
  int r = 0, n = input.size();
  long long sum = 0, count = 0;
  for(int l=0; l<n; ++l) { // consider [l,r)
    while(r<n && (sum + input[r] <= upper_limit)) sum += input[r++];
    count += r - l;
    sum -= input[l];
  }
  return count;
}

int main() {
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for(int i=0; i<n; ++i) cin >> a[i];

  while(q--) {
    long long x; cin >> x;
    cout << shakutori_count(a, x) << endl;
  }
}
