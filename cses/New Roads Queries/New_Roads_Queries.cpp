// https://cses.fi/problemset/task/2101/

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
    vector<int> idxs;
	DSU(int size) : parents(size), sizes(size, 1), idxs(size) {
		for (int i = 0; i < size; i++) {
            parents[i] = i;
            idxs[i] = i;
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
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

struct qry {
    int a, b;
    int day = -1;
    int idx;
};

vector<set<int>> components;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;


    for (int i = 0; i < N; i++) {
        components.push_back({i});
    }

    vector<pii> edges;
    for (int i = 0; i < M; i++) {
        pii cur;
        cin >> cur.first >> cur.second;
        cur.first--;
        cur.second--;
        edges.push_back(cur);
    }

    vector<qry> queries;
    vector<pii> qidx[N];
    for (int i = 0; i < Q; i++) {
        qry cur;
        cin >> cur.a >> cur.b;
        cur.a--, cur.b--;
        cur.idx = i;
        queries.push_back(cur);

        qidx[cur.a].push_back({i, cur.b});
        qidx[cur.b].push_back({i, cur.a});
    }

    int day = 0;
    DSU dsu(N);
    for (pii edge : edges) {
        day++;
        // if (day > 2) break;
        int u = edge.first, v = edge.second;
        if (dsu.connected(u, v)) continue;

        int pu = dsu.find(u);
        int pv = dsu.find(v);

        if (components[pu].size() < components[pv].size()) {
            swap(pu, pv);
            swap(u, v);
        }

        // if (day == 51) cout << dsu.connected(u, 71) << " " << dsu.connected(v, 71) << " " << dsu.connected(u, 63) << " " << dsu.connected(v, 63) << endl;
        // if (day == 51) cout << (components[pu].find(71) != components[pu].end()) << " " << (components[pv].find(71) != components[pv].end()) << " " << (components[pu].find(63) != components[pu].end()) << " " << (components[pv].find(63) != components[pv].end()) << endl;

        for (auto itr = components[pv].begin(); itr != components[pv].end(); itr++) {
            int ver = *itr;
            // if (day == 51 && (ver == 71 || ver == 63)) cout << ver << endl;
            for (pii qi : qidx[ver]) {
                // if (day == 51 && ver == 71) cout << qi.second << endl;
                if (components[pu].find(qi.second) != components[pu].end()) {
                    // if (day == 51 && ver == 71) cout << "E" << endl;
                    queries[qi.first].day = day;
                }
            }
        } for (auto itr = components[pv].begin(); itr != components[pv].end(); itr++) {
            int ver = *itr;
            components[pu].insert(ver);
        }

        dsu.unite(u, v);
    }

    for (qry cur : queries) cout << cur.day << endl;
}