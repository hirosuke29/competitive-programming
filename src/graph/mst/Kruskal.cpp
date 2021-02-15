/*
  Kruskal法
  計算量O(|E|log|E|)
*/

#include <vector>
using namespace std;

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

template <class T>
class Kruskal {
  private:
    T v;
    T sum = 0;
    vector<pair<pair<T, T>, T>> mst_edge;
    vector<pair<pair<T, T>, T>> edge;

    static bool comp(const pair<pair<T, T>, T> &a,
                     const pair<pair<T, T>, T> &b) {
        return a.second < b.second;
    }

    void init() {
        mst_edge.resize(0);
        sort(edge.begin(), edge.end(), comp);
    }

  public:
    Kruskal(T _v, vector<pair<pair<T, T>, T>> _edge) : v(_v), edge(_edge) {
        // v:頂点数
        // edge:グラフの辺((start,goal),cost)
        init();
        UnionFind<T> uf(v);
        for (auto _edge : edge) {
            if (!uf.same(_edge.first.first, _edge.first.second)) {
                sum += _edge.second;
                uf.unite(_edge.first.first, _edge.first.second);
                mst_edge.push_back(_edge);
            }
        }
    }

    T mst_sum() {
        return sum;
    }

    vector<pair<pair<T, T>, T>> mst() {
        return mst_edge;
    }
};