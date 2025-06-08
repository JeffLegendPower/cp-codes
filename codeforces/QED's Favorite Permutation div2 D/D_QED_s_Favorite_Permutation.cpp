// https://codeforces.com/contest/2030/problem/D

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
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
        int N, Q;
        cin >> N >> Q;

        int p[N];
        for (int i = 0; i < N; i++) cin >> p[i];

        vector<bool> move(N, false);
        int least = 1e6;
        for (int i = N - 1; i >= 0; i--) {
            least = min(least, p[i]);
            if (least < (i + 1)) move[i] = true;
        }

        vector<int> num(N, 0);
        int satis = 0;
        string s; cin >> s;
        for (int i = 0; i < N; i++) {
            if (s[i] == 'L') num[i]++;
            else num[i + 1]++;

            if (!move[i] || num[i] > 0) satis++;
        }

        while (Q--) {
            int i; cin >> i;
            i--;
            if (s[i] == 'L') {
                if (move[i] && num[i] == 1) satis--;
                if (move[i + 1] && num[i + 1] == 0) satis++;

                num[i]--;
                num[i + 1]++;
                s[i] = 'R';
            } else {
                if (move[i + 1] && num[i + 1] == 1) satis--;
                if (move[i] && num[i] == 0) satis++;

                num[i + 1]--;
                num[i]++;
                s[i] = 'L';
            }
            cout << (satis == N ? "YES" : "NO") << endl;
        }
    }
}