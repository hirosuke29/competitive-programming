/*
	Dijkstra法
	計算量O((|V|+|E|log|V|))
*/

#include <limits>
#include <queue>
#include <vector>
using namespace std;

template <class T>
class Dijkstra {
  private:
    T n, c, v;
    T start;
    const T _INF = numeric_limits<T>::max();
    vector<vector<pair<T, T>>> g;
    vector<T> cost;
    vector<bool> visited;
    priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> q;

    void init() {
        q.push(make_pair(0, start));
        cost.resize(n, _INF);
        visited.resize(n, false);
        cost[start] = 0;
    }

  public:
    Dijkstra(T _n, vector<vector<pair<T, T>>> _g, T _start)
        : n(_n), start(_start), g(_g) {
        // n:ノード数
        // g:グラフ(隣接リスト) pair(node, cost)
        // start:始点
        init();
        while (!q.empty()) {
            auto top = q.top();
            q.pop();
            c = top.first;
            v = top.second;
            if (c > cost[v])
                continue;
            visited[v] = true;
            for (T i = 0; i < (T)g[v].size(); i++) {
                if (!visited[g[v][i].first]) {
                    if (chmin(cost[g[v][i].first], cost[v] + g[v][i].second)) {
                        q.push(make_pair(cost[g[v][i].first], g[v][i].first));
                    }
                }
            }
        }
    }
    T costs(T i) {
        return cost[i];
    }
};