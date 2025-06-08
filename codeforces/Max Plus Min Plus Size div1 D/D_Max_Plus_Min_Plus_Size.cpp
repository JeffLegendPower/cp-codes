// https://codeforces.com/problemset/problem/2018/D

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
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

  public:
    vector<int> sizes, starts;
    vector<ll> maxeven, maxodd;
    vector<ll> maxval;
	DSU(int size) : parents(size), starts(size), sizes(size, 1), maxeven(size, -1), maxodd(size, -1), maxval(size, -1) {
		for (int i = 0; i < size; i++) { 
            parents[i] = i;
            starts[i] = i;
        }
	}

	/** @return the "representative" node in x's component */
	int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;

        maxeven[x_root] = max(maxeven[x_root], maxeven[y_root]);
        maxodd[x_root] = max(maxodd[x_root], maxodd[y_root]);
        starts[x_root] = min(starts[x_root], starts[y_root]);

        ll evenmax = maxeven[x_root], oddmax = maxodd[x_root];
        if (sizes[x_root]&1) {
            evenmax -= (starts[x_root]&1);
            oddmax -= ((starts[x_root]^1)&1);
        }

        maxval[x_root] = max(evenmax, oddmax);
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

    int T2 = T;

    while (T--) {
        int N; cin >> N;

        ll a[N];
        plli idxs[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            idxs[i].first = a[i];
            idxs[i].second = i;
        }
        sort(idxs, idxs + N, [](plli one, plli two) {
            return one.first > two.first;
        });

        DSU dsu(N);

        vector<bool> incl(N, false);
        ll best = 0;

        map<ll, int> maxs;
        ll num = 0;

        for (auto [ai, idx] : idxs) {
            if (idx&1) dsu.maxodd[idx] = ai;
            else dsu.maxeven[idx] = ai;
            dsu.maxval[idx] = ai;
            incl[idx] = true;

            if (idx < N - 1 && incl[idx + 1]) {
                int pidx = dsu.find(idx + 1);

                maxs[dsu.maxval[pidx]]--;
                num -= (dsu.sizes[pidx] + 1) / 2;

                if (maxs[dsu.maxval[pidx]] == 0) maxs.erase(dsu.maxval[pidx]);
                dsu.unite(idx, idx + 1);
            } if (idx > 0 && incl[idx - 1]) {
                int pidx = dsu.find(idx - 1);

                maxs[dsu.maxval[pidx]]--;
                num -= (dsu.sizes[pidx] + 1) / 2;

                if (maxs[dsu.maxval[pidx]] == 0) maxs.erase(dsu.maxval[pidx]);
                dsu.unite(idx, idx - 1);
            }

            int pidx = dsu.find(idx);
            maxs[dsu.maxval[pidx]]++;
            num += (dsu.sizes[pidx] + 1) / 2;

            best = max(best, num + ai + maxs.rbegin()->first);
        }

        cout << best << endl;
    }
}