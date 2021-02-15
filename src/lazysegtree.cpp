#include <functional>
#include <vector>
using namespace std;
/*
  抽象遅延伝播Segment Tree
*/

template <class T, class M>
class LazySegmentTree {
  private:
    int n = 1;
    vector<T> segtree;
    vector<T> lazy;
    function<T(T, T)> operation;
    function<M(M, M)> action_to_action;
    function<T(T, M)> action;
    function<T(T, long long n)> prop;
    T t_ie;
    M m_ie;

    void eval(int k, int len = 1) {
        if (lazy[k] == m_ie)
            return;
        if (k < n - 1) {
            lazy[2 * k + 1] = action_to_action(lazy[2 * k + 1], lazy[k]);
            lazy[2 * k + 2] = action_to_action(lazy[2 * k + 2], lazy[k]);
        }
        segtree[k] = action(segtree[k], prop(lazy[k], len));
        lazy[k] = m_ie;
    }

    void _update(int a, int b, T x, int k, int l, int r) {
        eval(k, r - l);
        if (a >= r || l >= b)
            return;
        else if (a <= l && r <= b) {
            lazy[k] = action_to_action(lazy[k], x);
            eval(k, r - l);
        }
        else {
            _update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            _update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            segtree[k] = operation(segtree[2 * k + 1], segtree[2 * k + 2]);
        }
    }

    T _query(int a, int b, int k, int l, int r) {
        eval(k, r - l);
        if (a >= r || b <= l)
            return t_ie;
        else if (a <= l && b >= r)
            return segtree[k];
        else {
            int vl = _query(a, b, 2 * k + 1, l, (l + r) / 2);
            int vr = _query(a, b, 2 * k + 2, (l + r) / 2, r);
            return operation(vl, vr);
        }
    }

  public:
    LazySegmentTree(
        vector<T> v, function<T(T, T)> _operation,
        function<M(M, M)> _action_to_action, function<T(T, M)> _action, T _t_ie,
        M _m_ie,
        function<T(T, long long)> _prop = [](T m, long long n) -> T {
            return m * 1;
        })
        : operation(_operation), action_to_action(_action_to_action),
          action(_action), t_ie(_t_ie), m_ie(_m_ie), prop(_prop) {
        /*
        _operation: セグ木に乗せるモノイドの演算
        _action_to_action: 遅延伝播用の完全二分木の伝播に使う演算
        _action:
        遅延伝播用の完全二分木からセグ木用の完全二分木に値を伝播させるときの演算
        _t_ie: セグ木に乗せるモノイド単位元
        _m_ie: 遅延伝播用のモノイドに乗せる単位元
        _prop: 区間に比例した作用素を渡すときに作用素*区間を求める演算
        */
        while (v.size() > n)
            n *= 2;
        segtree.resize(2 * n - 1, t_ie);
        lazy.resize(2 * n - 1, m_ie);
        for (int i = 0; i < v.size(); i++)
            segtree[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)
            segtree[i] = operation(segtree[2 * i + 1], segtree[2 * i + 2]);
    }

    void update(int a, int b, T x) {
        _update(a, b, x, 0, 0, n);
    }

    T query(int a, int b) {
        return _query(a, b, 0, 0, n);
    }
};