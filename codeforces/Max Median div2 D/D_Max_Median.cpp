// https://codeforces.com/problemset/problem/1486/D

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, k;
    cin >> N >> k;

    int a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    int best = 1;
    int low = 1, high = N;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        int pre[N + 1];
        pre[0] = 0;
        for (int i = 0; i < N; i++) {
            pre[i + 1] = pre[i] + ((a[i] >= mid) * 2 - 1);
        }

        set<int> mins;
        bool works = false;
        for (int i = k - 1; i < N; i++) {
            mins.insert(pre[i - k + 1]);
            if ((pre[i + 1] - (*mins.begin())) > 0) works = true;
        }

        if (works) {
            best = mid;
            low = mid + 1;
        } else high = mid - 1;
    }

    cout << best;
}