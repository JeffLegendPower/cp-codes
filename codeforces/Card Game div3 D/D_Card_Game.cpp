// https://codeforces.com/problemset/problem/1932/D

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

vector<string> ss[26];
vector<string> opp;

int calc(char c) {
    sort(ss[c - 'A'].begin(), ss[c - 'A'].end());
    int left = 0, right = ss[c - 'A'].size() - 1;
    while (left < right) {
        opp.push_back(ss[c - 'A'][left++] + " " + ss[c - 'A'][right--]);
    }

    if (left == right) return left;
    else return -1;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        char t; cin >> t;
        for (int i = 0; i < 26; i++) ss[i].clear();

        for (int i = 0; i < 2*N; i++) {
            string s; cin >> s;
            ss[s[1] - 'A'].push_back(s);
        }

        vector<string> extra;
        int num = N;
        if (t != 'C') {
            int res = calc('C');
            if (res != -1) extra.push_back(ss['C' - 'A'][res]);
            num -= ss['C' - 'A'].size() / 2;
        } if (t != 'D') {
            int res = calc('D');
            if (res != -1) extra.push_back(ss['D' - 'A'][res]);
            num -= ss['D' - 'A'].size() / 2;
        } if (t != 'H') {
            int res = calc('H');
            if (res != -1) extra.push_back(ss['H' - 'A'][res]);
            num -= ss['H' - 'A'].size() / 2;
        } if (t != 'S') {
            int res = calc('S');
            if (res != -1) extra.push_back(ss['S' - 'A'][res]);
            num -= ss['S' - 'A'].size() / 2;
        }

        vector<string> trs;
        sort(ss[t - 'A'].begin(), ss[t - 'A'].end(), greater<string>());
        int idx = 0;
        while (num--) {
            trs.push_back(ss[t - 'A'][idx++]);
        }

        while (idx < ss[t - 'A'].size()) {
            opp.push_back(ss[t - 'A'][idx++] + " " + trs.back());
            trs.pop_back();
        }

        if (trs.size() < extra.size()) {
            cout << "IMPOSSIBLE" << endl;
            opp.clear();
            continue;
        }

        while (!trs.empty()) {
            cout << extra.back() << " " << trs.back() << endl;
            trs.pop_back();
            extra.pop_back();
        }

        while (!opp.empty()) {
            cout << opp.back() << endl;
            opp.pop_back();
        }
    }
}