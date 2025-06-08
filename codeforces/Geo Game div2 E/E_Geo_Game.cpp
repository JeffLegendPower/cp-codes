// https://codeforces.com/contest/1903/problem/E

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
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        if (N == -1) return 0;

        int start = 0;
        ll x, y;
        cin >> x >> y;
        start ^= (x % 2) ^ (y % 2);

        vector<int> tsame, tother;
        for (int i = 0; i < N; i++) {
            pll cur;
            cin >> cur.first >> cur.second;

            if (((cur.first % 2) ^ (cur.second % 2)) == start) tsame.push_back(i + 1);
            else tother.push_back(i + 1);
        }

        // if first player, needs to end with same parity as started with
        // if second player, needs to end with other parity as started with
        // so first player gets rid of all other parity, second player gets rid of all same parity

        set<int> used;

        if (tother.size() <= N / 2) {
            cout << "First" << endl;
            
            int otheridx = 0;
            int sameidx = 0;

            while (used.size() < N) {

                while (otheridx < tother.size() && used.find(tother[otheridx]) != used.end()) otheridx++;
                while (sameidx < tsame.size() && used.find(tsame[sameidx]) != used.end()) sameidx++;

                if (otheridx < tother.size()) {
                    cout << tother[otheridx] << endl;
                    used.insert(tother[otheridx]);
                } else if (sameidx < tsame.size()) {
                    cout << tsame[sameidx] << endl;
                    used.insert(tsame[sameidx]);
                }

                if (used.size() == N) break;
                int res;
                cin >> res;
                if (res == -1) return 0;
                used.insert(res);
            }
        } else {
            cout << "Second" << endl;
            
            int otheridx = 0;
            int sameidx = 0;

            int t = 0;
            while (used.size() < N) {
                int res;
                cin >> res;
                if (res == -1) return 0;
                used.insert(res);

                while (otheridx < tother.size() && used.find(tother[otheridx]) != used.end()) otheridx++;
                while (sameidx < tsame.size() && used.find(tsame[sameidx]) != used.end()) sameidx++;

                if (sameidx < tsame.size()) {
                    cout << tsame[sameidx] << endl;
                    used.insert(tsame[sameidx]);
                } else if (otheridx < tother.size()) {
                    cout << tother[otheridx] << endl;
                    used.insert(tother[otheridx]);
                }
            }
        }

        cout << endl;
    }
}