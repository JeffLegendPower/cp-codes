// https://cses.fi/problemset/task/1191/

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

int jmp[20][500000];

int kth(int i, int k) { // kth ancestor of i
    for(int x=20; x>=0; --x)
        if(k & 1<<x) i = jmp[x][i];
    return i;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    ll k; cin >> N >> k;

    ll x[2*N]; for (int i = 0; i < N; i++) {
        cin >> x[i];
        x[N+i] = x[i];
    }

    ll pre[2*N + 1];
    pre[0] = 0;
    for (int i = 0; i < 2*N; i++) pre[i+1] = pre[i] + x[i];

    for (int i = 0; i < 2*N; i++) for (int j = 0; j < 20; j++) jmp[j][i] = i;

    for (int i = 0; i < 2*N; i++) {
        int low = i, high = 2*N - 1;
        int best = i;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (pre[mid+1] - pre[i] > k) high = mid - 1;
            else {
                low = mid + 1;
                best = mid;
            }
        }

        jmp[0][i] = min(best + 1, 2*N - 1);
    }

    for(int i = 1; i < 20; i++) for(int j = 0; j < N; j++) jmp[i][j] = jmp[i-1][jmp[i-1][j]];

    int num = 1e6;
    for (int i = 0; i < N; i++) {
        int low = 1, high = N;
        int best = N;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            int p = kth(i, mid);
            if (p >= i+N) {
                high = mid - 1;
                best = mid;
            } else low = mid + 1;
        }

        num = min(num, best);
    }

    cout << num;
}