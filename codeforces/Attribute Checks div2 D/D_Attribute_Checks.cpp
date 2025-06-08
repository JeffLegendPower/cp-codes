// https://codeforces.com/contest/2025/problem/D

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
const int Nmax = 5e3 + 1;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int l, int r, int value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

int query(int p) {
  int res = 0;
  for (p += N; p > 0; p >>= 1) res += t[p];
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, M;
    cin >> n >> M;

    N = M + 1;

    // i is intelligence, (m - i) is strength

    int m = 0;
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        if (r == 0) {
            m++;
            for (int i = m; i > 0; i--) {
                int last = query(i - 1);
                int cur = query(i);
                modify(i, i + 1, max(0, last - cur));
            }
        } else if (r > 0) {
            int low = r, high = m;
            if (low <= high) modify(low, high + 1, 1);
        } else {
            r = -r;
            int high = m - r, low = 0;
            if (low <= high) modify(low, high + 1, 1);
        }
    }

    int most = 0;
    for (int i = 0; i <= M; i++) {
        most = max(most, query(i));
    }
    cout << most << endl;
}