// https://usaco.org/index.php?page=viewproblem2&cpid=897

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

ll binpow(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("poetry");

    int N, M, K;
    cin >> N >> M >> K;

    ll MOD = 1e9 + 7;

    pii words[N];
    for (int i = 0; i < N; i++) cin >> words[i].first >> words[i].second;

    ll ways[K + 1];
    ways[0] = 1;
    for (int i = 1; i <= K; i++) ways[i] = 0;

    for (int i = 1; i <= K; i++) {
        for (int j = 0; j < N; j++) {
            if (i - words[j].first >= 0) ways[i] = (ways[i] + ways[i - words[j].first]) % MOD;
        }
    }

    ll waysn[N];
    for (int i = 0; i < N; i++) waysn[i] = 0;
    for (int i = 0; i < N; i++) {
        pii word = words[i];
        waysn[word.second - 1] = (waysn[word.second - 1] + ways[K - word.first]) % MOD;
    }

    ll cnts[26];
    for (int i = 0; i < 26; i++) cnts[i] = 0;
    for (int i = 0; i < M; i++) {
        char e;
        cin >> e;
        cnts[e - 'A']++;
    }
 
    ll total = 1;
    for (int i = 0; i < 26; i++) {
        ll cur = cnts[i];

        if (cur == 0) continue;

        ll next = 0;
        for (int j = 0; j < N; j++) {
            next = (next + 
                (total * binpow(waysn[j], cur, MOD)) % MOD
            ) % MOD;
        }

        total = next;
    }

    cout << total;
}