// https://codeforces.com/contest/2000/problem/E

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
        int n, m, k;
        cin >> n >> m >> k;

        int cnts[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cnts[i][j] = 0;
        }


        for (int i = 0; i < n - k + 1; i++) {
            // cout << i << endl;
            for (int j = 0; j < m - k + 1; j++) {
                for (int l = 0; l < k; l++) {
                    cnts[i][j + l]++;
                    if (i + k < n) cnts[i + k][j + l]--;

                    // cout << i << " " << j << " " << l << endl;
                    // cout << cnts[1][0] << endl;
                }
            }
        }

        vector<ll> nums;

        // cout << cnts[1][0] << endl;

        for (int j = 0; j < m; j++) {
            int counter = 0;
            for (int i = 0; i < n; i++) {
                counter += cnts[i][j];
                // cout << i << " " << j << " " << cnts[i][j] << endl;

                cnts[i][j] = counter;
                nums.push_back(cnts[i][j]);
                // cout << i << " " << j << " " << cnts[i][j] << endl;
            }
        }

        sort(nums.begin(), nums.end(), greater<ll>());
        // cout << nums.back() << endl;

        int w;
        cin >> w;
        ll gorillas[w];
        for (int i = 0; i < w; i++) cin >> gorillas[i];

        sort(gorillas, gorillas + w, greater<ll>());

        ll total = 0;
        int idx = 0;
        for (ll gorilla : gorillas) {
            total += gorilla * nums[idx++];
        }

        cout << total << endl;
    }
}