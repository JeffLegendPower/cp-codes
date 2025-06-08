// https://usaco.org/index.php?page=viewproblem2&cpid=1382

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


constexpr ll MOD = 1e9 + 7;
class LazySegtree {
private:
    int N;  // array size
    int h;
    // {a and b, a}
    vector<pll> t;
    // d1 is (b modif), d2 is (a modif)
    vector<ll> d1, d2;

    // k is the length of the segment
    pll calc(pll a, pll b, ll d1, ll d2, int k) {
        // return ((a+b)*d)%MOD;

        return {
            ((((a.first+b.first)*d1)%MOD) * d2)%MOD,
            ((a.second+b.second)*d2)%MOD
        };
    }

    // Update d[p]
    // k is the length of segment
    // void apply(int p, ll value, int k) {
    //     // Update t[p] as if it was already affected by d[p]
    //     t[p] = (t[p] * value)%MOD;
    //     if (p < N) d[p] = (d[p] * value)%MOD;
    // }

    void apply1(int p, ll value, int k) {
        // Update t[p] as if it was already affected by d[p]
        t[p].first = (t[p].first * value)%MOD;
        if (p < N) d1[p] = (d1[p] * value)%MOD;
    } void apply2(int p, ll value, int k) {
        // Update t[p] as if it was already affected by d[p]
        t[p].first = (t[p].first * value)%MOD;
        t[p].second = (t[p].second * value)%MOD;
        if (p < N) d2[p] = (d2[p] * value)%MOD;
    }

public:
    LazySegtree(int size) : N(size), h(sizeof(int) * 8 - __builtin_clz(N)), t(2 * size, {1, 1}), d1(size, 1), d2(size, 1) {}

    void build(int l, int r) {
        int k = 2;
        for (l += N, r += N-1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) t[i] = calc(t[i<<1], t[i<<1|1], d1[i], d2[i], k);
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h-1);
        for (l += N, r += N-1; s > 0; --s, k >>= 1) for (int i = l >> s; i <= r >> s; ++i) {
            if (d1[i] != 1) {
                apply1(i<<1, d1[i], k);
                apply1(i<<1|1, d1[i], k);
                d1[i] = 1;
            } if (d2[i] != 1) {
                apply2(i<<1, d2[i], k);
                apply2(i<<1|1, d2[i], k);
                d2[i] = 1;
            }
        }
    }

    void modify(int l, int r, ll value, bool amod) {
        if (value == 1) return;
        push(l, l + 1);
        push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l&1) {
                if (amod) apply2(l++, value, k);
                else apply1(l++, value, k);
            } if (r&1) {
                if (amod) apply2(--r, value, k);
                else apply1(--r, value, k);
            }
        }
        build(l0, l0 + 1);
        build(r0 - 1, r0);
    }

    ll query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        pll res = {0, 0};
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = calc(res, t[l++], 1, 1, -1);
            if (r&1) res = calc(res, t[--r], 1, 1, -1);
        }
        return res.first - res.second;
    }
};

ll pow2[1000001];

// 500000004 is modinv of 2
ll numdiagsplit(int N, vector<pii>& cows) {
    sort(cows.begin(), cows.end(), [](pii& one, pii &two) {
        return one.second > two.second;
    });

    LazySegtree ab(N), a(N);
    for (int i = 0; i < N; i++) {
        // shift a (bottom left) modifications right 1
        if (cows[i].first+1 < N) ab.modify(cows[i].first+1, N, 2, true);
    }

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        if (cows[i].first+1 < N) ab.modify(cows[i].first+1, N, 500000004, true);

        ans = (ans + ab.query(cows[i].first, N)) % MOD;

        // shift b (top right) modifications left 1
        ab.modify(0, cows[i].first-1+1, 2, false);

        ab.modify(cows[i].first, cows[i].first+1, 0, true);
    }

    return ans;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    pow2[0] = 1;
    for (int i = 1; i < N; i++) pow2[i] = (pow2[i-1]*2ll)%MOD;

    vector<pii> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].first >> cows[i].second;
        cows[i].first--;
        cows[i].second--;
    }

    ll pow2suff[N];
    pow2suff[N-1] = 1;
    for (int j = N-2; j >= 0; j--) {
        pow2suff[j] = (pow2suff[j+1] + pow2[N-1-j])%MOD;
    }

    ll ans = 0;
    for (int i = 0; i < N-1; i++) {
        ll addd = (pow2[i]*pow2suff[i+1])%MOD;
        ans = (ans + addd) % MOD;
    }
    ans = (4ll*ans)%MOD;


    ans = (ans + 2ll*MOD - 2ll*numdiagsplit(N, cows))%MOD;

    for (int i = 0; i < N; i++) cows[i].first = N-1-cows[i].first;
    ans = (ans + 2ll*MOD - 2ll*numdiagsplit(N, cows))%MOD;

    cout << ans;
}