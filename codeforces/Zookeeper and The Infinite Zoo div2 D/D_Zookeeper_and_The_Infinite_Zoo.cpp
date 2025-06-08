// https://codeforces.com/contest/1491/problem/D

// Condition: We can move from vertex a to vertex a+b if a&b == b
// So we can't move from vertex u to v if v < u so let's account for that first
// Now for the condition. By looking at the binary representation of a
// b must have some subset of those bits set to pass the condition
// This means some things:
// First, a+b will have at most the same number of bits that a has, we can never set another bit
// But a+b can have less bits than a, as if a has 2 consecutive bits and b has the first one set, a will
// only have 1 of those 2 bits by the end of it
// Second, when moving from a to a+b, each bit can either stay in the same place or shift up, they can never shift down
// So now we can iterate from the least significant to the most significant bits of u and v
// If ever v has more significant bits than u, a path doesn't exist as we can't satisfy those bits of v as there's not enough
// bits of u behind or at those positions
// Second, if u has more bits than v, we can always collapse them onto the most significant bit of v so they will have the same # of bits
// Since we only have to iterate through the binary representation of u and v,
// this takes O(log(max(u, v))) time (but really O(30))

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
        ll u, v;
        cin >> u >> v;

        if (u > v) {
            cout << "NO" << endl;
            continue;
        }

        bool works = true;
        int set = 0;
        for (int i = 0; i < 30; i++) {
            if ((u & (1ll << i)) > 0) set++;
            if ((v & (1ll << i)) > 0) set--;

            if (set < 0) works = false;
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}