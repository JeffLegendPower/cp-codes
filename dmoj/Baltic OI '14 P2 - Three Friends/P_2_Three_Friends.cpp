// https://dmoj.ca/problem/btoi14p2

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

// 0 indexed
// assume extra char is in position s[M] to s[N-1];
// return whether this is possible
bool solve(string s) {
    int N = s.size();
    int M = (N-1)/2;

    // possible[i][0] = whether first i chars on second half match up
    // possible[i][1] = whether first i chars on second half match up but some might be shifted 1 right
    // because the bad token is here
    vector<vector<bool>> possible(M+1, vector<bool>(2, false));
    possible[0][1] = true;

    for (int i = 0; i < M+1; i++) {
        possible[i][0] = s[M+i] == s[i];
        if (i > 0 && !possible[i-1][0]) possible[i][0] = false;

        if (i > 0) {
            possible[i][1] = s[M+i] == s[i-1];
            if (!possible[i-1][1]) possible[i][1] = false;
            if (possible[i-1][0]) possible[i][1] = true;
        }
    }

    return possible[M][1];
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    string s; cin >> s;
    int N = s.size();

    if (N % 2 == 0) {
        cout << "NOT POSSIBLE";
        return 0;
    }

    int M = (N-1)/2;

    bool possible1 = solve(s);
    reverse(s.begin(), s.end());
    bool possible2 = solve(s);
    reverse(s.begin(), s.end());

    if (!possible1 && !possible2) {
        cout << "NOT POSSIBLE";
    } if (possible1 && !possible2) {
        for (int i = 0; i < M; i++) cout << s[i];
    } if (!possible1 && possible2) {
        for (int i = 0; i < M; i++) cout << s[M+1 + i];
    } if (possible1 && possible2) {
        bool same = true;
        for (int i = 0; i < M; i++) if (s[i] != s[M+1+i]) same = false;
        if (!same) cout << "NOT UNIQUE";
        else for (int i = 0; i < M; i++) cout << s[i];
    }
}