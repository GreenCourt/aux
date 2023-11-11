// 蟻本pp143-145
#include<bits/stdc++.h>
using namespace std;


// Sの部分集合を列挙する。
// bit列で表される集合Sの部分集合を全て(bit列的に)降順で列挙できる。
// O(2^|S|)
void enumerate_subsets(int S = 0b10101) {
  for(int B=S; ; B = (B-1) & S) {
    cout << bitset<5>(B) << endl;;
    if(B==0) break;
  }
}


// 部分集合を全列挙し、さらにそのそれぞれの部分集合の部分集合を全列挙する
// n個の要素からなる集合 U があるとする。
// S⊆U を全列挙し、さらに各Sに対して T⊆S を全列挙したいときは O(3^n) になる。
// 一見 O(2^n * 2^n) = O(4^n) だが、U の各要素 b を考えると、
// 各 b が独立して以下の3通りの状態をとるので O(3^n) となる。
// - b は T に含まれる(すなわち S にも含まれる)。
// - b は S に含まれるが、T に含まれない。
// - b は S にも T にも含まれない
// 限界は n<=18 くらいか？
void enumerate_subsets_of_subsets(int n=3) {
  for(int S=0; S<(1<<n); S++) {
    cout << bitset<3>(S) << '\n';
    for (int T=S; ; T=(T-1)&S) {
      cout << "\t" << bitset<3>(T) << '\n';
      if (T==0) break;
    }
  }
}

// n個の要素からk個選ぶ組み合わせを全列挙
void enumerate_combinations(int n=5, int k=3) {
  for(int B=(1<<k)-1; B<(1<<n); B=(((B&~(B+(B&-B)))/(B&-B))>>1)|(B+(B&-B))) {
    cout << bitset<5>(B) << endl;
  }
}

// msb, lsbの抽出
// msb, lsbの位置(右から何番目のbitか)
// bitベースの右ローテーション、左ローテション(範囲外に行くbitが反対から現れる)
inline unsigned long long extract_msb(unsigned long long x) { return 1LL << ((x==0) ? 0 : 64 - __builtin_clzll(x)-1); }
inline unsigned long long extract_lsb(unsigned long long x) { return 1LL << (__builtin_ffsll(x)-1); }
inline int msb_position(unsigned long long x) { return (x==0) ? 0 : 64 - __builtin_clzll(x); }
inline int lsb_position(unsigned long long x) { return __builtin_ffsll(x); }
inline int bit_rotate_right(int bits, int rot, int length) { return (bits>>rot) + ((((1<<rot)-1) & bits) << (length - rot)); }
inline int bit_rotate_left(int bits, int rot, int length) { return ((bits<<rot)+(bits >> (length-rot))) & ((1<<length)-1); }

int main() {
  enumerate_subsets();
  cout << "--------\n";
  enumerate_subsets_of_subsets();
  cout << "--------\n";
  enumerate_combinations();

}
