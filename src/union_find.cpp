#include <vector>
using namespace std;

/*
  **Union Find木**
  <vector>が必要
  T: integer(int, long longなど)
  n個の整数に対してunion find森を生成
  parent: 親の配列 ex)par[x]はxの親
  rank: ランクの配列で、root以外は意味はない
  size_of: サイズの配列で、root以外は意味がない
  root(x): xの根を返す
  same(x, y): boolでxとyが連結かを返す
  size(x): xが含まれる木の要素数を返す
  unite(x, y): xが含まれる木とyが含まれる木を連結させる
  計算量:めちゃくちゃ速い(O(logN)より速い)
*/

template <class T>
struct UnionFind {
    vector<T> parent;
    vector<T> rank;
    vector<T> size_of;

    UnionFind(T n) : parent(n), rank(n), size_of(n) {
        for (T i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
            size_of[i] = 1;
        }
    }

    T root(T x) {
        return parent[x] == x ? x : parent[x] = root(parent[x]);
    }

    bool same(T x, T y) {
        return root(x) == root(y);
    }

    T size(T x) {
        return size_of[root(x)];
    }

    void unite(T x, T y) {
        x = root(x);
        y = root(y);
        if (x == y)
            return;
        if (rank[x] < rank[y]) {
            size_of[y] += size_of[x];
            parent[x] = y;
        }
        else {
            size_of[x] += size_of[y];
            parent[y] = x;
            if (rank[x] == rank[y])
                rank[x]++;
        }
        return;
    }
};