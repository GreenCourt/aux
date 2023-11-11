/*
 * 二次元のグリッドに対する操作
 * vector<string> のほか vector<vector<int>> とかでもいける。
 * 90度回転や、空要素のトリミングなど。
 */

template<typename T>
void show(const vector<T> &g) {
  cerr << "-------------------\n";
  if(g.empty()) return;
  int n = g.size(), m = g[0].size();
  for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) cerr << g[i][j] << " \n"[j==m-1];
}

template<typename T>
vector<T> rotate90right(const vector<T> &p) {
  if(p.empty()) return vector<T>();
  int n = p.size(), m = p[0].size();
  vector<T> q(m, T(n, 0));
  for(int i=0; i<n; ++i) for(int j=0; j<m;++j) q[j][n-1-i] = p[i][j];
  return q;
}

template<typename T>
vector<T> rotate90left(const vector<T> &p) {
  if(p.empty()) return vector<T>();
  int n = p.size(), m = p[0].size();
  vector<T> q(m, T(n, 0));
  for(int i=0; i<n; ++i) for(int j=0; j<m;++j) q[m-1-j][i] = p[i][j];
  return q;
}

template<typename T, typename U>
vector<T> trim2d(const vector<T> &p, U empty) {
  if(p.empty()) return vector<T>();
  int n = p.size(), m = p[0].size();
  int rs = -1, re = -1, cs = -1, ce = -1;
  for(int i=0,brk=0; i<n && !brk; ++i) for(int j=0; j<m; ++j) if(p[i][j] != empty) { brk=true, rs=i; break; }
  if(rs == -1) return vector<T>();
  for(int i=n-1,brk=0; i>=0 && !brk; --i) for(int j=0; j<m; ++j) if(p[i][j] != empty) { brk=true, re=i; break; }
  for(int j=0,brk=0; j<m && !brk; ++j) for(int i=rs; i<=re; ++i) if(p[i][j] != empty) { brk=true, cs=j; break; }
  for(int j=m-1,brk=0; j>=0 && !brk; --j) for(int i=rs; i<=re; ++i) if(p[i][j] != empty) { brk=1, ce=j; break; }
  assert(re != -1 && cs != -1 && ce != -1);
  vector q(re-rs+1, T(ce-cs+1,empty));
  for(int i=rs; i<=re; ++i) for(int j=cs; j<=ce; ++j) q[i-rs][j-cs] = p[i][j];
  return q;
}
