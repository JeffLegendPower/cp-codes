// https://codeforces.com/contest/1729/problem/F

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
        string s;
        cin >> s;

        int N = s.size();

        int pres[N + 1];
        pres[0] = 0;
        for (int i = 0; i < N; i++) {
            pres[i + 1] = pres[i] + s[i] - '0';
        }

        int w, M;
        cin >> w >> M;

        // start idx of substrings which = i (mod 9)
        vector<int> Ls[9];
        int summ = 0;
        for (int i = 0; i < w; i++) summ += s[i] - '0';
        Ls[summ % 9].push_back(0);

        for (int i = 1; i < N - w + 1; i++) {
            summ -= s[i - 1] - '0';
            summ += s[i + w - 1] - '0';
            Ls[summ % 9].push_back(i);
        }

        while (M--) {
            int l, r, k;
            cin >> l >> r >> k;
            int modd = (pres[r] - pres[l - 1]) % 9;
            // cout << pres[r] - pres[l - 1] << endl;

            int L1 = 1e6, L2 = 1e6;
            for (int mod1 = 0; mod1 < 9; mod1++) {
                if (Ls[mod1].size() == 0) continue;
                int mod2 = ((72 + k - mod1 * modd) % 9);
                if (Ls[mod2].size() == 0) continue;
                if (mod2 == mod1 && Ls[mod2].size() == 1) continue;
                // cout << mod1 << " " << modd << " " << mod2 << endl;
                int l1 = Ls[mod1][0];
                int l2 = Ls[mod2][mod2 == mod1 ? 1 : 0];
                if (l1 < L1) {
                    L1 = l1;
                    L2 = l2;
                } else if (l1 == L1 && l2 < L2) {
                    L1 = l1;
                    L2 = l2;
                }
            }

            if (L1 == 1e6) cout << "-1 -1";
            else cout << L1 + 1 << " " << L2 + 1;
            cout << endl;
        }
    }
}