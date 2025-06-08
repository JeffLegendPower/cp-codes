// https://usaco.org/index.php?page=viewproblem2&cpid=947

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("balance");

    int N; cin >> N;

    int a[N], b[N];
    ll inva = 0, invb = 0;
    ll a1 = 0, b1 = 0, a0 = 0, b0 = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (a[i] == 1) a1++;
        else {
            inva += a1;
            a0++;
        }
    } for (int i = 0; i < N; i++) {
        cin >> b[i];
        if (b[i] == 1) b1++;
        else {
            invb += b1;
            b0++;
        }
    }

    ll best = abs(inva - invb);

    // swap 0s from a with 1s from b
    ll invac = inva, invbc = invb;
    ll a1c = a1, b1c = b1, a0c = a0, b0c = b0;
    int aidx = N - 1, bidx = 0;

    ll c = 0;
    while (aidx >= 0 && bidx < N) {
        while (aidx >= 0 && a[aidx] != 0) {
            aidx--;
            a1c--;
        } while (bidx < N && b[bidx] != 1) {
            bidx++;
            b0c--;
        }
        if (aidx < 0 || bidx >= N) break;

        c += N - aidx - 1;
        c += bidx;
        c += 1;

        invac -= a1c;
        invbc -= b0c;

        best = min(best, c + abs(invac - invbc));

        aidx--;
        bidx++;
    }

    // swap 1s from a with 0s from b
    invac = inva, invbc = invb;
    a1c = a1, b1c = 0, a0c = 0, b0c = b0;
    aidx = N - 1, bidx = 0;

    c = 0;
    while (aidx >= 0 && bidx < N) {
        while (aidx >= 0 && a[aidx] != 1) {
            aidx--;
            a0c++;
        } while (bidx < N && b[bidx] != 0) {
            bidx++;
            b1c++;
        }
        if (aidx < 0 || bidx >= N) break;

        a1c--;
        b0c--;

        c += N - aidx - 1;
        c += bidx;
        c += 1;

        invac += a1c - a0c;
        invbc += b0c - b1c;

        best = min(best, c + abs(invac - invbc));

        aidx--;
        bidx++;
    }

    cout << best << endl;
}