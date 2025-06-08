// https://dmoj.ca/problem/ioi05p1

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

    int L, W;
    cin >> L >> W;

    int horpre[L+1][W], vertpre[L][W+1];

    for (int i = 0; i <= L; i++) {
        for (int j = 0; j < W; j++) horpre[i][j] = 0;
    } for (int i = 0; i < L; i++) {
        for (int j = 0; j <= W; j++) vertpre[i][j] = 0;
    }

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int l, w; cin >> l >> w;
        l--, w--;
        horpre[l+1][w]++;
        vertpre[l][w+1]++;
    }

    for (int i = 1; i <= L; i++) {
        for (int j = 0; j < W; j++) horpre[i][j] += horpre[i-1][j];
    } for (int i = 0; i < L; i++) {
        for (int j = 1; j <= W; j++) vertpre[i][j] += vertpre[i][j-1];
    }

    int perim_horl[L], perim_horr[L];
    int perim_vertl[W], perim_vertr[W];
    for (int i = 0; i < L; i++) {
        perim_horl[i] = 1e8;
        perim_horr[i] = 1e8;
    } for (int i = 0; i < W; i++) {
        perim_vertl[i] = 1e8;
        perim_vertr[i] = 1e8;
    }

    for (int l = 0; l < L; l++) {
        for (int r = l; r < L; r++) {
            int flowers = 0;
            int w2 = 0;
            for (int w = 0; w < W; w++) {
                flowers += horpre[r+1][w] - horpre[l][w];
                while (flowers > K || horpre[r+1][w2] - horpre[l][w2] == 0) {
                    flowers -= horpre[r+1][w2] - horpre[l][w2];
                    w2++;
                }

                int perim = 2*(r-l+1) + 2*(w-w2+1);
                if (flowers == K) {
                    perim_horl[l] = min(perim_horl[l], perim);
                    perim_horr[r] = min(perim_horr[r], perim);
                }
            }
        }
    }

    for (int l = 0; l < W; l++) {
        for (int r = l; r < W; r++) {
            int flowers = 0;
            int w2 = 0;
            for (int w = 0; w < L; w++) {
                flowers += vertpre[w][r+1] - vertpre[w][l];
                while (flowers > K || vertpre[w2][r+1] - vertpre[w2][l] == 0) {
                    flowers -= vertpre[w2][r+1] - vertpre[w2][l];
                    w2++;
                }

                int perim = 2*(r-l+1) + 2*(w-w2+1);
                if (flowers == K) {
                    perim_vertl[l] = min(perim_vertl[l], perim);
                    perim_vertr[r] = min(perim_vertr[r], perim);
                    // if (l == 3) cout << r << "  " << perim << " " << w << " " << w2 << endl;
                }
            }
        }
    }

    for (int i = 1; i < L; i++) perim_horr[i] = min(perim_horr[i], perim_horr[i-1]);
    for (int i = L-2; i >= 0; i--) perim_horl[i] = min(perim_horl[i], perim_horl[i+1]);
    for (int i = 1; i < W; i++) perim_vertr[i] = min(perim_vertr[i], perim_vertr[i-1]);
    for (int i = W-2; i >= 0; i--) perim_vertl[i] = min(perim_vertl[i], perim_vertl[i+1]);

    int best = 1e8;
    for (int i = 0; i < L-1; i++) best = min(best, perim_horr[i] + perim_horl[i+1]);
    for (int i = 0; i < W-1; i++) {
        best = min(best, perim_vertr[i] + perim_vertl[i+1]);
        // cout << i << " " << perim_vertl[i] << endl;
    }

    if (best == 1e8) cout << "NO";
    else cout << best;
}