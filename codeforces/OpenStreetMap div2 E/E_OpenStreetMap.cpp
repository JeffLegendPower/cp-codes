// https://codeforces.com/contest/1195/problem/E

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M, a, b;
    cin >> N >> M >> a >> b;

    ll g0, x, y, z;
    cin >> g0 >> x >> y >> z;

    vector<ll> g;
    g.push_back(g0);
    for (int i = 1; i <= (N - 1) * M + M - 1; i++) {
        g.push_back((g.back() * x + y) % z);
    }

    // ll h[N][M];
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //         h[i][j] = g[i * M + j];
    //     }
    // }

    ll mins[N][M];
    for (int i = 0; i < N; i++) {
        deque<plli> q;
        int added = 0, removed = 0;

        for (int j = 0; j < b; j++) {
            while (!q.empty() && q.back().first > g[i * M + j]) q.pop_back();
            q.push_back({g[i * M + j], added});
            added++;
        }
        for (int j = b - 1; j < M; j++) {
            mins[i][j] = q.front().first;

            if (j < M - 1) {
                if (!q.empty() && q.front().second == removed) q.pop_front();
                removed++;

                while (!q.empty() && q.back().first > g[i * M + j + 1]) q.pop_back();
                q.push_back({g[i * M + j + 1], added});
                added++;
            }
        }
    }

    ll total = 0;

    for (int j = b - 1; j < M; j++) {
        deque<plli> q;
        int added = 0, removed = 0;

        for (int i = 0; i < a; i++) {
            while (!q.empty() && q.back().first > mins[i][j]) q.pop_back();
            q.push_back({mins[i][j], added});
            added++;
        }

        for (int i = a - 1; i < N; i++) {
            total += q.front().first;

            if (i < N - 1) {
                if (!q.empty() && q.front().second == removed) q.pop_front();
                removed++;

                while (!q.empty() && q.back().first > mins[i +  1][j]) q.pop_back();
                q.push_back({mins[i + 1][j], added});
                added++;
            }
        }
    }

    cout << total << endl;
}