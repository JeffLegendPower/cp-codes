// https://codeforces.com/contest/1858/problem/B

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

    int T;
    cin >> T;

    while (T--) {
        ll N, M, d;
        cin >> N >> M >> d;

        ll sellers[M];
        for (int i = 0; i < M; i++) cin >> sellers[i];

        ll cookies = 1;
        ll last = 1;

        for (int i = 0; i < M; i++) {
            ll dist = sellers[i] - last;
            cookies += (dist - 1) / d;
            if (sellers[i] > last) cookies++;
            last = sellers[i];
        }
        cookies += (N - last) / d;

        ll cookies2 = cookies;
        ll cnt = 0;
        
        for (int i = 0; i < M; i++) {
            ll start = (i == 0) ? 1 : sellers[i - 1];
            ll end = (i == M - 1) ? N + 1 : sellers[i + 1];

            ll last1 = (sellers[i] - start - 1) / d;
            ll last2 = (end - sellers[i] - 1) / d;
            ll cnt1 = last1 + last2 + 1;

            // cout << cnt1 << endl;

            ll cnt3 = (end - start - 1) / d;
            if (sellers[i] == 1) cnt3++;
            // cout << cnt3 << endl;
            ll cookies3 = cookies - (cnt1 - cnt3);
            if (cookies3 < cookies2) {
                cookies2 = cookies3;
                cnt = 1;
            } else if (cookies3 == cookies2) cnt++;

            // cout << cookies3 << endl;
        }

        cout << cookies2 << " " << cnt << endl;
    }
}