// https://codeforces.com/gym/102951/problem/C

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

    int N;
    cin >> N;

    int a[N];
    map<int, int> b;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) {
        int bi; cin >> bi;
        b[bi] = i;
    }

    int lcs[N + 1];
    lcs[0] = -1;
    for (int i = 1; i <= N; i++) lcs[i] = 1e6;

    int longest = 0;
    for (int i = 0; i < N; i++) {
        int bpos = b[a[i]];

        int low = 0, high = N - 1;
        int best = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (lcs[mid] >= bpos) {
                best = mid;
                high = mid - 1;
            } else low = mid + 1;
        }

        lcs[best] = min(lcs[best], bpos);
        longest = max(longest, best);
    }

    cout << longest;
}