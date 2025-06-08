// https://codeforces.com/contest/1513/problem/D

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>
// Usage: FOR(i, 0, N) {...}
#define FOR(i, start, end) for(int i = start; i < end; i++)


struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


class DSU {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
    vector<bool> checked;
	DSU(int size) : parents(size), sizes(size, 1), checked(size, false) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	/** @return the "representative" node in x's component */
	int find(int x) {
		return parents[x] == x ? x : (parents[x] = find(parents[x]));
	}

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        ll p;
        cin >> N >> p;

        ll a[N];
        map<ll, vector<int>> aidxs;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (a[i] < p) aidxs[a[i]].push_back(i);
        }

        DSU dsu(N);
        ll weight = 0;
        while (aidxs.size() > 0) {

            auto itr = aidxs.begin();
            int curIdx = itr->second.back();
            ll val = itr->first;
            itr->second.pop_back();
            if (itr->second.size() == 0) aidxs.erase(itr->first);


            if (dsu.checked[dsu.find(curIdx)]) continue;
            dsu.checked[dsu.find(curIdx)] = true;

            for (int left = curIdx - 1; left >= 0; left--) {
                if (a[left] % val != 0) break;
                weight += val;

                // a[left] should never be < a[curIdx]
                if (dsu.checked[dsu.find(left)]) {
                    dsu.unite(curIdx, left);
                    break;
                }
                dsu.unite(curIdx, left);
            } for (int right = curIdx + 1; right < N; right++) {
                if (a[right] % val != 0) break;
                weight += val;

                // a[right] should never be < a[curIdx]
                if (dsu.checked[dsu.find(right)]) {
                    dsu.unite(curIdx, right);
                    break;
                }
                dsu.unite(curIdx, right);
            }
        }

        for (int i = 0; i < N - 1; i++) {
            if (!dsu.connected(i, i + 1)) {
                dsu.unite(i, i + 1);
                weight += p;
            }
        }

        cout << weight << endl;
    }
}