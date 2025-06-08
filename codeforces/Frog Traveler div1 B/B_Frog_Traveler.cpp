// https://codeforces.com/contest/1601/problem/B

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

    int N;
    cin >> N;

    int a[N], b[N];
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];

    ll dp[N + 1];
    // from where, dist jumped
    pll prev[N + 1];
    
    for (int i = 0; i <= N; i++) dp[i] = 1e9;
    dp[N] = 0;

    deque<int> todo;
    set<int> searched;

    todo.push_back(N - 1);

    int rightsearch = N - 2;
    while (!todo.empty()) {
        int i = todo.front();
        todo.pop_front();

        searched.insert(i);

        for (int j = min(rightsearch, i + 1); j >= max(i - a[i], -1); j--) {

            if (j == -1) {
                if (dp[i + 1] + 1 < dp[0]) {
                    dp[0] = dp[i + 1] + 1;
                    prev[0] = {i + 1, i - j};
                }
                continue;
            }

            if (dp[i + 1] + 1 < dp[j + b[j] + 1]) {
                dp[j + b[j] + 1] = dp[i + 1] + 1;
                prev[j + b[j] + 1] = {i + 1, i - j};

                if (searched.find(j + b[j]) == searched.end()) todo.push_back(j + b[j]);
            }
        }
        rightsearch = min(rightsearch, max(i - a[i], -1) - 1);
    }

    if (dp[0] == 1e9) {
        cout << -1 << endl;
        return 0;
    }

    cout << dp[0] << endl;

    vector<ll> backtrack;
    for (int i = 0; i < N; i = prev[i].first) {
        backtrack.push_back(prev[i].first - prev[i].second);
    }

    reverse(backtrack.begin(), backtrack.end());

    for (ll back : backtrack) cout << back << " ";
}