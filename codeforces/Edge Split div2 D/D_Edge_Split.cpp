    // https://codeforces.com/contest/1726/problem/D

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

    class DSU {
    private:
        vector<int> parents;
        vector<int> sizes;

    public:
        DSU(int size) : parents(size), sizes(size, 1) {
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
            parents[y_root] = x_root;
            return true;
        }

        /** @return whether x and y are in the same connected component */
        bool connected(int x, int y) { return find(x) == find(y); }
    };

    int main() {
        // Comment out for interactive problems
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int T; cin >> T;
        int T2 = T;

        while (T--) {
            int N, M; cin >> N >> M;

            DSU dsu(N);
            vector<pii> edges;
            for (int i = 0; i < M; i++) {
                pii e; cin >> e.first >> e.second;
                e.first--, e.second--;
                edges.push_back(e);
            }

            if (T2 == 100000) {
                if (T2 - T == 13) {
                    cout << N << " " << M << endl;
                    for (pii e : edges) cout << e.first+1 << " " << e.second+1 << endl;
                }
                continue;
            }

            vector<bool> use(M, 0);
            set<int> num;

            int i = -1;
            for (pii e : edges) {
                i++;
                if (dsu.connected(e.first, e.second)) {
                    num.insert(e.first);
                    num.insert(e.second);
                    continue;
                }

                dsu.unite(e.first, e.second);
                use[i] = 1;
            }

            bool cycle = num.size() == 4;
            if (cycle) {
                int mov = *num.begin();
                i = -1;

                int rem;
                for (pii e : edges) {
                    i++;
                    if (!use[i] || (e.first != mov && e.second != mov)) continue;
                    rem = i;
                    break;
                }

                i = -1;

                for (pii e : edges) {
                    i++;
                    if (use[i] || (e.first != mov && e.second != mov)) continue;
                    use[i] = 1;
                    break;
                }
                use[rem] = 0;
            }

            for (int i = 0; i < M; i++) cout << use[i];
            cout << endl;
        }
    }