// https://usaco.org/index.php?page=viewproblem2&cpid=1302

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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

struct frnd {
    ll a, b, t;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        ll N, tc, tm;

        frnd friends[N];
        for (int i = 0; i < N; i++) cin >> friends[i].a >> friends[i].b >> friends[i].t

        pll mintctm = {1e9, 1e9};

        ll low = 1, high = tc + tm;
        while (low <= high) {
            ll mid = low + (high - low) / 2;

            ll tmneeded = 1e9;

            ll maxtc = = tc;
            pll tcbounds = {1, tc};
            pll tmbounds = {1, tm};
            ll mintm = 1;
            bool possible = true;
            
            for (frnd i : friends) {
                if (i.b < i.a) {
                    ll x = i.a - i.b;
                    ll right = i.t - i.b * mid;
                    ll res = floor(right / (double) x);
                    if (res <= 0) {
                        possible = false;
                        break;
                    }
                    tcbounds.second = min(tcbounds.second, res);
                    

                    if (!((res < 0) ^ (x < 0))) {
                        
                    }
                }
            }


            for (frnd i : friends) {
                ll lowtm = 1, hightm = min(mid - 1, tm);
                ll besttm = 1e9;
                while (lowtm <= hightm) {
                    ll midtm = lowtm + (hightm - lowtm) / 2;
                    if (mid - midtm > tc) {
                        lowtm = midtm + 1;
                        continue;
                    }
                    ll midtc = mid - midtm;
                    if (midtc * i.a + midtm * i.b <= i.t) {
                        hightm = midtm - 1;
                        besttm = min(besttm, midtm);
                    }
                }
            }
        }
    }
}