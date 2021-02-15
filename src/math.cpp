/*
  初等整数論
*/

/*
  **素数判定**
  整数nが素数であるかtrue/falseで判定する
  計算量O(√n)
*/

template <class T>
bool is_prime(T n) {
    if (n == 1)
        return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

/*
  **素因数分解**
  整数nを素因数分解してmapで返す
  mapの中身は(素数,指数)
  計算量O(√n)
*/

#include <map>
using namespace std;

template <class T>
map<T, T> prime_factorize(T n) {
    map<T, T> res;
    for (T i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            res[i]++;
            n /= i;
        }
    }
    if (n != 1)
        res[n] = 1;
    return res;
}

/*
  **約数列挙**
  計算量O(√N)
*/

#include <vector>

template <class T>
vector<T> divisor(T n) {
    vector<T> r;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            r.push_back(i);
            if (i * i != n)
                r.push_back(n / i);
        }
    }
    sort(r.begin(), r.end());
    return r;
}

/*
  **組み合わせを素数でわったものを求める(背景原理まだ理解してない)**
  vectorはvector<INTEGER> vec(0)の形で宣言してから渡す
  MAXは最大の階乗の数
  Mは素数
*/

template <class T>
void MODinit(T MAX, T M, vector<T> &fac, vector<T> &finv) {
    // fac,finvは空配列でok
    fac.resize(2, 1);
    finv.resize(2, 1);
    vector<T> inv(2, 1);
    for (T i = 2; i < MAX; i++) {
        fac.push_back(fac[i - 1] * i % M);
        inv.push_back(M - inv[M % i] * (M / i) % M);
        finv.push_back(finv[i - 1] * inv[i] % M);
    }
}

template <class T>
T com(T n, T k, vector<T> &fac, vector<T> &finv, T M) {
    // nCk
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * (finv[k] * finv[n - k] % M) % M;
}