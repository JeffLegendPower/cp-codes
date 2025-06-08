// https://codeforces.com/contest/1994/problem/D

// To solve this problem we need to use the pigeonhole principle
// The pigeonhole principle states that if we have n pigeons and m holes
// where there are more pigeons than holes (n > m), we must have atleast 1 hole
// with > 1 pigeon. While this seems quite stupid, it is actually extremely important
// First we need to notice that for abs(a - b) to be divisble by x, a = b (mod x)
// Secondly, we must notice that under mod x, there are at most x possible remainders
// (0, 1..., x - 2, x - 1). Finally, we need to notice that the order of operations here
// doesn't matter. So we will start by finding a pair divisible by n - 1. This is where the
// pigeonhole principle comes into play. Since we have n values and under (mod n - 1) there are only
// at most n - 1 remainders, there must be atleast 2 values with the same remainder and therefore divisible by n - 1
// Now we can greedily assign the first pair that we find. This is possible because once we assign a pair, we can remove
// (ignore) one of the vertices, and now we have n - 1 values, but we need a pair divisible by n - 2. Again by the pigeonhole
// principle, there is atleast 1 valid pair. This will continue until we have connected all the vertices.

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
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        bool ignore[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            ignore[i] = false;
        }

        pii edges[N - 1];
        for (int x = N - 1; x > 0; x--) {
            map<ll, int> mods;
            for (int i = 0; i < N; i++) {
                if (ignore[i]) continue;

                ll mod = a[i] % x;
                if (mods.find(mod) == mods.end()) {
                    mods[mod] = i;
                    continue;
                }

                edges[x - 1] = {mods[mod], i};
                ignore[i] = true;
                break;
            }
        }

        cout << "YES" << endl;
        for (pii edge : edges) cout << edge.first + 1 << " " << edge.second + 1 << endl;
    }
}