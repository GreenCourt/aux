// 222 --> 3
template<typename T>
T number_of_digits(T x) {
  assert(x>=0);
  T n=0;
  while(x) x/=10, n++;
  return n;
}

// 12345 --> 54321
template<typename T>
T reverse_digits(T x) {
  assert(x>=0);
  T p=1, r=0;
  for(T k = x/10; k; k/=10) p*=10;
  cerr << p << endl;
  for(T k = x; k; k/=10) { r += p * (k%10); p /= 10; }
  return r;
}
