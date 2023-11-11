template<typename T>
bool isclose(T a, T b, T rel_tol, T abs_tol) {
  assert(0.0 <= rel_tol && rel_tol < 1.0);
  assert(0.0 <= abs_tol && rel_tol < 1.0);
  if (a == b) return true;
  if (isinf(a) || isinf(b)) return false;
  double diff = abs(b - a);
  return (diff <= abs(rel_tol * b)) || (diff <= abs(rel_tol * a)) || (diff <= abs_tol);
}

template<typename T>
inline bool isclose(T a, T b, T tolerance) { return isclose(a, b, tolerance, tolerance); }
