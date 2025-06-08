// https://codeforces.com/contest/1933/problem/F

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

    int T2 = T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        bool grid[N][M];
        // can u reach the top val of column j at time i (where i = time t % N)
        // times[j][i]
        ll times[M][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> grid[i][j];
                times[j][i] = 1e9;
            }
        }

        times[0][0] = 0;
        for (int j = 0; j < M; j++) {
            deque<int> idxs;
            for (int i = 0; i < N; i++) if (times[j][i] != 1e9) idxs.push_back(i);

            while (!idxs.empty()) {
                int i = idxs.front();
                idxs.pop_front();

                if (!(grid[(i + 1) % N][j] || grid[(i + 2) % N][j])) {
                    if (times[j][i] + 1 < times[j][(i + 2) % N]) {
                        times[j][(i + 2) % N] = times[j][i] + 1;
                        idxs.push_back((i + 2) % N);
                    }
                }
            }

            if (j < M - 1) {
                for (int i = 0; i < N; i++) {
                    if (times[j][i] != 1e9 && !grid[(i + 1) % N][j + 1]) 
                        times[j + 1][(i + 1) % N] = times[j][i] + 1;
                }
            }
        }

        ll time = 1e18;
        for (ll i = 0; i < N; i++) {
            if (times[M - 1][i] != 1e9) {
                ll i2 = (times[M - 1][i] - (M - 1)) % N;

                time = min(time,
                    times[M - 1][i] + min(N - 1 - i2, i2 + 1)
                );
            }
        }

        if (time == 1e18) cout << -1 << endl;
        else cout << time << endl;
    }
}