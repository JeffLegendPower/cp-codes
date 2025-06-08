// https://codeforces.com/contest/1610/problem/D

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

    ll MOD = 1e9 + 7;

    ll a[N];
    int numodds = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (a[i] % 2 == 1) numodds++;
    }
    
    ll pow2s[N + 1];
    pow2s[0] = 1;
    for (int i = 1; i <= N; i++) {
        pow2s[i] = (pow2s[i - 1] * 2) % MOD;
    }

    ll total = 0;
    for (ll i = N - 1; i >= N - numodds; i--) {
        total = (total + pow2s[i]) % MOD;
    }


    vector<int> a2pows;
    for (int i = 0; i < N; i++) {
        if (a[i] % 2 == 1) continue;
        int num = 0;
        while (a[i] % 2 == 0) {
            a[i] /= 2;
            num++;
        }
        a2pows.push_back(num);
    }

    sort(a2pows.begin(), a2pows.end());

    ll num = -1;
    ll cnt = 1;
    for (int i = 0; i < a2pows.size(); i++) {
        if (a2pows[i] != num) {
            ll toadd = (pow2s[cnt - 1] + MOD - 1) % MOD;
            toadd = (toadd * pow2s[a2pows.size() - i]) % MOD;
            total = (total + toadd) % MOD;

            num = a2pows[i];
            cnt = 1;
        } else cnt++;
    }

    ll toadd = (pow2s[cnt - 1] + MOD - 1) % MOD;
    total = (total + toadd) % MOD;

    cout << total << endl;
}