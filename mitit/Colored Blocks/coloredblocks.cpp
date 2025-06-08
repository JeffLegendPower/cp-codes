// https://mitit.org/Contest/ViewProblem/colored-blocks?cid=advanced2-2025

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


class Segtree {
private:
    int N;  // array size
    vector<int> t;

public:
    Segtree(int size) : N(size), t(2 * size, 0ll) {}

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = t[i<<1] + t[i<<1|1];
    }

    void modify(int l, int r, int value) {
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) t[l++] += value;
            if (r&1) t[--r] += value;
        }
    }

    int query(int p) {
        ll res = 0;
        for (p += N; p > 0; p >>= 1) res += t[p];
        return res;
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;

        ll a[N];
        map<ll, int> mapp;
        int cntr = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (mapp.find(a[i]) == mapp.end()) mapp[a[i]] = cntr++;
        }

        for (int i = 0; i < N; i++) a[i] = mapp[a[i]];

        Segtree seggy(N);

        int k = 0;
        vector<int> cnts(N, 0);
        for (int i = 0; i < N; i++) {
            seggy.modify(a[i], a[i]+1, max(0, -seggy.query(a[i])));

            seggy.modify(a[i], a[i]+1, 2);
            seggy.modify(0, N, -1);
            k = max(k, seggy.query(a[i]));


            cnts[a[i]]++;
        }
        

        cout << k << endl;
        for (int i = 0; i < k-1; i++) cout << "1 " << i+1 << endl;
        cout << (N - (k-1)) << " ";
        for (int i = k-1; i < N; i++) cout << i+1 << " ";
        cout << endl;
    }
}