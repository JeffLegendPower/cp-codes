// https://usaco.org/index.php?page=viewproblem2&cpid=1281&lang=en

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>
#define pcs pair<char, string>
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
    char c;
    // points to next str;
    int next = -1;

    ll size;
};
vector<vector<node>> graph;
vector<ll> lens;
vector<pcs> ts;

ll l, r;

void dfs(int row, ll l, ll r) {
    ll l2 = l, r2 = r;

    int i = 0;
    for (node n : graph[row]) {
        // cout << row << " " << i << " " << l << " " << r << endl;
        ll len = n.size;

        if (l <= min(r, len)) {
            if (n.next == -1) {
                // cout << row << " " << i << " " << l << " " << r << endl;
                cout << n.c;
            } else {
                dfs(n.next, l, r);
            }
        }

        l = max(1ll, l - len);
        r -= len;
        if (r <= 0) break;
    }

    l = l2, r = r2;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    string s = "a";
    cin >> l >> r >> N;

    ts.push_back({'.', "a"});
    graph.push_back({});
    lens.push_back(0);

    for (int i = 1; i <= N; i++) {
        pcs cur;
        cin >> cur.first >> cur.second;

        ts.push_back(cur);
        graph.push_back({});
        lens.push_back(0);
    }

    for (int i = N; i >= 0; i--) {
        for (int j = 0; j < ts[i].second.size(); j++) {
            node n;
            n.c = ts[i].second[j];

            if (i == N) {
                n.size = 1;

                if (lens[i] + n.size <= 1e18) {
                    lens[i] += n.size;
                    graph[i].push_back(n);
                }
                continue;
            }

            n.size = 1;
            // bottleneck makes this O(N^2)
            for (int k = i + 1; k <= N; k++) {
                if (n.c == ts[k].first) {
                    n.size = lens[k];
                    n.next = k;
                    break;
                }
            }

            if (lens[i] + n.size <= 1e18) {
                lens[i] += n.size;
                graph[i].push_back(n);
            }
        }
    }

    dfs(0);
}