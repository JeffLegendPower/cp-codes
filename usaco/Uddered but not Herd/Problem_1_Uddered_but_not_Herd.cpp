// https://usaco.org/index.php?page=viewproblem2&cpid=1089

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

const int MAXN = 20;
ll dp[1 << MAXN];

// num chars i, j such that char i comes right after char j
ll adj[26][26];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    for (int i = 0; i < 1<<MAXN; i++) dp[i] = 1e9;
    dp[0] = 1;

    string s;
    cin >> s;

    int S = s.size();

    int charset = 0;
    for (int i = 0; i < S - 1; i++) {
        adj[s[i + 1] - 'a'][s[i] - 'a']++;
        
        charset |= (1 << (s[i] - 'a'));
    }
    charset |= (1 << (s[S - 1] - 'a'));

    int N = __builtin_popcount(charset);
    vector<int> chars;
    for (int bit = 0; bit < 26; bit++) {
        if (charset & (1 << bit)) chars.push_back(bit);
    }
    

    for (int num = 1; num <= N; num++) {
        for (int msk = 0; msk < 1<<N; msk++) {
            if (__builtin_popcount(msk) != num) continue;

            for (int c = 0; c < N; c++) {
                if (!(msk & (1<<c))) continue;

                ll numadj = 0;
                for (int c2 = 0; c2 < N; c2++) {
                    if (!(msk & (1<<c2))) continue;
                    numadj += adj[chars[c2]][chars[c]];
                }

                dp[msk] = min(dp[msk], dp[msk ^ (1<<c)] + numadj);
            }
        }
    }

    cout << dp[(1<<N) - 1];
}