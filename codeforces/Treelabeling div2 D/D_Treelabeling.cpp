// https://codeforces.com/contest/1605/problem/D

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
    int num;
};
vector<node> graph;
vector<int> evens, odds;

vector<int> nums[32];

void dfs(int cur, int parent, bool h) {
    if (h) odds.push_back(cur);
    else evens.push_back(cur);
    for (int next : graph[cur].next) if (!(next == parent)) dfs(next, cur, h^1);
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

        graph.clear();
        for (int i = 0; i < N; i++) graph.push_back({});

        for (int i = 0; i < 32; i++) nums[i].clear();

        for (ll i = 1; i <= N; i++) {
            for (int b = 31; b >= 0; b--) {
                if ((1ll<<b)&i) {
                    nums[b].push_back(i);
                    break;
                }
            }
        }

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }
        dfs(0, -1, 0);

        if (evens.size() > odds.size()) evens.swap(odds);

        for (int b = 0; (1<<b) <= evens.size(); b++) {
            if ((1<<b)&evens.size()) {
                for (int i = 0; i < (1<<b); i++) {
                    graph[evens.back()].num = nums[b].back();

                    evens.pop_back();
                    nums[b].pop_back();
                }
            }
        }

        for (int b = 0; b < 32; b++) {
            while (!nums[b].empty()) {
                graph[odds.back()].num = nums[b].back();
                nums[b].pop_back();
                odds.pop_back();
            }
        }

        for (int i = 0; i < N; i++) cout << graph[i].num << " ";
        cout << endl;
    }
}