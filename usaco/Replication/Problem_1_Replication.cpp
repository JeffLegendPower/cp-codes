// https://usaco.org/index.php?page=viewproblem2&cpid=1065

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

const int MAXN = 1000;
int D;

struct ety {
    int i, j, time;
};

char grid[MAXN][MAXN];
bool searched[MAXN][MAXN];
int dists[MAXN][MAXN]; // min manhatten dist from i,j to some rock

bool possible[MAXN][MAXN];
int siz[MAXN][MAXN];

void bfs() {
    deque<pii> todo;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '#') {
                dists[i][j] = 0;
                searched[i][j] = true;
                todo.push_back({i, j});
            }
        }
    }

    while (!todo.empty()) {
        auto [i, j] = todo.front();
        todo.pop_front();

        int next = dists[i][j] + 1;
        if (i > 0 && !searched[i - 1][j]) {
            searched[i - 1][j] = true;
            dists[i - 1][j] = next;
            todo.push_back({i - 1, j});
        } if (i < N - 1 && !searched[i + 1][j]) {
            searched[i + 1][j] = true;
            dists[i + 1][j] = next;
            todo.push_back({i + 1, j});
        } if (j > 0 && !searched[i][j - 1]) {
            searched[i][j - 1] = true;
            dists[i][j - 1] = next;
            todo.push_back({i, j - 1});
        } if (j < N - 1 && !searched[i][j + 1]) {
            searched[i][j + 1] = true;
            dists[i][j + 1] = next;
            todo.push_back({i, j + 1});
        }
    }
}

int cnt = 0;
void bfs2() {

    auto cmp = [](ety one, ety two) {
        return one.time < two.time;
    };

    priority_queue<ety, vector<ety>, decltype(cmp)> todo(cmp);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (possible[i][j]) {
                todo.push({i, j, siz[i][j]});
                searched[i][j] = true;
            }
        }
    }

    while (!todo.empty()) {
        auto [i, j, time] = todo.top();
        todo.pop();
        
        int next = time - 1;
        if (next < 1) continue;

        if (i > 0 && !searched[i - 1][j] && grid[i - 1][j] != '#') {
            searched[i - 1][j] = true;
            siz[i - 1][j] = next;
            possible[i - 1][j] = true;
            todo.push({i - 1, j, next});
        } if (i < N - 1 && !searched[i + 1][j] && grid[i + 1][j] != '#') {
            searched[i + 1][j] = true;
            siz[i + 1][j] = next;
            possible[i + 1][j] = true;
            todo.push({i + 1, j, next});
        } if (j > 0 && !searched[i][j - 1] && grid[i][j - 1] != '#') {
            searched[i][j - 1] = true;
            siz[i][j - 1] = next;
            possible[i][j - 1] = true;
            todo.push({i, j - 1, next});
        } if (j < N - 1 && !searched[i][j + 1] && grid[i][j + 1] != '#') {
            searched[i][j + 1] = true;
            siz[i][j + 1] = next;
            possible[i][j + 1] = true;
            todo.push({i, j + 1, next});
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> D;

    // {i, j, time}
    deque<ety> todo;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            siz[i][j] = -1;

            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                possible[i][j] = true;
                siz[i][j] = 1;
                todo.push_back({i, j, 0});
            }
        }
    }

    bfs();

    while (!todo.empty()) {
        auto [i, j, time] = todo.front();
        todo.pop_front();

        int next = time + 1;
        int si = 1 + (time / D);

        siz[i][j] = si - 1;
        if (dists[i][j] < si) continue;
        siz[i][j] = si;

        if (i < N - 1 && grid[i + 1][j] != '#' && dists[i + 1][j] >= si && !possible[i + 1][j]) {
            possible[i + 1][j] = true;
            todo.push_back({i + 1, j, next});
        } if (i > 0 && grid[i - 1][j] != '#' && dists[i - 1][j] >= si && !possible[i - 1][j]) {
            possible[i - 1][j] = true;
            todo.push_back({i - 1, j, next});
        }
        if (j < N - 1 && grid[i][j + 1] != '#' && dists[i][j + 1] >= si && !possible[i][j + 1]) {
            possible[i][j + 1] = true;
            todo.push_back({i, j + 1, next});
        } if (j > 0 && grid[i][j - 1] != '#' && dists[i][j - 1] >= si && !possible[i][j - 1]) {
            possible[i][j - 1] = true;
            todo.push_back({i, j - 1, next});
        }
    }

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) searched[i][j] = false;

    bfs2();

    int num = 0;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) num += possible[i][j];

    cout << num;
}