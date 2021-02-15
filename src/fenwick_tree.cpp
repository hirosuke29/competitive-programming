/*
  Fenwick Tree (BIT木)
  区間クエリに答えられる
  セグ木より機能は少ないけど軽い
*/

#include <vector>
using namespace std;

template <class T>
class Fenwick_Tree {
  private:
    vector<int> v;
    int n;
    int e;
    void init() {
        v.resize(n, e);
    }

  public:
    Fenwick_Tree(T _n, T _e) : n(_n), e(_e) {
		//n:配列サイズ
		//e:単位元
		//実装上は1-indexedだけど0-indexedで渡す
        n++;
        init();
    }

    T one_query(int a) {
        T sum = 0;
        for (int i = a + 1; i > 0; i -= i & -i)
            sum += v[i];
        return sum;
    }
	
    T query(int i, int j) {
        T sum_i = one_query(i - 1);
        T sum_j = one_query(j);
        return sum_j - sum_i;
    }

    void update(int a, int w) {
        for (int i = a + 1; i <= n; i += i & -i) {
            v[i] += w;
        }
    }
};