#include<bits/stdc++.h>
using namespace std;

//
// https://atcoder.jp/contests/abc297/tasks/abc297_g
//
// 山がたくさんあるゲームを解く。
//
// grundy数は山一つに対して決まる値。
// grundy==0の状態で手番が回ってきたら負け。
// grundy!=0の状態で手番が回ってきたら勝ち。
// 取れなくなったら終わり＝要素数が0のときがgrundy数0。
// ある状態aから遷移できる先のgrundy数のmexがaのgrundy数。
// 要素数に対して下からgrundyを決めていける。
//
// 山ごとにgrundy数を求めたあと、それらのxorをとって、
// xorが0の状態で手番が回ってきたら負け、xorが非zeroなら勝ち。
// 詳しくはabc297gの解説動画。
// https://www.youtube.com/watch?v=HKWpUwHdc6s&t=54s
//
// grundy数の求め方は問題ごとに異なるが、
// Nimの派生系であれば「grundy数のxorを取ればよい」というのは同じ。
// よって、grundy数の求め方が鍵。
// O(1)でgrundy数を計算することが求められることが多い。
// mexを使う方法でgrundy数を確認する実験をして、
// その結果を眺めてO(1)の式を考えるとよい。
// 実験ができているなら、O(1)で同じ値が計算できているかのassertもできる。
//

int l,r;

int grundy(int a) {
  return a % (l+r) / l;
}

void check_grundy(int a) {
  // mexを使って求めたgrundy数を配列gにいれる。
  // その後、grundy()関数とg[]を比較してassert
  vector<int> g(a+1, -1);
  g[0] = 0;

  for(int i=1; i<=a; ++i) {
    if(i<l) {
      g[i] = 0;
      continue;
    }
    vector<bool> e(a+1);
    for(int j=max(0, i-r); j<=max(0, i-l); ++j) {
      e[g[j]] = true;
    }
    int mex = 1e9;
    for(int j=0; j<=a; ++j) if(e[j] == false) { mex = j; break; }
    g[i] = mex;
  }

  for(int i=0; i<=a; ++i) {
    cerr << i << ":" << g[i] << " " << grundy(i) << endl;
    assert(grundy(i) == g[i]);
  }
}

int main() {
  int n; cin >> n >> l >> r;

  int x = 0;
  for(int i=0; i<n; ++i) {
    int a; cin >> a;
#if 0
    // grundy数の実験
    check_grundy(a);
#endif
    x ^= grundy(a);
  }
  puts(x ? "First" : "Second");
}
