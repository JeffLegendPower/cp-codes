// https://codeforces.com/contest/1829/problem/G

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

    vector<vector<ll>> pres;
        int row = 0;
        int diff = 1;
        ll num = 1;
        for (int diff = 1; diff <= 2023; diff++) {
            pres.push_back({});
            pres[diff - 1].push_back(0);
            for (int i = 0; i < diff; i++) {
                pres[diff - 1].push_back(num * num + pres[diff - 1].back());
                // cout << diff << " " << pres[diff - 1].back() << endl;
                num++;
            }
        }

    while (T--) {
        ll N;
        cin >> N;

        ll diff2 = 1;
        ll num2 = 0;
        while (num2 < N) {
            num2 += diff2++;
        }
        diff2--;

        // cout << diff2 << " " << endl;

        ll total = 0;
        ll startidx = diff2 - (num2 - N) - 1;
        ll endidx = diff2 - (num2 - N);
        // cout << endidx << " " << diff2 << " " << pres[diff2 - 1][endidx] << " " << pres[diff2 - 1][startidx - 1] << endl;
        while (diff2 > 0) {
            // int startidx = diff2 - (num2 - N);
            total += pres[diff2 - 1][endidx] - pres[diff2 - 1][startidx];
            // cout << endidx << " " << startidx << endl;

            N -= diff2;
            num2 -= diff2;
            diff2--;
            endidx = min(endidx, diff2);
            startidx = max(startidx - 1, 0ll);

            // cout << total << endl;
        }

        // cout << num2 << " " << diff2 << endl;
        cout << total << endl;
    }
}