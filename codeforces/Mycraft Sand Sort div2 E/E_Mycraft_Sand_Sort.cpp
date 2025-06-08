// https://codeforces.com/contest/2064/problem/E

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

class Segtree {
private:
    int N;  // array size
    vector<int> t;

    int combine(int a, int b) {
        return max(a, b);
    }

public:
    Segtree(int size) : N(size), t(2 * size, 0) {}

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, int value) {  // Set value at position p
        for (t[p += N] = value; p > 1; p >>= 1) 
            t[p >> 1] = combine(t[p], t[p^1]);
    }

    int query(int l, int r) {  // Query on interval [l, r)
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = combine(res, t[l++]);
            if (r&1) res = combine(res, t[--r]);
        }
        return res;
    }
};

ll MOD = 998244353;

class DSU {
    public:
        vector<int> parents;
        vector<int> sizes;
        vector<int> old;

        DSU(int size) : parents(size), sizes(size, 1), old(size, 0) {
            for (int i = 0; i < size; i++) { parents[i] = i; }
        }
    
        /** @return the "representative" node in x's component */
        int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }
    
        /** @return whether the merge changed connectivity */
        bool unite(int x, int y) {
            int x_root = find(x);
            int y_root = find(y);
            if (x_root == y_root) { return false; }
    
            if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
            sizes[x_root] += sizes[y_root];
            old[x_root] += old[y_root];
            parents[y_root] = x_root;
            return true;
        }
    
        /** @return whether x and y are in the same connected component */
        bool connected(int x, int y) { return find(x) == find(y); }

        void addold(int x) {
            old[find(x)]++;
        } int getold(int x) {
            return old[find(x)];
        }
};

// u, v, t
#define edg array<int, 3>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;

        Segtree maxseg(N);
        int p[N], p2[N+1];
        for (int i = 0; i < N; i++) {
            cin >> p[i];
            p2[p[i]] = i;
            maxseg.modify(i, p[i]);
        }


        int c[N]; for (int i = 0; i < N; i++) cin >> c[i];

        vector<edg> edges;
        vector<int> lastc(N+1, -1);
        for (int i = 0; i < N; i++) {
            if (lastc[c[i]] != -1) edges.push_back({i, lastc[c[i]], maxseg.query(lastc[c[i]]+1, i)});
            lastc[c[i]] = i;
        }

        sort(edges.begin(), edges.end(), [](edg one, edg two) {
            return one[2] < two[2];
        });
        
        DSU dsu(N);
        ll ways = 1;
        int ei = 0;
        for (int i = 1; i < N; i++) {
            while (ei < edges.size() && edges[ei][2] <= i) {
                dsu.unite(edges[ei][0], edges[ei][1]);
                ei++;
            }

            ways = (ways * ((ll) dsu.sizes[dsu.find(p2[i])] - dsu.getold(p2[i]))) % MOD;

            dsu.addold(p2[i]);
        }

        cout << ways << endl;
    }
}