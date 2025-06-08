// https://usaco.org/index.php?page=viewproblem2&cpid=1019

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

struct node {
    vector<int> next;
    ll dp;
};
node graph[100000];

bool possible = true;
void dfs(int cur, int parent, int k) {
    int nonzero = 0;
    map<int, int> nonzeros;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        dfs(next, cur, k);
        if (!possible) return;

        ll dp = (graph[next].dp + 1) % k;

        if (dp > 0) {
            if (nonzeros[k - dp] > 0) {
                nonzeros[k - dp]--;
                if (nonzeros[k - dp] == 0) nonzeros.erase(k - dp);
                nonzero--;
            } else {
                nonzero++;
                nonzeros[dp]++;
            }
        }
    }

    if (nonzero > 1) {
        possible = false;
    } else if (nonzero == 1) {
        for (auto itr = nonzeros.begin(); itr != nonzeros.end(); itr++) {
            if (itr->second == 0) continue;
            graph[cur].dp = itr->first;
            break;
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("deleg");

    int N;
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }

    vector<bool> ks(N, false);
    for (int k = 1; k <= N - 1; k++) {
        if ((N - 1) % k > 0) continue;
        possible = true;
        for (int i = 0; i < N; i++) graph[i].dp = 0;
        dfs(0, -1, k);
        ks[k - 1] = possible;
    }

    for (int i = 0; i < N - 1; i++) cout << ks[i];
}