// https://cses.fi/problemset/task/1193

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


struct node {
    int x, y;
    int dist;
};

int main() {
    int N, M;
    cin >> N >> M;

    char grid[N][M];
    int dist[N][M];
    bool searched[N][M];
    char dir[N][M];

    // i, j
    pii a, b;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'A') a = {i, j};
            if (grid[i][j] == 'B') b = {i, j};
            
            searched[i][j] = false;
            if (grid[i][j] == '#') searched[i][j] = true;
        }
    }

    deque<node> todo;

    todo.push_back({b.second, b.first, 0});
    searched[b.first][b.second] = true;
    dist[b.first][b.second] = 0;
    dir[b.first][b.second] = '.';

    while (!todo.empty()) {
        node cur = todo.front();
        todo.pop_front();

        if (cur.x < M - 1 && !searched[cur.y][cur.x + 1]) {
            searched[cur.y][cur.x + 1] = true;
            dist[cur.y][cur.x + 1] = cur.dist + 1;
            dir[cur.y][cur.x + 1] = 'L';
            todo.push_back({cur.x + 1, cur.y, cur.dist + 1});
        } if (cur.x > 0 && !searched[cur.y][cur.x - 1]) {
            searched[cur.y][cur.x - 1] = true;
            dist[cur.y][cur.x - 1] = cur.dist + 1;
            dir[cur.y][cur.x - 1] = 'R';
            todo.push_back({cur.x - 1, cur.y, cur.dist + 1});
        } if (cur.y < N - 1 && !searched[cur.y + 1][cur.x]) {
            searched[cur.y + 1][cur.x] = true;
            dist[cur.y + 1][cur.x] = cur.dist + 1;
            dir[cur.y + 1][cur.x] = 'U';
            todo.push_back({cur.x, cur.y + 1, cur.dist + 1});
        } if (cur.y > 0 && !searched[cur.y - 1][cur.x]) {
            searched[cur.y - 1][cur.x] = true;
            dist[cur.y - 1][cur.x] = cur.dist + 1;
            dir[cur.y - 1][cur.x] = 'D';
            todo.push_back({cur.x, cur.y - 1, cur.dist + 1});
        }
    }

    if (!searched[a.first][a.second]) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    cout << dist[a.first][a.second] << endl;
    int x = a.second, y = a.first;
    for (int i = 0; i < dist[a.first][a.second]; i++) {
        cout << dir[y][x];
        if (dir[y][x] == 'U') y--;
        else if (dir[y][x] == 'D') y++;
        else if (dir[y][x] == 'L') x--;
        else x++;
    }
}