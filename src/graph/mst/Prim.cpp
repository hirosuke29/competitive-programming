/*
  Prim法
  計算量O(|E|log|V|)
*/

#include <queue>
#include <vector>
using namespace std;

template <class T>
class Prim {
  private:
    T v;
    T sum;
    vector<bool> visited;
    vector<vector<pair<T, T>>> g;
    vector<pair<pair<T, T>, T>> mst_edge;
    priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> q;

    void init() {
        sum = 0;
        mst_edge.resize(0);
        visited.resize(v, false);
        for (T i = 0; i < g[0].size(); i++) {
            q.push(make_pair(g[0][i].second, g[0][i].first));
        }
        visited[0] = true;
    }

  public:
    Prim(T _v, vector<vector<pair<T, T>>> _g) : v(_v), g(_g) {
        // v:頂点数
        // g:グラフ(隣接リスト)
        init();
        while (!q.empty()) {
            pair<T, T> top = q.top();
            q.pop();
            T vertex = top.second;
            if (visited[vertex])
                continue;
            visited[vertex] = true;
            sum += top.first;
            for (T i = 0; i < g[vertex].size(); i++)
                q.push(make_pair(g[vertex][i].second, g[vertex][i].first));
        }
    }

    T mst_sum() {
        return sum;
    }
};