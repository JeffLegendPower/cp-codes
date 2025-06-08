// https://codeforces.com/problemset/problem/1784/B

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

struct opp {
    int a1, a2;
    char c1, c2;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int M; cin >> M;

        string ppl[M];
        vector<int> todo[3][3];

        for (int i = 0; i < M; i++) {
            cin >> ppl[i];

            int cntw = -1, cnti = -1, cntn = -1;
            for (int j = 0; j < 3; j++) {
                if (ppl[i][j] == 'w') cntw++;
                if (ppl[i][j] == 'i') cnti++;
                if (ppl[i][j] == 'n') cntn++;
            }

            if (cntw > 0) {
                if (cnti < 0) todo[1][0].push_back(i);
                if (cntn < 0) todo[2][0].push_back(i);
            } if (cnti > 0) {
                if (cntw < 0) todo[0][1].push_back(i);
                if (cntn < 0) todo[2][1].push_back(i);
            } if (cntn > 0) {
                if (cntw < 0) todo[0][2].push_back(i);
                if (cnti < 0) todo[1][2].push_back(i);
            }
        }

        map<int, char> mapp;
        mapp[0] = 'w';
        mapp[1] = 'i';
        mapp[2] = 'n';

        vector<opp> opers;
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                while (!todo[i][j].empty() && !todo[j][i].empty()) {
                    opers.push_back({todo[i][j].back() + 1, todo[j][i].back() + 1, mapp[j], mapp[i]});
                    todo[i][j].pop_back();
                    todo[j][i].pop_back();
                }
            }
        }

        while (!todo[0][1].empty() && !todo[1][2].empty() && !todo[2][0].empty()) {
            opers.push_back({todo[0][1].back() + 1, todo[2][0].back() + 1, 'i', 'w'});
            opers.push_back({todo[2][0].back() + 1, todo[1][2].back() + 1, 'i', 'n'});
            todo[0][1].pop_back();
            todo[1][2].pop_back();
            todo[2][0].pop_back();
        } 
        while (!todo[1][0].empty() && !todo[2][1].empty() && !todo[0][2].empty()) {
            opers.push_back({todo[1][0].back() + 1, todo[2][1].back() + 1, 'w', 'i'});
            opers.push_back({todo[2][1].back() + 1, todo[0][2].back() + 1, 'w', 'n'});
            todo[1][0].pop_back();
            todo[2][1].pop_back();
            todo[0][2].pop_back();
        }

        cout << opers.size() << endl;
        for (auto [a1, a2, c1, c2] : opers) cout << a1 << " " << c1 << " " << a2 << " " << c2 << endl;
    }
}