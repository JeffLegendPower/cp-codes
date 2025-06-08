// https://dmoj.ca/problem/ccc21s5

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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
const int Nmax = 2e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = gcd(t[i<<1], t[i<<1|1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = gcd(res, t[l++]);
    if (r&1) res = gcd(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int M; cin >> N >> M;

    int gcds[N][17];
    for (int i = 0; i < N; i++) for (int j = 0; j < 17; j++) gcds[i][j] = 0;

    array<int, 3> Z[M];
    for (int i = 0; i < M; i++) {
        int l, r, z;
        cin >> l >> r >> z;
        l--, r--;
        gcds[l][z]++;
        if (r < N - 1) gcds[r + 1][z]--;

        Z[i][0] = l, Z[i][1] = r, Z[i][2] = z;
    }

    for (int i = 0; i < 17; i++) for (int j = 1; j < N; j++) gcds[j][i] += gcds[j - 1][i];

    for (int i = 0; i < N; i++) {
        ll a = 1;
        for (ll j = 1; j < 17; j++) {
            if (gcds[i][j] > 0) a = lcm(a, j);
        }

        t[N + i] = a;
    }
    build();

    bool possible = true;
    for (auto [l, r, z] : Z) {
        if (query(l, r + 1) != z) {
            possible = false;
        }
    }

    if (!possible) {
        cout << "Impossible";
        return 0;
    }

    for (int i = 0; i < N; i++) cout << t[N + i] << " ";
}