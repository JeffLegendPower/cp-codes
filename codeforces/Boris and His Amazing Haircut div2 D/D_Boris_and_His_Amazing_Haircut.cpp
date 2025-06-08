// https://codeforces.com/contest/1779/problem/D

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
    bool operator() (ll a, ll b) {
        return a < b;
    }
};

typedef tree<ll, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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
    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N;

        ll a[N], b[N];
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int i = 0; i < N; i++) cin >> b[i];

        cin >> M;
        map<ll, int> x;
        for (int i = 0; i < M; i++) {
            ll xi;
            cin >> xi;
            x[xi]++;
        }

        map<ll, int> needed;
        ordered_set cur;
        // cur.insert(1);

        // if (cur.find(1) == cur.end()) cout << "E";

        bool possible = true;
        for (int i = 0; i < N; i++) {
            if (a[i] < b[i]) {
                possible = false;
                break;
            } 
            // else if (a[i] == b[i]) continue;
            bool remove = false;
            if (cur.find(b[i]) == cur.end()) {
                if (a[i] != b[i]) needed[b[i]]++;
                else remove = true;
                cur.insert(b[i]);
            }

            ll curval = *(cur.find_by_order(0));
            while (curval < b[i]) {
                cur.erase(curval);
                curval = *(cur.find_by_order(0));
            }
            if (remove) {
                cur.erase(curval);
            }
        }

        for (auto itr = needed.begin(); itr != needed.end(); itr++) {
            if (x[itr->first] < (itr->second)) possible = false;
        }

        // cout << needed

        if (!possible) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}