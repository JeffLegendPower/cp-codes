// https://codeforces.com/contest/1521/problem/D

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
	vector<int> sizes;

  public:
	DSU(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
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

struct node {
    vector<int> next;
    bool root = false;

    int connect;
};
node graph[100000];
vector<pii> rem, add;
set<pii> rem2;
DSU dsu(10);

void dfs(int cur, int parent) {
    int children = graph[cur].next.size() - graph[cur].root;
    if (parent != -1) children--;

    vector<int> next2;
    for (int next : graph[cur].next) {
        if (next == parent) continue;
        if (graph[next].next.size() - 1 > 1 && children > 1) {
            children--;
            graph[cur].connect--;
            graph[next].connect--;

            graph[next].root = true;
            rem.push_back({cur, next});
        } else next2.push_back(next);
    } for (int next : next2) {
        if (graph[next].next.size() - 1 <= 1 && children > 1) {
            children--;
            graph[cur].connect--;
            graph[next].connect--;

            graph[next].root = true;
            rem.push_back({cur, next});
        } else {
            dsu.unite(cur, next);
        }
    }

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        dfs(next, cur);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        for (int i = 0; i < N; i++) graph[i].next.clear();
        rem.clear();
        add.clear();

        dsu = DSU(N);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;

            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        } for (int i = 0; i < N; i++) graph[i].connect = graph[i].next.size();

        graph[0].root = true;
        dfs(0, -1);

        vector<int> singles;
        for (int i = 0; i < N; i++) if (graph[i].connect <= 1) singles.push_back(i);

        int left = 0, right = 0;
        while (right < singles.size()) {
            if (dsu.connected(singles[left], singles[right])) {
                right++;
                continue;
            }
            add.push_back({singles[left], singles[right]});
            graph[singles[left]].connect++;
            graph[singles[right]].connect++;
            dsu.unite(singles[left], singles[right]);

            while (left < N && graph[singles[left]].connect == 2) left++;
            while (right < N && graph[singles[right]].connect == 2) right++;
        }

        cout << rem.size() << endl;
        for (int i = 0; i < rem.size(); i++) {
            cout << rem[i].first + 1 << " " << rem[i].second + 1 << " " << add[i].first + 1 << " " << add[i].second + 1 << endl;
        }
    }
}