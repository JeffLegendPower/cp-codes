// https://codeforces.com/contest/1914/problem/G1

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
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int c[2*N];
        for (int i = 0; i < 2*N; i++) cin >> c[i];

        // number of "minimal closed segments" as described in the editorial
        vector<pii> segs;
        set<int> nums;
        int segidx = 0;

        segs.push_back({0, 0});
        nums.insert(c[0]);
        for (int i = 1; i < 2*N; i++) {
            int cur = c[i];
            if (nums.find(cur) == nums.end()) nums.insert(cur);
            else nums.erase(cur);

            if (nums.size() == 0) {
                segs[segidx].second = i;
                segidx++;
                segs.push_back({i + 1, i + 1});
            }
        }
        segs.pop_back();

        cout << segs.size() << " ";

        ll MOD = 998244353;

        ll ways = 1;
        for (pii seg : segs) {
            int cnt = seg.second - seg.first + 1;

            for (int i = seg.first + 1; i < seg.second; i++) {
                set<int> segnums;
                for (int j = i; j <= seg.second; j++) {
                    if (segnums.find(c[j - 1]) == segnums.end()) segnums.insert(c[j - 1]);
                    else segnums.erase(c[j - 1]);

                    if (segnums.size() == 0) {
                        cnt -= j - i + 1;
                        i = j;
                        break;
                    }
                }
            }

            ways = (ways * cnt) % MOD;
        }

        cout << ways << endl;
    }
}