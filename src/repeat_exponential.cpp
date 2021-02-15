/*
  **繰り返し自乗法**
  nのp乗のをMODで割ったあまりを返す
  計算量O(logP)
*/

template <class T>
T repeat_exponential(T n, T p, int MOD) {
    if (p == 0)
        return 1;
    else if (p % 2 == 0) {
        T res = repeat_exponential(n, p / 2, MOD);
        return res * res % MOD;
    }
    else
        return n * repeat_exponential(n, p - 1, MOD);
}