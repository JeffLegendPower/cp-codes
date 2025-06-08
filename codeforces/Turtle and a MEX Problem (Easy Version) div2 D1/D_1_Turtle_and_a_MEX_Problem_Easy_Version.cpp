// https://codeforces.com/contest/2003/problem/D1

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

// struct node {
//     bool searched = false;
//     vector<int> next;
    
//     ll val;
//     ll dpval;

//     // set x to first number, BUT if x is already = to first number set x to second number
//     pll puv;
// };
// vector<node> graph;


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        ll M;
        cin >> N >> M;

        // graph.clear();

        ll best = 0;

        for (int i = 0; i < N; i++) {
            int l;
            cin >> l;

            int a[l];
            for (int j = 0; j < l; j++) cin >> a[j];

            sort(a, a + l);

            ll mex = 0;
            pll cur = {-1, -1};
            for (int j = 0; j < l; j++) {
                if (a[j] == mex) mex++;
                else if (a[j] > mex) {
                    if (cur.first == -1) {
                        cur.first = mex;
                        mex++;
                        if (a[j] == mex) mex++;
                    } else if (cur.second == -1) {
                        cur.second = mex;
                        break;
                    }
                }
            }

            if (cur.first == -1) {
                cur = {mex, mex + 1};
            } else if (cur.second == -1) {
                cur.second = mex;
            }

            best = max(best, cur.second);

            // node nod;
            // nod.puv = cur;
            // nod.val = cur.second;
            // graph.push_back(nod);
        }

        ll total = 0;
        total += best * (min(best, M) + 1);

        // cout << 

        ll start = best + 1;
        ll cnt = max(0ll, M - best);

        total += cnt * (start + start + cnt - 1) / 2;

        cout << total << endl;
    }
}