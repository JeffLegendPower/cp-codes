// https://codeforces.com/contest/1856/problem/D

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

        vector<vector<int>> maxidxs;
        maxidxs.push_back({});
        for (int i = 0; i < N; i++) maxidxs[0].push_back(i);

        int idx = 0;
        while (maxidxs.back().size() > 1) {
            maxidxs.push_back({});
            for (int i = 0; i < maxidxs[idx].size() - 1; i += 2) {
                int one = maxidxs[idx][i], two = maxidxs[idx][i + 1];

                if (two - one == 1) {
                    cout << "? " << one + 1 << " " << two + 1 << endl;
                    int res; cin >> res;

                    if (res == 1) maxidxs[idx + 1].push_back(one);
                    else maxidxs[idx + 1].push_back(two);
                    continue;
                }

                cout << "? " << one + 1 << " " << two << endl;
                int res1; cin >> res1;

                cout << "? " << one + 1 << " " << two + 1 << endl;
                int res2; cin >> res2;

                if (res1 == res2) maxidxs[idx + 1].push_back(two);
                else maxidxs[idx + 1].push_back(one);
            }
            if (maxidxs[idx].size() % 2 == 1) maxidxs[idx + 1].push_back(maxidxs[idx].back());

            idx++;
        }

        cout << "! " << maxidxs.back()[0] + 1 << endl;
    }
}