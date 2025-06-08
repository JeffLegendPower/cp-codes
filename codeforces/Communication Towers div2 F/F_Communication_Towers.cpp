// https://codeforces.com/contest/1814/problem/F

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
const int Nmax = 3e5;  // limit for array size
int N;  // array size
vector<pii> t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
//   for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int l, int r, pii edge) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l&1) t[l++].push_back(edge);
        if (r&1) t[--r].push_back(edge);
    }
}

// int query(int p) {
//   int res = 0;
//   for (p += N; p > 0; p >>= 1) res += t[p];
//   return res;
// }
// Segtree end

struct node {
    int l, r;
    int idx;
};

class DSU {
  public:
    vector<int> p, sz;
	// stores previous unites
	vector<pair<int &, int>> history;

	DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

	int get(int x) { return x == p[x] ? x : get(p[x]); }

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return; }
		if (sz[a] < sz[b]) { swap(a, b); }

		// save this unite operation
		history.push_back({sz[a], sz[a]});
		history.push_back({p[b], p[b]});

		p[b] = a;
		sz[a] += sz[b];
	}

	int snapshot() { return history.size(); }

	void rollback(int cnt) {
		while (cnt--) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};


int most = 0;
void segtreedfs(int i) {
    
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int M;
    cin >> N >> M;

    node vertices[N];
    for (int i = 0; i < N; i++) {
        cin >> vertices[i].l >> vertices[i].r;
        vertices[i].idx = i;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        int l = max(vertices[u].l, vertices[v].l);
        int r = min(vertices[u].r, vertices[v].r);
        modify(l, r + 1, {u, v});
    }
}