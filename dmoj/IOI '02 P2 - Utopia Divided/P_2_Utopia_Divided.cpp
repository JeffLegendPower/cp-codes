// https://dmoj.ca/problem/ioi02p2

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

    int N; cin >> N;

    int x[N], y[N];
    for (int i = 0; i < N; i++) cin >> x[i];
    for (int i = 0; i < N; i++) cin >> y[i];
    sort(x, x+N);
    sort(y, y+N);

    bool xn[N], yn[N];
    int samex = 0, samey = 0;
    for (int i = 0; i < N; i++) {
        int sq; cin >> sq;
        xn[i] = sq == 1 || sq == 4;
        yn[i] = sq == 1 || sq == 2;

        if (i>0 && xn[i]==xn[i-1]) samex++;
        if (i>0 && yn[i]==yn[i-1]) samey++;
    }


    pii ans[N];
    int lx = samex-1, rx = samex, ly = samey-1, ry = samey;
    bool posx = false, posy = false;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            if (xn[0]) {
                ans[i].first = x[rx++];
                posx = 1;
            } else {
                ans[i].first = -x[rx++];
                posx = 0;
            }
        } else if (i > 0 && xn[i] == xn[i-1]) {
            ans[i].first = x[lx] * ((((samex - lx)&1)^posx) ? 1 : -1);
            lx--;
        } else {
            ans[i].first = x[rx] * ((((rx - samex)&1)^posx) ? 1 : -1);
            rx++;
        }

        if (i == 0) {
            if (yn[0]) {
                ans[i].second = y[ry++];
                posy = 1;
            } else {
                ans[i].second = -y[ry++];
                posy = 0;
            }
        } else if (i > 0 && yn[i] == yn[i-1]) {
            ans[i].second = y[ly] * ((((samey - ly)&1)^posy) ? 1 : -1);
            ly--;
        } else {
            ans[i].second = y[ry] * ((((ry - samey)&1)^posy) ? 1 : -1);
            ry++;
        }

        if (ans[i].first > 0) cout << '+';
        cout << ans[i].first << " ";
        if (ans[i].second > 0) cout << '+';
        cout << ans[i].second << endl;
    }
}