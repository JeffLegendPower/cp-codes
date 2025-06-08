// https://usaco.org/index.php?page=viewproblem2&cpid=577

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

template <class T>
class Segtree {
public:
    int N;  // array size
    vector<T> t;

    T combine(T a, T b) {
        return {min(a.first, a.second + b.first), a.second + b.second};
    }

    Segtree(int size) : N(size), t(2 * size, T()) {}

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, int val) {  // Set value at position p
        p += N;
        t[p].first += val;
        t[p].second += val;
        for (; p > 1; p >>= 1) {
            p |= 1;
            t[p >> 1] = combine(t[p^1], t[p]);
        }
    }

    T query(int l, int r) {  // Query on interval [l, r)
        T left = T(), right = T();
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) left = combine(left, t[l++]);
            if (r&1) right = combine(t[--r], right);
        }
        return combine(left, right);
    }

    int minpre() {
        int p = 1;
        while (p < N) {
            int l = p<<1, r = p<<1|1;
            p <<= 1;

            if (t[l].first > t[l].second + t[r].first) p |= 1;
        }

        p -= N;
        return query(0, p+1).first;
    }
};

void solve(int N, vector<int> &bessie, vector<int> &elsie, vector<int> &res) {
    int siz = 1 << (32 - __builtin_clz(N - 1));
    Segtree<pii> seg(siz);

    vector<int> elsiepos(2*N + 1, -1);
    vector<int> elsie2(elsie);
    sort(elsie2.begin(), elsie2.end(), greater<int>());
    
    for (int i = 0; i < N; i++) elsiepos[elsie2[i]] = i;

    int l = 0;
    for (int i = 0; i < N; i++) {
        seg.modify(elsiepos[elsie[i]], -1);
        while (l < N && bessie[i] < elsie2[l]) l++;
        if (l < N) seg.modify(l, 1);

        res[i] = i+1 + min(0, seg.minpre());
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("cardgame");

    int N; cin >> N;

    vector<int> elsie(N);
    vector<bool> bessieB(2*N + 1, true);
    bessieB[0] = false;

    for (int i = 0; i < N; i++) {
        cin >> elsie[i];
        bessieB[elsie[i]] = false;
    }

    vector<int> bessie;
    for (int i = 2*N; i >= 1; i--) {
        if (bessieB[i]) bessie.push_back(i);
    }

    vector<int> left(N), right(N);
    solve(N, bessie, elsie, left);

    reverse(bessie.begin(), bessie.end());
    for (int i = 0; i < N; i++) bessie[i] = 2*N + 1 - bessie[i];

    reverse(elsie.begin(), elsie.end());
    for (int i = 0; i < N; i++) elsie[i] = 2*N + 1 - elsie[i];

    solve(N, bessie, elsie, right);
    reverse(right.begin(), right.end());

    int best = max(left[N-1], right[0]);
    for (int i = 0; i < N-1; i++) {
        best = max(best, left[i] + right[i+1]);
    }

    cout << best;
}