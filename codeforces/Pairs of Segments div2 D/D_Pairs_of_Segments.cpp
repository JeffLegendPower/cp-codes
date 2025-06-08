// https://codeforces.com/contest/1841/problem/D

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

bool intersects(pll& one, pll& two) {
    return max(one.first, two.first) <= min(one.second, two.second);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        pll pairs[N];
        for (int i = 0; i < N; i++) cin >> pairs[i].first >> pairs[i].second;

        vector<pll> pairs2;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (intersects(pairs[i], pairs[j])) 
                    pairs2.push_back({min(pairs[i].first, pairs[j].first), max(pairs[i].second, pairs[j].second)});
            }
        }

        sort(pairs2.begin(), pairs2.end(), [](pll one, pll two) {
            return one.second < two.second;
        });

        int numans = 0;
        pll cur = {-1, -1};
        
        for (pll pair : pairs2) {
            if (!intersects(pair, cur)) {
                numans += 2;
                cur = pair;
            }
        }

        cout << N - numans << end
    }
}