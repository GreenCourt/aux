// 指定した文字で文字列を分割するやつ。
vector<string> split(const string &s, char delimiter, bool keep_empty=false) {
  vector<string> r; string t;
  for(char c:s) {
    if(c==delimiter){if(!t.empty()||keep_empty) r.push_back(t); t.clear();}
    else t += c;
  }
  if (!t.empty()||keep_empty) r.push_back(t);
  return r;
}

// 指定した文字を文字列から除去するやつ
string remove_char(string &s, char c) {
  string r;
  for (const auto i: s) if(i!=c) r.push_back(i);
  return r;
}

// 回文判定
// AOJの[この問題](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0063)でverifyできる
bool is_palindrome(const string& s) {
  int l = 0, r = s.size()-1;
  while(l<r) if(s[l++] != s[r--]) return false;
  return true;
}

// 文字列の左側を指定された文字でパディングするやつ
string fill_left(const string& s, int length_after_filling, char c='0') {
  return string(length_after_filling - s.length(), c) + s;
}

// stip系
string lstrip(const string &s, char c) {
  for(int i=0; i<(int)s.size(); ++i) if(s[i] != c) return s.substr(i);
  return "";
}

string rstrip(const string &s, char c) {
  for(int i=s.size()-1; i>=0; --i) if(s[i] != c) return s.substr(0, i+1);
  return "";
}

string strip(const string &s, char c) {
  int l=s.size(), r=-1;
  for(int i=0; i<(int)s.size(); ++i) if(s[i] != c) { l=i; break;};
  for(int i=s.size()-1; i>=0; --i) if(s[i] != c) { r=i; break;};
  return l <= r ? s.substr(l, r-l+1) : "";
}
