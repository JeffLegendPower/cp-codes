// https://usaco.org/index.php?page=viewproblem2&cpid=1403&lang=en

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

struct prt {
    ll p, s;
    int i;

    ll t;
};
// mootrino, antimootrino pair
// (NOTE CANT BE OTHER WAY AROUND)
#define pprt pair<prt, prt>

ll calctime(pprt x) {
    ll s = x.first.s + x.second.s;
    ll d = abs(x.first.p - x.second.p);
    ll t = 2 * ((d + s - 1) / (s));
    // cout << s << " " << d << endl;
    if (x.first.p < x.second.p) t--;

    return t;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;

        prt parts[N];
        for (int i = 0; i < N; i++) cin >> parts[i].p;
        for (int i = 0; i < N; i++) cin >> parts[i].s;
        for (int i = 0; i < N; i++) parts[i].i = i;

        set<int> odd1, even1;
        set<int, greater<int>> odd2, even2;
        for (int i = 0; i < N; i += 2) {
            even1.insert(i);
            even2.insert(i);
        } for (int i = 1; i < N; i += 2) {
            odd1.insert(i);
            odd2.insert(i);
        }

        vector<ll> times(N, -1);

        auto cmp = [](pprt one, pprt two) {
            ll s1 = one.first.s + one.second.s;
            ll d1 = abs(one.first.p - one.second.p);
            ll t1 = 2 * ((d1 + s1 - 1) / (s1));
            if (one.first.p < one.second.p) t1--;

            ll s2 = two.first.s + two.second.s;
            ll d2 = abs(two.first.p - two.second.p);
            ll t2 = 2 * ((d2 + s2 - 1) / (s2));
            if (two.first.p < two.second.p) t2--;

            return t1 > t2;
        };

        priority_queue<pprt, vector<pprt>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < N; i += 2) {
            pq.push({parts[i], parts[i + 1]});
            if (i > 0) pq.push({parts[i], parts[i - 1]});
        }

        // cout << calctime({parts[2], parts[1]}) << endl;

        while (!pq.empty()) {
            auto [one, two] = pq.top();
            pq.pop();
            if (times[one.i] != -1 || times[two.i] != -1) continue;
            // cout << one.i << "   " << two.i << endl;

            times[one.i] = calctime({one, two});
            times[two.i] = calctime({one, two});

            even1.erase(one.i);
            even2.erase(one.i);
            odd1.erase(two.i);
            odd2.erase(two.i);

            if (one.i < two.i) {
                auto left = odd2.upper_bound(one.i);
                auto right = even1.upper_bound(two.i);
                if (left == odd2.end() || right == even1.end()) continue;
                pq.push({parts[*right], parts[*left]});
            } else {
                auto left = even2.upper_bound(two.i);
                auto right = odd1.upper_bound(one.i);
                if (left == even2.end() || right == odd1.end()) continue;
                pq.push({parts[*left], parts[*right]});
            }
        }

        for (int i = 0; i < N; i++) {
            cout << times[i];
            if (i < N - 1) cout << " ";
        }
        if (T > 0) cout << endl;
    }
}