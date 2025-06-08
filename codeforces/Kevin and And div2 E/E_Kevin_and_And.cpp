// https://codeforces.com/contest/2061/problem/E

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

    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        ll a[N], b[M];
        ll summ = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            summ += a[i];
        } for (int i = 0; i < M; i++) cin >> b[i];

        ll bsub[1<<M];
        bsub[0] = 0;
        for (int i = 0; i < (1<<M); i++) {
            bsub[i] = (1<<30) - 1;
            for (int bit = 0; bit < M; bit++) {
                if ((1<<bit)&i) bsub[i] &= b[bit];
            }
        }

        ll ac[N][M+1];
        for (int i = 0; i < N; i++) for (int j = 0; j <= M; j++) ac[i][j] = a[i];

        for (int j = 1; j <= M; j++) {
            for (int msk = 0; msk < (1<<M); msk++) {
                if (__builtin_popcount(msk) != j) continue;
                for (int i = 0; i < N; i++) {
                    ac[i][j] = min(ac[i][j], a[i]&bsub[msk]);
                    // cout << bsub[msk] << " " << j << endl;
                }
            }
        }

        priority_queue<pll> opers;
        for (int i = 0; i < N; i++) {
            opers.push({ac[i][0] - ac[i][1], i});
        }

        // cout << ac[0][2] << endl;

        vector<int> nums(N, 1);
        while (K > 0) {
            K--;

            auto [diff, i] = opers.top();
            opers.pop();

            // cout << diff << endl;

            summ -= diff;
            nums[i]++;
            if (nums[i] <= M) opers.push({ac[i][nums[i]-1] - ac[i][nums[i]], i});
        }

        // cout << bsub[3] << endl;

        // set<pll, greater<pll>> opers;
        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < M; j++) {
        //         opers.insert({a[i] - (a[i]&b[j]), i});
        //     }
        // }

        // while (K > 0) {
        //     K--;

        //     auto [diff, idx] = *opers.begin();
        //     for (int i = 0; i < M; i++) {
        //         opers.erase({a[idx] - (a[idx]&b[i]), idx});
        //     }

        //     summ -= diff;
        //     a[idx] -= diff;
        //     for (int i = 0; i < M; i++) {
        //         opers.insert({a[idx] - (a[idx]&b[i]), idx});
        //     }
        // }

        cout << summ << endl;
    }
}