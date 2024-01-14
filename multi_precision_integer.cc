#include<bits/stdc++.h>
using namespace std;

#include<boost/multiprecision/cpp_int.hpp>
using mpint = boost::multiprecision::cpp_int;

int main() {
  // https://atcoder.jp/contests/abc169/tasks/abc169_b
  int n; cin >> n;
  vector<long long> a(n);
  for(int i=0; i<n; ++i) {
    cin >> a[i];
    if(a[i]==0) {
      cout << "0\n";
      return 0;
    }
  }

  mpint x = 1, limit = mpint(1e18);
  for(int i=0; i<n; ++i) {
    x *= a[i];
    if(x > limit) {
      cout << "-1\n";
      return 0;
    }
  }
  cout << x << '\n';
}
