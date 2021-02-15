/*
　Segment Tree
*/

using namespace std;

/*
  抽象Segment Tree
*/
#include <functional>
#include <vector>

template <class T>
class SegmentTree {
    /*
    セグメント木
    - 条件
        モノイドが乗る
    - モノイド
        - 集合X上の二項演算X * X ->
    Xにおいて，結合法則が成り立ち，かつ単位元が存在するもの．
    */
  private:
    /*
    メンバ変数
    n: 元の配列のサイズよりも大きく，かつその値に最も近い2のべき乗の値
    segtree: セグメント木の二分木構造の情報を格納した配列
    ie: 単位元
    */
    int n = 1;
    vector<T> segtree;
    function<T(T, T)> operation;
    T ie;

    T _query(int a, int b, int k, int l, int r) {
        if (a >= r || b <= l)
            return ie;
        else if (a <= l && b >= r)
            return segtree[k];
        else {
            int vl = _query(a, b, 2 * k + 1, l, (l + r) / 2);
            int vr = _query(a, b, 2 * k + 2, (l + r) / 2, r);
            return operation(vl, vr);
        }
    }

  public:
    SegmentTree(vector<T> v, function<T(T, T)> _operation, T _ie)
        : operation(_operation), ie(_ie) {
        /*
        コンストラクタ O(N)
        v: セグ木を構築するもととなる0-indexedの配列
        operation: 関数　(function<T(T, T)>) 渡すときには
        auto fx = [](int x1, int x2) -> int{ return min(x1,
        x2);};のような形のものを渡す． ie: 単位元
        */
        while (v.size() > n)
            n *= 2;
        segtree.resize(2 * n - 1, ie);
        for (int i = 0; i < v.size(); i++)
            segtree[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)
            segtree[i] = operation(segtree[2 * i + 1], segtree[2 * i + 2]);
    }

    T operator[](int i) {
        /*
        ランダムアクセス O(1)
        */
        return segtree[i + n - 1];
    }

    void update(int i, T x, bool replace = true) {
        /*
        値の更新 O(log N)
        0-indexedのindexと値を指定する．
        replace:
        更新の方式．値を入れ替えるか(true)，元の値に作用をするか(false)を選ぶ．
        */
        i += n - 1;
        if (replace)
            segtree[i] = x;
        else
            segtree[i] = operation(segtree[i], x);
        while (i > 0) {
            i = (i - 1) / 2;
            segtree[i] = operation(segtree[2 * i + 1], segtree[2 * i + 2]);
        }
    }

    T query(int a, int b) {
        /*
        クエリ O(log N)
        [a,b)で指定した区間のクエリを処理する．
        */
        return _query(a, b, 0, 0, n);
    }
};

