/*
    Warshall-Floyd法
    計算量O(|V|^3)
    負閉路検出はg[i][i]が負となるものを見つけたらよい(O(N))
*/

#include <vector>
using namespace std;

template <class T>
class WarshallFloyd {
  private:
    T n;
    T _INF;
    vector<vector<T>> g;

    void init() {
        n = g.size();
    }

  public:
    WarshallFloyd(vector<vector<T>> _g, T __INF) : g(_g), _INF(__INF) {
        // g:グラフ(隣接行列)
        //_INF:最大値(long longなら1e18やINT64_MAX / 2などにする)
        init();
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (g[i][k] == _INF || g[k][j] == _INF)
                        continue;
                    chmin(g[i][j], g[i][k] + g[k][j]);
                }
    }

    T costs(T i, T j) {
        return g[i][j];
    }
};