// https://usaco.org/index.php?page=viewproblem2&cpid=620

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("pails");
    
    int X, Y, K, M;
    cin >> X >> Y >> K >> M;

    int dp[X + 1][Y + 1];
    for (int x = 0; x <= X; x++) for (int y = 0; y <= Y; y++) dp[x][y] = 1e6;

    dp[0][0] = 0;
    deque<pii> todo;
    todo.push_back({0, 0});
    while (!todo.empty()) {
        auto [x, y] = todo.front();
        todo.pop_front();

        int time = dp[x][y];

        if (dp[x][0] > time + 1) {
            dp[x][0] = time + 1;
            todo.push_back({x, 0});
        } if (dp[0][y] > time + 1) {
            dp[0][y] = time + 1;
            todo.push_back({0, y});
        } 
        if (dp[X][y] > time + 1) {
            dp[X][y] = time + 1;
            todo.push_back({X, y});
        } if (dp[x][Y] > time + 1) {
            dp[x][Y] = time + 1;
            todo.push_back({x, Y});
        }

        int poury = min(x, Y - y);
        int pourx = min(y, X - x);
        if (dp[x - poury][y + poury] > time + 1) {
            dp[x - poury][y + poury] = time + 1;
            todo.push_back({x - poury, y + poury});
        } if (dp[x + pourx][y - pourx] > time + 1) {
            dp[x + pourx][y - pourx] = time + 1;
            todo.push_back({x + pourx, y - pourx});
        }
    }

    int mindist = 1e6;
    for (int x = 0; x <= X; x++) {
        for (int y = 0; y <= Y; y++) if (dp[x][y] <= K) mindist = min(mindist, abs(M - x - y));
    }

    cout << mindist;
}