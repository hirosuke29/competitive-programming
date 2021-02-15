/*
  Euler Tour
  グラフは隣接リスト
*/
using namespace std;
#include <vector>

class EulerTour {
  private:
    int n, index;

  public:
    vector<int> eulertour;
    vector<int> begin;
    vector<int> end;

    EulerTour(vector<vector<int>> &g, int v) : n(g.size()), index(0) {
        begin.resize(n, 0);
        end.resize(n, 0);
        create_euler_tour(g, v, -1);
    }

    void create_euler_tour(vector<vector<int>> &g, int v, int parent) {
        begin[v] = index;
        index++;
        eulertour.push_back(v);
        for (auto i : g[v]) {
            if (i != parent) {
                create_euler_tour(g, i, v);
                eulertour.push_back(v);
            }
        }
        end[v] = index;
    }
};