// https://codeforces.com/contest/1624/problem/E

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


struct rnge {
    int l, r, i;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        string t[N];
        for (int i = 0; i < N; i++) cin >> t[i];
        string s;
        cin >> s;

        rnge seg2s[10][10];
        rnge seg3s[10][10][10];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                seg2s[i][j] = {-1, -1, -1};
                for (int k = 0; k < 10; k++) {
                    seg3s[i][j][k] = {-1, -1, -1};
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 1; j < M; j++) {
                seg2s[t[i][j - 1] - '0'][t[i][j] - '0'] = {j - 1, j, i};
            } for (int j = 2; j < M; j++) {
                seg3s[t[i][j - 2] - '0'][t[i][j - 1] - '0'][t[i][j] - '0'] = {j - 2, j, i};
            }
        }

        vector<rnge> dp(M, {-1, -1, -1});

        if (M >= 2) dp[1] = seg2s[s[0] - '0'][s[1] - '0'];
        if (M >= 3) dp[2] = seg3s[s[0] - '0'][s[1] - '0'][s[2] - '0'];
        
        for (int i = 3; i < M; i++) {
            rnge two = seg2s[s[i - 1] - '0'][s[i] - '0'];
            rnge three = seg3s[s[i - 2] - '0'][s[i - 1] - '0'][s[i] - '0'];
            
            if (two.l != -1 && dp[i - 2].l != -1) {
                dp[i] = two;
            } if (three.l != -1 && dp[i - 3].l != -1) {
                dp[i] = three;
            }
        }

        if (dp[M - 1].l == -1) {
            cout << -1 << endl;
            continue;
        }

        vector<rnge> ranges;
        int i = M - 1;
        while (i >= 0) {
            rnge cur = dp[i];
            ranges.push_back(cur);

            i -= cur.r - cur.l + 1;
        }

        reverse(ranges.begin(), ranges.end());
        cout << ranges.size() << endl;
        for (rnge range : ranges) {
            cout << range.l + 1 << " " << range.r + 1 << " " << range.i + 1 << endl;
        }
    }
}