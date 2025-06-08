// https://codeforces.com/problemset/problem/1861/C

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

    int T; cin >> T;
    
    while (T--) {
        string s; cin >> s;

        int N = s.size();

        int len = 0, incr = 0;

        // for 0 to be good, cnt >= 2 AND (
        // last one was 0 OR (last one was 1 and atleast 1 + between that 1 and this 0)
        // )

        // for 1 to be good, cnt < 2 OR (
        // last one was 1 OR (last)
        // )

        bool works = true;

        int cnt = 0;
        bool plus = false;
        int numplus = 0;
        int numplus0 = 0;
        bool neg = false;
        char last = '.';
        for (int i = 0; i < N; i++) {
            if (s[i] == '+') {
                cnt++;
                plus = true;
                numplus++;
                numplus0++;
            } if (s[i] == '-') {
                cnt--;
                numplus--;
                numplus0 = max(numplus0 - 1, 0);
                if (numplus < 0) neg = true;
            } if (s[i] == '0') {
                if (cnt < 2) works = false;
                if (numplus0 <= 0) works = false;

                if (last == '0' && !neg) numplus = max(numplus, 0);
                else numplus = 0;

                neg = false;
                last = '0';
            } if (s[i] == '1') {
                if (last == '0' && !neg) works = false;

                plus = false;
                numplus = 0;
                numplus0 = 0;
                last = '1';
            }
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}