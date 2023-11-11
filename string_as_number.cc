/*
 * 文字列で表される数値の大小比較
 *
 * 例えば、二つの文字列 "123" と "87" を、数値 123 と 87 とみなして大小比較するようなやつ。
 * 文字列の長さが非常に長く、愚直に int や long long に変換できない状況を想定。
 * 文字列としての長さを比較したうえで、長さが同じであれば辞書順比較する。
 * 負の値は想定していない。
 */

#include<bits/stdc++.h>
using namespace std;

bool gt(const string &a, const string &b) { // a > b
  return (a.size() > b.size()) or (a.size()==b.size() and a>b);
}

bool lt(const string &a, const string &b) { // a < b
  return (a.size() < b.size()) or (a.size()==b.size() and a<b);
}

bool geq(const string &a, const string &b) { // a >= b
  return gt(a,b) or a==b;
}

bool leq(const string &a, const string &b) { // a <= b
  return lt(a,b) or a==b;
}

int main() {
  vector<pair<string,string>> S = {
    {"123", "222"},
    {"99", "100"},
    {"12", "12"},
    {"1000", "999"},
    {"4321", "1234"},
  };

  auto f = [](const string &a, const string &b) {
    if(gt(a,b)) return " > ";
    if(lt(a,b)) return " < ";
    return " = ";
  };

  for(auto [a,b] : S) cout << a << f(a,b) << b << endl;
}
