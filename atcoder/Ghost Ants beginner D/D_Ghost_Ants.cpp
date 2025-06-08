// https://atcoder.jp/contests/abc360/tasks/abc360_d

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

struct ant {
    // true = right, false = left
    bool dir;
    ll x;
};

int main() {
    int N;
    ll T;
    cin >> N >> T;
    string s;
    cin >> s;

    ant ants[N];
    FOR(i, 0, N) {
        ants[i].dir = s[i] - '0';
    } FOR(i, 0, N) {
        cin >> ants[i].x;
    }
    sort(ants, ants + N, [](ant one, ant two) {
        return one.x < two.x;
    });

    ll combos = 0;

    int preLeft[N + 1], preRight[N + 1];
    preLeft[0] = 0, preRight[0] = 0;
    FOR(i, 0, N) {
        preLeft[i + 1] = preLeft[i];
        preRight[i + 1] = preRight[i];
        if (ants[i].dir) preRight[i + 1]++;
        else preLeft[i + 1]++;
    } FOR(i, 0, N) {

        if (ants[i].dir) {
            int low = i + 1, high = N - 1;
            ll most = T * 2 + ants[i].x;
            int best = i;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                ll cur = ants[mid].x;
                if (cur <= most) {
                    low = mid + 1;
                    best = max(best, mid);
                } else high = mid - 1;
            }
            combos += preLeft[best + 1] - preLeft[i + 1];
        }
    }

    cout << combos;
}