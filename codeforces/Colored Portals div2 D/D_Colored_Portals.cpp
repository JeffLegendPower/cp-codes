// https://mirror.codeforces.com/contest/2004/problem/D

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
        int N, Q;
        cin >> N >> Q;

        // vector<int> possible[6];
        map<string, int> portals;
        portals["BG"] = 0;
        portals["BR"] = 1;
        portals["BY"] = 2;
        portals["GR"] = 3;
        portals["GY"] = 4;
        portals["RY"] = 5;
        
        portals["GB"] = 0;
        portals["RB"] = 1;
        portals["YB"] = 2;
        portals["RG"] = 3;
        portals["YG"] = 4;
        portals["YR"] = 5;

        vector<int> nodes;
        vector<string> nodes2;

        set<int> next1[6];
        set<int, greater<int>> next2[6];

        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            sort(s.begin(), s.end());
            nodes.push_back(portals[s]);
            nodes2.push_back(s);

            // possible[portals[s]].push_back(i);
            next1[portals[s]].insert(i);
            next2[portals[s]].insert(i);
        }

        while (Q--) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            int low = min(u, v);
            int high = max(u, v);
            u = low;
            v = high;

            string s1 = nodes2[u];
            string s2 = nodes2[v];
            if (s1[0] == s2[0] || s1[1] == s2[1]) {
                cout << abs(u - v) << endl;
                continue;
            }

            int mincost = 1e6;

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    string x = "";
                    x += s1[i];
                    x += s2[j];
                    int num = portals[x];

                    auto first = next1[num].upper_bound(u);
                    if (first != next1[num].end()) {
                        int val = *first;
                        mincost = min(mincost, abs(val - u) + abs(v - val));
                    }

                    auto second = next2[num].upper_bound(u);
                    if (second != next2[num].end()) {
                        int val = *second;
                        mincost = min(mincost, abs(val - u) + abs(val - v));
                    }
                }
            }

            if (mincost == 1e6) cout << -1 << endl;
            else cout << mincost << endl;
        }
    }
}