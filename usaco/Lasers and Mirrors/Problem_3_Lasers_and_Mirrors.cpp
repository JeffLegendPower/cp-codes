// https://usaco.org/index.php?page=viewproblem2&cpid=671

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (plli a, plli b) {
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

struct pst {
    ll x, y;
    int time = 1e6;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("lasers");

    int N;
    ll xl, yl, xb, yb;
    cin >> N >> xl >> yl >> xb >> yb;

    pst posts[N + 2];
    posts[0] = {xl, yl, 0};
    map<ll, vector<int>> rows, cols;

    for (int i = 1; i <= N; i++) {
        cin >> posts[i].x >> posts[i].y;

        rows[posts[i].y].push_back(i);
        cols[posts[i].x].push_back(i);
    }
    posts[N + 1] = {xb, yb};
    rows[yb].push_back(N + 1);
    cols[xb].push_back(N + 1);

    rows[yl].push_back(0);
    cols[xl].push_back(0);

    deque<int> todo;
    todo.push_back(0);
    while (!todo.empty()) {
        int idx = todo.front();
        todo.pop_front();

        auto [x, y, time] = posts[idx];

        vector<int>& row = rows.find(y)->second;
        vector<int>& col = cols.find(x)->second;

        for (int i : row) {
            if (i == idx) continue;
            // if (idx == 2) cout << i << " " << posts[i].time << endl;
            if (posts[i].time < time + 1) break;
            if (posts[i].time <= time + 1) continue;

            posts[i].time = time + 1;
            todo.push_back(i);
        } for (int i : col) {
            if (i == idx) continue;
            if (posts[i].time < time + 1) break;
            if (posts[i].time <= time + 1) continue;
            posts[i].time = time + 1;
            todo.push_back(i);
        }
    }

    if (posts[N + 1].time == 1e6) cout << -1;
    else cout << posts[N + 1].time - 1;

    // for (int i = 0; i < N + 2; i++) cout << posts[i].time << " ";
}