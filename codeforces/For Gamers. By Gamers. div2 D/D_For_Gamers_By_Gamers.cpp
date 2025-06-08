// https://codeforces.com/contest/1657/problem/D

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


struct unt {
    ll c, d, h;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, C;
    cin >> N >> C;

    vector<unt> units(N);
    for (int i = 0; i < N; i++) {
        cin >> units[i].c >> units[i].d >> units[i].h;
    }

    sort(units.begin(), units.end(), [](unt one, unt two) {
        if (one.c == two.c) {
            return one.d * one.h > two.d * two.h;
        }
        return one.c < two.c;
    });

    vector<ll> pows(C + 1, 0);
    pows[0] = 0;
    for (int i = 0; i < N; i++) {
        unt unit = units[i];
        if (i > 0 && unit.c == units[i - 1].c) continue;
        int num = 0;
        for (int j = unit.c; j <= C; j += unit.c) {
            num++;
            pows[j] = max(pows[j], unit.d * unit.h * num);
        }
    }
    vector<ll> pres(C + 1, 0);
    for (int i = 1; i <= C; i++) pres[i] = max(pres[i - 1], pows[i]);

    int M;
    cin >> M;

    while (M--) {
        ll D, H;
        cin >> D >> H;
        ll str = D * H;

        int low = 0, high = C;
        int best = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            ll midpow = pres[mid];
            if (midpow <= str) low = mid + 1;
            else {
                high = mid - 1;
                best = mid;
            }
        }

        cout << best << " ";
    }
}