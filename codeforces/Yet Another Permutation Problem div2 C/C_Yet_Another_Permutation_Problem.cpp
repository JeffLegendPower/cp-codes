// https://codeforces.com/contest/1858/problem/C

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
    bool operator() (int a, int b) {
        return a < b;
    }
};

typedef tree<int, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        ordered_set oset;
        for (int i = 1; i <= N; i++) oset.insert(i);

        vector<int> p;
        while (oset.size() > 0) {
            // int start = *oset.find_by_order(0);
            // p.insert(start);

            for (int i = *oset.find_by_order(0); i <= N; i <<= 1) {
                p.push_back(i);
                oset.erase(i);
            }
        }

        for (int i = 0; i < N; i++) cout << p[i] << " ";
        cout << endl;
    }
}