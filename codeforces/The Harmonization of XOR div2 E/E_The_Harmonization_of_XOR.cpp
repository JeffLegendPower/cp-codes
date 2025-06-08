// https://codeforces.com/contest/1787/problem/E

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
        int N, k;
        cin >> N >> k;
        ll x;
        cin >> x;

        int a[N];
        for (int i = 0; i < N; i++) a[i] = i + 1;

        vector<vector<ll>> subseqs;
        set<int> used;
        if (x <= N) {
            used.insert(x);
            subseqs.push_back({x});
        }

        for (int i = 0; i < N; i++) {
            ll one = i + 1;
            ll two = one ^ x;
            if (two <= N && used.find(one) == used.end() && used.find(two) == used.end()) {
                used.insert(one);
                used.insert(two);
                vector<ll> cur;
                cur.push_back(one);
                cur.push_back(two);
                subseqs.push_back(cur);
            }
        }
        
        ll last = 0;
        vector<ll> lastsubseq;
        for (int i = 0; i < N; i++) {
            if (used.find(i + 1) != used.end()) continue;
            last ^= (i + 1);
            lastsubseq.push_back(i + 1);
        }

        if (last == x) {
            subseqs.push_back(lastsubseq);
        } else if (last == 0 && subseqs.size() > 0) {
            for (ll ele : lastsubseq) subseqs.back().push_back(ele);
        } else {
            cout << "NO" << endl;
            continue;
        }

        if (subseqs.size() < k || (subseqs.size() - k) % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;

        int tocombine = subseqs.size() - k;
        vector<ll> combined;
        for (int i = 0; i <= tocombine; i++) {
            for (ll ele : subseqs[i]) {
                combined.push_back(ele);
            }
        }

        cout << combined.size() << " ";
        for (ll ele : combined) cout << ele << " ";
        cout << endl;

        for (int i = tocombine + 1; i < subseqs.size(); i++) {
            cout << subseqs[i].size() << " ";
            for (ll ele : subseqs[i]) cout << ele << " ";
            cout << endl;
        }
    }
}