// https://dmoj.ca/problem/ioi05p2

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

#define etry array<ll, 3>

// max prefix sum across range, sum
template <class T, class K>
class LazySegtree {
public:
    int N;  // array size
    int h;
    vector<T> t;
    vector<ll> width;
    vector<K> d;

    T combine(T a, T b) {
        return a + b;
    }

    // k is the length of the segment
    T calc(T a, T b, K d, ll k, K d2) {
        if (d == 1e9 + 1) {
            return {
                max(a[0], a[1] + b[0]),
                a[1] + b[1],
                d2
            };
        }

        return {
            max(0ll, d*k),
            d*k,
            d
        };
    }

    // Update d[p]
    // k is the length of segment
    void apply(int p, K value, ll k) {
        // Update t[p] as if it was already affected by d[p]
        t[p] = {
            max(0ll, value*k),
            value*k,
            value
        };
        if (p < N) d[p] = value;
    }

    LazySegtree(int size, vector<ll> widths) : N(size), h(sizeof(int) * 8 - __builtin_clz(N)), t(2 * size, T()), d(size, 1e9+1), width(2*size, 0) {
        for (int i = 0; i < widths.size(); i++) width[size+i] = widths[i];
    }

    void build(int l, int r) {
        int k = 2;
        for (l += N, r += N-1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) {
                width[i] = width[i<<1] + width[i<<1|1];
                t[i] = calc(t[i<<1], t[i<<1|1], d[i], width[i], t[i][2]);
            }
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h-1);
        for (l += N, r += N-1; s > 0; --s, k >>= 1) for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 1e9+1) {
            apply(i<<1, d[i], width[i<<1]);
            apply(i<<1|1, d[i], width[i<<1|1]);
            d[i] = 1e9+1;
        }
    }

    void modify(int l, int r, K value) {
        if (value == 1e9+1) return;
        push(l, l + 1);
        push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l&1) {
                apply(l, value, width[l]);
                l++;
            } if (r&1) {
                r--;
                apply(r, value, width[r]);
            }
        }
        build(l0, l0 + 1);
        build(r0 - 1, r0);
    }

    T query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        T left = {0, 0, 0}, right = {0, 0, 0};

        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) left = calc(left, t[l++], 1e9+1, -1, -1);
            if (r&1) right = calc(t[--r], right, 1e9+1, -1, -1);
        }
        return calc(left, right, 1e9+1, -1, -1);
    }
};

#define upd array<ll, 4>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    vector<upd> upds;
    while (true) {
        char c; cin >> c;
        if (c == 'E') break;
        if (c == 'I') {
            ll a, b, D;
            cin >> a >> b >> D;
            upds.push_back({c, a, b, D});
        } if (c == 'Q') {
            ll h; cin >> h;
            upds.push_back({c, h, -1, -1});
        }
    }
    int M = upds.size();

    vector<int> nums2;
    nums2.push_back(0);
    for (int i = 0; i < M; i++) {
        if (upds[i][0] == 'Q') continue;
        nums2.push_back(upds[i][1]);
        nums2.push_back(upds[i][2]+1);
    }
    sort(nums2.begin(), nums2.end());

    vector<int> nums;
    map<int, int> idxs;

    int i2 = 0;
    for (int i = 0; i < nums2.size(); i++) {
        if (i > 0 && nums2[i] == nums2[i-1]) continue;
        nums.push_back(nums2[i]);
        idxs[nums2[i]] = i2++;
    }
    
    if (nums.empty()) {
        for (int i = 0; i < M; i++) {
            cout << N << endl;
        }
        return 0;
    }

    vector<ll> widths;
    for (int i = 0; i < nums.size()-1; i++) widths.push_back(nums[i+1]-nums[i]);
    widths.push_back(N-nums.back());

    int K = nums.size();

    LazySegtree<etry, ll> seggy(K > 1 ? 1ll << (64 - __builtin_clzll(K - 1)) : 1, widths);
    int len = K > 1 ? 1ll << (64 - __builtin_clzll(K - 1)) : 1;
    seggy.build(0, len);

    for (int i = 0; i < M; i++) {
        if (upds[i][0] == 'Q') {
            ll h = upds[i][1];
            int low = 0, high = K;
            int best = 1;
            while (low <= high) {
                int mid = low+(high-low)/2;
                ll qry = seggy.query(0, mid)[0];
                if (qry > h) {
                    best = mid;
                    high = mid - 1;
                } else low = mid + 1;
            }

            ll idx = nums[best-1]-1;
            ll height = seggy.query(0, best-1)[1];
            seggy.push(best-1, best);

            ll slope = seggy.t[len+best-1][2];

            if (slope == 0) {
                cout << N << endl;
                continue;
            }
            
            cout << min((ll)N, (idx + (h - height)/slope)) << endl;


            continue;
        }

        int l = upds[i][1], r = upds[i][2] + 1;
        int D = upds[i][3];
        l = idxs[l], r = idxs[r];
        seggy.modify(l, r, D);
    }
}