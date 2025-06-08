// https://codeforces.com/contest/1968/problem/G2

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

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, l, r;
        cin >> N >> l >> r;

        string s; cin >> s;
        vector<int> zf = z_function(s);
        zf[0] = N;

        vector<int> lcps(N + 1, 0);

        // solve for lcp for each k <= sqrt(n) in O(nlogn) time for a total of O(nlogn*sqrtn) time
        for (int i = 1; i*i <= N; i++) {
            int low = 1, high = N;
            int best = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;

                int cnt = 0;
                for (int j = 0; j < N; j++) {
                    if (zf[j] >= mid) {
                        cnt++;
                        j += mid - 1;
                    }
                }

                if (cnt >= i) {
                    low = mid + 1;
                    best = mid;
                } else high = mid - 1;
            }

            lcps[i] = best;
        }

        // now solve for max k for each lcp <= sqrt(n) in O(n) time for a total of O(nsqrtn) time
        // as for all k > sqrt(n), lcp <= sqrt(n) so we can do this
        for (int i = 1; i*i <= N; i++) {
            int cnt = 0;
            for (int j = 0; j < N; j++) {
                if (zf[j] >= i) {
                    cnt++;
                    j += i - 1;
                }
            }

            lcps[cnt] = max(lcps[cnt], i);
        }

        for (int i = N - 1; i >= 0; i--) lcps[i] = max(lcps[i], lcps[i + 1]);
        for (int i = l; i <= r; i++) cout << lcps[i] << " ";
        cout << endl;
    }
}