// https://mirror.codeforces.com/contest/2001/problem/C

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
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<pii> edges;

        vector<bool> connected(N, false);
        vector<set<int>> next(N);
        connected[0] = true;
        int numconnected = 1;

        int queries = 0;
        // for (int i = 0; i < N; i++) {
        while (numconnected < N) {
            // if (!connected[i]) continue;
            int a = 0;

            int b = 0;
            while (b < N && connected[b]) b++;

            // if (b >= N) break;

            int low = a, high = b;
            while (low != b) {
                while (true) {
                    if (next[low].find(high) != next[low].end()) {
                        low = high;
                        high = b;
                        break;
                    }

                    // queries++;
                    // if (queries > 15*N) return 0;
                    cout << "? " << low + 1 << " " << high + 1 << endl;
                    cout.flush();

                    int res;
                    cin >> res;
                    if (res == (low + 1)) {
                        connected[high] = true;
                        numconnected++;
                        edges.push_back({low, high});
                        next[low].insert(high);
                        next[high].insert(low);
                        low = high;
                        high = b;
                        break;
                    } else {
                        if (connected[res - 1]) low = res - 1;
                        else high = res - 1;
                    }
                }
            }
        }

        cout << "! ";
        for (pii edge : edges) cout << edge.first + 1 << " " << edge.second + 1 << " ";
        cout << endl;
        cout.flush();
    }
}