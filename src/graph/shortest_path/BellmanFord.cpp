/*
	Bellman-Ford法
	計算量O(|V||E|)
*/

#include <limits>
#include <vector>
using namespace std;

template <class T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
class BellmanFord {
  private:
    T n, e, start;
    T _INF = numeric_limits<T>::max();
    vector<pair<pair<T, T>, T>> g;
    vector<T> cost;
    bool is_negative_cycle = false;

    void init() {
        cost.resize(n, _INF);
        cost[start] = 0;
        e = g.size();
    }

  public:
    BellmanFord(T _n, vector<pair<pair<T, T>, T>> _g, T _start)
        : n(_n), g(_g), start(_start) {
        // n:長点数
        // g:グラフ(辺の配列((start,goal),cost))
        // start:始点
        init();
        for (T i = 0; i < n; i++) {
            for (T j = 0; j < e; j++) {
                if (cost[g[j].first.first] == _INF)
                    continue;
                if (chmin(cost[g[j].first.second],
                          cost[g[j].first.first] + g[j].second))
                    if (i == n - 1)
                        is_negative_cycle = true;
            }
        }
    }

    bool is_negative() {
        return is_negative_cycle;
    }

    T costs(T i) {
        return cost[i];
    }
};