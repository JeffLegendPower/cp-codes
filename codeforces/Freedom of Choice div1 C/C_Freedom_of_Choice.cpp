// https://codeforces.com/contest/1893/problem/C

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


struct blck {
    int n;
    ll l, r;
    vector<ll> a, c;
    ll sumc = 0;
}; struct entry {
    ll mincost = 0; // min # of a needed to get atleast l elements
    ll extraspace = 0; // # of eles other than a available in the multisets after removing l elements
    ll suml = 0, sumr = 0;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int M;
        cin >> M;

        blck blocks[M];
        ll suml = 0, sumr = 0;

        map<ll, entry> entries;

        for (int i = 0; i < M; i++) {
            cin >> blocks[i].n >> blocks[i].l >> blocks[i].r;
            suml += blocks[i].l;
            sumr += blocks[i].r;
            for (int j = 0; j < blocks[i].n; j++) {
                ll a; cin >> a;
                blocks[i].a.push_back(a);
            } for (int j = 0; j < blocks[i].n; j++) {
                ll c; cin >> c;
                blocks[i].c.push_back(c);
                blocks[i].sumc += c;
            }

            for (int j = 0; j < blocks[i].n; j++) {
                ll a = blocks[i].a[j];
                entry cur = entries[a];
                cur.suml += blocks[i].l;
                cur.sumr += blocks[i].r;
                ll numa = blocks[i].c[j];
                ll numother = blocks[i].sumc - numa;
                numother -= blocks[i].l;
                if (numother < 0) {
                    cur.mincost += -numother;
                    numa -= -numother;
                }
                cur.extraspace += min(max(0ll, numother), blocks[i].r - blocks[i].l);

                entries[a] = cur;
            }
        }

        ll least = 1e18;
        for (auto itr = entries.begin(); itr != entries.end(); itr++) {
            ll a = itr->first;
            entry cur = itr->second;

            if (a < suml || a > sumr) continue;
            if (suml <= a - 1 && entries.find(a - 1) == entries.end()) least = 0;
            if (a + 1 <= sumr && entries.find(a + 1) == entries.end()) least = 0;
            
            ll cost = cur.mincost;
            a -= sumr - cur.sumr + cur.suml + cur.extraspace;
            cost += max(a, 0ll);
            least = min(least, cost);
        }

        if (least == 1e18) least = 0;

        cout << least << endl;
    }
}