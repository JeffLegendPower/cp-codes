// https://codeforces.com/contest/1349/problem/A

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

struct ppow {
    pii mins = {1e6, 1e6};
    int upd = 0;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    int a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    map<int, ppow> ppow2;

    for (int i = 0; i < N; i++) {

        for (int j = 2; j * j <= a[i]; j++) {
            int num = 0;
            while (a[i] % j == 0) {
                a[i] /= j;
                num++;
            }

            if (num == 0) continue;

            pii ppo = ppow2[j].mins;
            if (num <= ppo.first) {
                ppo.second = ppo.first;
                ppo.first = num;
            } else if (num < ppo.second) ppo.second = num;

            ppow2[j].mins = ppo;
            ppow2[j].upd++;
        }

        if (a[i] > 1) {
            int j = a[i];

            pii ppo = ppow2[j].mins;
            if (1 <= ppo.first) {
                ppo.second = ppo.first;
                ppo.first = 1;
            } else if (1 < ppo.second) ppo.second = 1;

            ppow2[j].mins = ppo;
            ppow2[j].upd++;
        }
    }

    ll num = 1;
    // cout << ppow2.size() << endl;
    for (auto itr = ppow2.begin(); itr != ppow2.end(); itr++) {
        int poww = itr->second.mins.second;

        int diff = N - itr->second.upd;
        if (diff == 1) poww = itr->second.mins.first;
        else if (diff >= 2) poww = 0;

        if (poww == 1000000) poww = 0;

        // cout << itr->first << " " << poww << endl;

        while (poww--) num *= itr->first;
    }

    cout << num;
}