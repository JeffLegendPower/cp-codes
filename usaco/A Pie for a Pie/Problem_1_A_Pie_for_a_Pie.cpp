// https://usaco.org/index.php?page=viewproblem2&cpid=765

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
    vector<int> next;
	DSU(int size) : parents(size), sizes(size, 1), next(size) {
		for (int i = 0; i < size; i++) {
            parents[i] = i;
            next[i] = i + 1;
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
        next[x_root] = max(next[x_root], next[y_root]);
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

struct node {
    int idx;
    bool searched = false;
    int dist = -1;

    ll s[2];
};
vector<node> cows[2];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("piepie");

    int N;
    ll D;
    cin >> N >> D;

    for (int i = 0; i < N; i++) {
        node cur;
        cin >> cur.s[0] >> cur.s[1];
        cur.idx = i;
        cows[0].push_back(cur);
    } for (int i = 0; i < N; i++) {
        node cur;
        cin >> cur.s[0] >> cur.s[1];
        cur.idx = i;
        cows[1].push_back(cur);
    }

    sort(cows[0].begin(), cows[0].end(), [](node one, node two) {
        return one.s[1] < two.s[1];
    });
    sort(cows[1].begin(), cows[1].end(), [](node one, node two) {
        return one.s[0] < two.s[0];
    });

    vector<DSU> cow;
    cow.push_back(DSU(N + 1));
    cow.push_back(DSU(N + 1));

    // if at bessie, j=0, if at elsie j=1
    // {i, j}
    deque<pii> todo;
    for (int i = 0; i < N; i++) {
        if (cows[0][i].s[1] == 0) {
            todo.push_back({i, 0});
            cows[0][i].dist = 1;
            cows[0][i].searched = true;
            cow[0].unite(i, i + 1);
        }
    } for (int i = 0; i < N; i++) {
        if (cows[1][i].s[0] == 0) {
            todo.push_back({i, 1});
            cows[1][i].dist = 1;
            cows[1][i].searched = true;
            cow[1].unite(i, i + 1);
        }
    }

    while (!todo.empty()) {
        auto [i, j] = todo.front();
        todo.pop_front();

        int next = cows[j][i].dist + 1;

        ll most = cows[j][i].s[j], least = most - D;

        int low = 0, high = N - 1;
        int best = N;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (cows[j^1][mid].s[j] < least) {
                low = mid + 1;
            } else {
                high = mid - 1;
                best = mid;
            }
        }

        for (int i2 = cow[j^1].next[cow[j^1].find(best)] - 1; i2 < N; i2 = cow[j^1].next[cow[j^1].find(i2)] - 1) {
            ll s = cows[j^1][i2].s[j];
            if (s > most) break;

            cows[j^1][i2].dist = next;
            todo.push_back({i2, j^1});

            cow[j^1].unite(i2, i2 + 1);
        }
    }

    int pies[N];
    for (int i = 0; i < N; i++) pies[cows[0][i].idx] = cows[0][i].dist;

    for (int i = 0; i < N; i++) {
        cout << pies[i];
        if (i < N - 1) cout << endl;
    }
}