// https://usaco.org/index.php?page=viewproblem2&cpid=1331&lang=en

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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
    vector<int> main;

  public:
	DSU(int size) : parents(size), sizes(size, 1), main(size) {
		for (int i = 0; i < size; i++) { 
            parents[i] = i;
            main[i] = i;
        }
	}

	/** @return the "representative" node in x's component */
	int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }

    int node(int v) { return main[find(v)]; }

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;

        main[x_root] = max(main[x_root], main[y_root]);
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

struct node {
    vector<int> next;
    int p = -1;

    int val = -1;
};
vector<node> first;
vector<node> last;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 0; i < N; i++) first.push_back({});
        for (int i = 0; i < N - 1; i++) {
            int v, p; cin >> v >> p;
            v--, p--;
            first[v].p = p;
            first[p].next.push_back(v);
            first[v].val = v;
        }

        int root = -1;
        for (int i = 0; i < N; i++) if (first[i].p == -1) {
            root = i;
            first[i].val = i;
        }

        int M; cin >> M;
        for (int i = 0; i < N; i++) last.push_back({});
        for (int i = 0; i < M - 1; i++) {
            int v, p; cin >> v >> p;
            v--, p--;

            last[v].p = p;
            last[p].next.push_back(v);
            last[v].val = v;
        }
        last[root].val = root;

        DSU dsu(N);
        vector<pii> oper;
        for (auto &v : last) {
            if (v.p == -1) continue;

            stack<pii> tomerge;
            int one = v.val, two = v.val;
            while (first[one].p != last[two].p && first[one].p != -1 && last[two].p != -1) {
                int onep = dsu.node(first[one].p);
                int twop = last[two].p;

                if (onep == twop || onep == -1 || twop == -1) continue;

                tomerge.push({onep, twop});

                one = onep;
                two = twop;
            }

            while (!tomerge.empty()) {
                auto [one, two] = tomerge.top();
                tomerge.pop();
                oper.push_back({one + 1, two + 1});
                dsu.unite(one, two);
            }
        }

        for (int i = 0; i < N; i++) {
            int upd = dsu.node(first[i].val);
            if (last[upd].val == -1) oper
        }

        cout << oper.size() << endl;
        for (auto [a, b] : oper) cout << a << " " << b << endl;
    }
}