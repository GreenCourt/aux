#include<bits/stdc++.h>
using namespace std;

// 総和がS以下となる範囲(l,r)のうち、最も短いものは？
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_A&lang=ja

template<typename T>
int shakutori_minimum_length(vector<T> const &input, long long lower_limit) {
  /* O(n) */
  /* returns the minimum length of sequence whose sum >= lower_limit. */
  int r = 0, n = input.size(), minimum_length = n + 1;
  long long sum = 0;
  for(int l=0; l<n; ++l) { // consider [l,r)
    while(r<n && (sum  < lower_limit)) sum += input[r++];
    if(sum >= lower_limit) minimum_length = min(minimum_length, r - l);
    sum -= input[l];
  }
  return minimum_length;
}

int main() {
  int n,s; cin >> n >> s;
  vector<int> a(n);
  for(int i=0; i<n; ++i) cin >> a[i];
  int l = shakutori_minimum_length(a, s);
  cout << (l==n+1 ? 0 : l) << endl;
}
