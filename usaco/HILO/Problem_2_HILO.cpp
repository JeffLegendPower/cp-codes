// https://usaco.org/index.php?page=viewproblem2&cpid=1162&lang=en

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
const int Nmax = 1e6;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 1e6;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // 5 2 4 3        x=3.5     HILOHILO     x=4.5     HILOLO      nothing->HI->LO->NOTHING
    // every element goes thru a process like this: nothing->HI->LO->nothing

    cin >> N;
    set<int> none1, hi, lo, none2;

    set<int> seq1;
    set<int, greater<int>> seq2;

    int mina = 1e6;
    int a[N];
    vector<int> types(N, 0);
    vector<int> idxs(N + 1, -1);

    for (int i = 0; i < 1e6; i++) t[N + i] = 1e6;

    for (int i = 0; i < N; i++) {
        cin >> a[i];
        idxs[a[i]] = i;
        t[N + i] = a[i];

        if (a[i] < mina) {
            mina = a[i];
            hi.insert(i);
            types[i] = 1;
            seq1.insert(i);
            seq2.insert(i);
            t[N + i] = 1e6;
        } else none1.insert(i);
    }

    build();

    cout << 0 << endl;
    int cnt = 0;
    for (int x = 1; x < N; x++) {
        int idx = idxs[x];

        // if (x == 2) {
        //     for (auto itr = seq1.begin(); itr != seq1.end(); itr++) {
        //         cout << (*itr) << "   " << types[*itr] << endl;
        //     }
        //     break;
        // }

        hi.erase(x);
        lo.insert(idx);
        types[idx] = 2;

        bool hibef = (seq2.upper_bound(idx) == seq2.end()) ? false : (types[*seq2.upper_bound(idx)] == 1);
        bool loaft = (seq1.upper_bound(idx) == seq1.end()) ? false : (types[*seq1.upper_bound(idx)] == 2);

        if (hibef && !loaft) cnt++;
        if (!hibef && loaft) cnt--;

        int lower = idx, upper = 1e6;
        int xf = 0;
        while (lower + 1 < upper) {
            // if (xf++ > 3) break;
            int next = query(lower + 1, upper);
            if (next == 1e6) break;
            int nextidx = idxs[next];

            // cout << next << endl;

            upper = nextidx;
            modify(nextidx, 1e6);
            none1.erase(nextidx);
            hi.insert(nextidx);
            types[nextidx] = 1;

            seq1.insert(nextidx);
            seq2.insert(nextidx);
            bool hibef = (seq2.upper_bound(nextidx) == seq2.end()) ? false : (types[*seq2.upper_bound(nextidx)] == 1);
            bool loaft = (seq1.upper_bound(nextidx) == seq1.end()) ? false : (types[*seq1.upper_bound(nextidx)] == 2);

            if (!hibef && loaft) cnt++;
        }

        // cout << cnt << " ";

        lower = idx, upper = 1e6;
        while (lo.upper_bound(idx) != lo.end()) {
            int nextidx = *lo.upper_bound(idx);
            lo.erase(nextidx);
            none2.insert(nextidx);
            types[nextidx] = 3;

            seq1.erase(nextidx);
            seq2.erase(nextidx);

            // cout << "E";
            
            bool hibef = (seq2.upper_bound(nextidx) == seq2.end()) ? false : (types[*seq2.upper_bound(nextidx)] == 1);
            bool loaft = (seq1.upper_bound(nextidx) == seq1.end()) ? false : (types[*seq1.upper_bound(nextidx)] == 2);

            if (hibef && !loaft) cnt--;
        }

        cout << cnt << endl;
    }
    cout << 0;
}