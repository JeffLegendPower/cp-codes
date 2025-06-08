// https://codeforces.com/contest/687/problem/C

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    bool sums[K + 1][K + 1];
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= K; j++) sums[i][j] = false;
    }
    sums[0][0] = true;
    
    while (N--) {
        int c;
        cin >> c;

        for (int x = K - c; x >= 0; x--) {
            for (int x2 = 0; x2 <= K - c; x2++) {
                sums[x + c][x2 + c] |= sums[x][x2];
                sums[x + c][x2] |= sums[x][x2];
            }
        }
    }

    vector<int> sums2;
    for (int i = 0; i <= K; i++) if (sums[K][i]) sums2.push_back(i);

    cout << sums2.size() << endl;
    for (int sum : sums2) cout << sum << " ";
}