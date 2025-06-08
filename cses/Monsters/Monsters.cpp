// https://cses.fi/problemset/task/1194

// This can be solved with some cool bfs
// If there was no monster clause, we could solve this by using bfs/dfs
// to search through the entire grid and act like the walls are "impenetrable"
// and then check all the borders to see if we escaped. However, if a tile is closer
// or equal distance to a monster than to the player, then the tile is unreachable by the player
// Now we can solve this with bfs, but first fill the queue with the starting positions of all the monsters
// and it will essentially give higher priority to the monsters than to the player
// and then add the player starting position at the end. So now if a monster is able to reach before/at the same time
// as the player at a spot, bfs for the monster will arrive there first and we can say that spot is monster controlled
// Now, we can just check for all the player controlled spots on the border, if none exist then it's not possible
// And if one does, we can just save the directions to get there and use backtracking to get the path

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


int main() {
    int N, M;
    cin >> N >> M;


    char grid[N][M];
    // 0 = unsearched, 1 = controlled by player, 2 = controled by monster/is wall
    int searched[N][M];
    char from[N][M];

    deque<pii> todo;
    pii a;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            searched[i][j] = 0;
            if (grid[i][j] == 'A') a = {i, j};
            if (grid[i][j] == 'M') {
                todo.push_back({i, j});
                searched[i][j] = 2;
            } if (grid[i][j] == '#') searched[i][j] = 2;
        }
    }

    todo.push_back(a);
    searched[a.first][a.second] = 1;
    from[a.first][a.second] = '.';
    while (!todo.empty()) {
        pii cur = todo.front();
        todo.pop_front();

        int i = cur.first;
        int j = cur.second;

        if (i > 0 && searched[i - 1][j] == 0) {
            searched[i - 1][j] = searched[i][j];
            from[i - 1][j] = 'U';
            todo.push_back({i - 1, j});
        } if (i < N - 1 && searched[i + 1][j] == 0) {
            searched[i + 1][j] = searched[i][j];
            from[i + 1][j] = 'D';
            todo.push_back({i + 1, j});
        } if (j > 0 && searched[i][j - 1] == 0) {
            searched[i][j - 1] = searched[i][j];
            from[i][j - 1] = 'L';
            todo.push_back({i, j - 1});
        } if (j < M - 1 && searched[i][j + 1] == 0) {
            searched[i][j + 1] = searched[i][j];
            from[i][j + 1] = 'R';
            todo.push_back({i, j + 1});
        }
    }

    
    pii end = {-1, -1};
    for (int i = 0; i < N; i++) {
        if (searched[i][0] == 1) {
            end = {i, 0};
            break;
        } if (searched[i][M - 1] == 1) {
            end = {i, M - 1};
            break;
        }
    }
    if (end.first == -1) {
        for (int i = 0; i < M; i++) {
            if (searched[0][i] == 1) {
                end = {0, i};
                break;
            } if (searched[N - 1][i] == 1) {
                end = {N - 1, i};
                break;
            }
        }
    }

    if (end.first == -1) {
        cout << "NO";
        return 0;
    }

    vector<char> ans;
    while (from[end.first][end.second] != '.') {
        char fro = from[end.first][end.second];

        ans.push_back(fro);
        if (fro == 'U') end.first++;
        else if (fro == 'D') end.first--;
        else if (fro == 'L') end.second++;
        else end.second--;
    }

    reverse(ans.begin(), ans.end());
    
    cout << "YES" << endl;
    cout << ans.size() << endl;
    for (char an : ans) cout << an;
}