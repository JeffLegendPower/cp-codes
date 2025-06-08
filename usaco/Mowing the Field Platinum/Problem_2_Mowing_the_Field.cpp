// https://usaco.org/index.php?page=viewproblem2&cpid=601

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

// Segtree for time
class Segtree {
private:
    int N;  // array size
    vector<int> t;
    

public:
    vector<int> times;
    map<int, int> timemap;
    Segtree(int size, vector<int> times2) : N(size), t(2 * size, 0) {
        times = vector<int>(times2);
        for (int i = 0; i < size; i++) timemap[times[i]] = i;
    }

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = t[i<<1] + t[i<<1|1];
    }

    void modify(int p, int value) {  // Set value at position p
        p = timemap[p];
        for (t[p += N] += value; p > 1; p >>= 1) 
            t[p >> 1] = t[p] + t[p^1];
    }

    int query(int l, int r) {  // Query on interval [l, r)
        l = timemap[l], r = timemap[r]+1;

        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }
};

// Segtree for y
class Segtree2 {
private:
    int N;  // array size
    vector<Segtree> t;

    Segtree combine(Segtree a, Segtree b) {
        // return a + b;
        vector<int> times;
        times.reserve(a.times.size() + b.times.size());
        times.insert(times.end(), a.times.begin(), a.times.end());
        times.insert(times.end(), b.times.begin(), b.times.end());
        sort(times.begin(), times.end());

        return Segtree(times.size(), times);
    }

public:
    Segtree2(int size, vector<vector<int>> times) : N(size) {
        t.resize(2*size, Segtree(0, {}));
        for (int i = 0; i < size; i++) {
            t[size + i] = Segtree(times[i].size(), times[i]);
        }
    }

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, int time, int amt) {  // Set value at position p
    p += N;
    t[p].modify(time, amt);
        for (; p > 1; p >>= 1) {
            t[p>>1].modify(time, amt);
        }
    }

    int query(int l, int r, int time, int T) {  // Query on interval [l, r)
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) {
                int left = time - T;
                auto itr = upper_bound(t[l].times.begin(), t[l].times.end(), left);
                if (itr != t[l].times.begin()) res += t[l].query(*t[l].times.begin(), *(--itr));

                int right = time+T;
                auto itr2 = lower_bound(t[l].times.begin(), t[l].times.end(), right);
                if (itr2 != t[l].times.end()) res += t[l].query(*itr2, *t[l].times.rbegin());

                l++;
            } if (r&1) {
                r--;
                
                int left = time - T;
                auto itr = upper_bound(t[r].times.begin(), t[r].times.end(), left);
                if (itr != t[r].times.begin()) res += t[r].query(*t[r].times.begin(), *(--itr));

                int right = time+T;
                auto itr2 = lower_bound(t[r].times.begin(), t[r].times.end(), right);
                if (itr2 != t[r].times.end()) res += t[r].query(*itr2, *t[r].times.rbegin());
            }
        }
        return res;
    }
};

// # startx, starty, endx, endy, time
#define path array<ll, 5>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    setIO("mowing");

    int N, T;
    cin >> N >> T;

    path paths[N-1];
    vector<ll> ys;
    for (int i = 0; i < N-1; i++) {
        if (i > 0) {
            paths[i][0] = paths[i-1][2];
            paths[i][1] = paths[i-1][3];
        } else {
            cin >> paths[i][0] >> paths[i][1];
        }

        cin >> paths[i][2] >> paths[i][3];
        paths[i][4] = i;

        ys.push_back(paths[i][3]);
    }
    ys.push_back(paths[0][1]);
    
    map<ll, int> ycompress;
    sort(ys.begin(), ys.end());
    for (int i = 0; i < N; i++) {
        ycompress[ys[i]] = i;
    }

    vector<vector<int>> ytimes(N, vector<int>{});
    for (int i = 0; i < N-1; i++) {
        paths[i][1] = ycompress[paths[i][1]];
        paths[i][3] = ycompress[paths[i][3]];

        if (paths[i][1] == paths[i][3]) ytimes[paths[i][1]].push_back(i);
    }

    vector<path> horpaths, verpaths;
    vector<pii> xupd;
    for (int i = 0; i < N-1; i++) {
        if (paths[i][1] == paths[i][3]) {
            horpaths.push_back(paths[i]);
            xupd.push_back({min(paths[i][0], paths[i][2])+1, -horpaths.size()});
            xupd.push_back({max(paths[i][0], paths[i][2]), -horpaths.size()});
        } else {
            verpaths.push_back(paths[i]);
            xupd.push_back({paths[i][0], verpaths.size()});
        }
    }
    
    sort(xupd.begin(), xupd.end());

    Segtree2 seg(N, ytimes);
    seg.build();

    vector<bool> in(horpaths.size(), false);
    int cnt = 0;
    for (auto [x, i] : xupd) {
        if (i < 0) {
            i = -i - 1;

            int t = horpaths[i][4];
            int y = horpaths[i][1];

            if (in[i]) seg.modify(y, t, -1);
            else seg.modify(y, t, 1);

            in[i] = !in[i];
        } else {
            i--;

            int t = verpaths[i][4];
            int y1 = min(verpaths[i][1], verpaths[i][3])+1;
            int y2 = max(verpaths[i][1], verpaths[i][3])-1;

            cnt += seg.query(y1, y2 + 1, t, T);
        }
    }

    cout << cnt;
}