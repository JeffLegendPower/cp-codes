// https://codeforces.com/problemset/problem/1761/C

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

struct node {
    vector<int> prev;
    vector<int> nums;
    bool searched = false;
};
vector<node> graph;

vector<int> topo;
void toposort(int v) {
    graph[v].searched = true;

    for (int next : graph[v].prev) {
        if (!graph[next].searched) toposort(next);
    }

    topo.push_back(v);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        graph.clear();
        topo.clear();
        for (int i = 0; i < N; i++) graph.push_back({});

        bool b[N][N];
        for (int i = 0; i < N; i++) {
            string s; cin >> s;
            for (int j = 0; j < N; j++) {
                if (s[j] == '0') continue;
                graph[i].prev.push_back(j);
            }
        }

        for (int i = 0; i < N; i++) if (!graph[i].searched) toposort(i);
        reverse(topo.begin(), topo.end());

        for (int i : topo) {
            graph[i].nums.push_back(i+1);
            for (int next : graph[i].prev) {
                vector<bool> has(N+1, false);

                for (int x : graph[next].nums) has[x] = true;
                for (int x : graph[i].nums) if (!has[x]) graph[next].nums.push_back(x);
            }
        }

        for (int i = 0; i < N; i++) {
            cout << graph[i].nums.size() << " ";
            for (int num : graph[i].nums) cout << num << " ";
            cout << endl;
        }
    }
}