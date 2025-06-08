// https://codeforces.com/contest/1349/problem/C

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

#define bfsentry tuple<int, int, int>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M, T;
    cin >> N >> M >> T;

    int a[N][M];
    int flipstart[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
            flipstart[i][j] = -1;
        }
    }



    deque<bfsentry> todo;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            bool flip = false;
            if (i > 0 && a[i - 1][j] == a[i][j]) flip = true;
            if (i < N - 1 && a[i + 1][j] == a[i][j]) flip = true;
            if (j > 0 && a[i][j - 1] == a[i][j]) flip = true;
            if (j < M - 1 && a[i][j + 1] == a[i][j]) flip = true;

            if (flip) {
                todo.push_back({i, j, 0});
                flipstart[i][j] = 0;
            }
        }
    }

    while (!todo.empty()) {
        auto [i, j, time] = todo.front();
        todo.pop_front();

        if (i > 0 && flipstart[i - 1][j] == -1) {
            flipstart[i - 1][j] = time + 1;
            todo.push_back({i - 1, j, time + 1});
        } if (i < N - 1 && flipstart[i + 1][j] == -1) {
            flipstart[i + 1][j] = time + 1;
            todo.push_back({i + 1, j, time + 1});
        } if (j > 0 && flipstart[i][j - 1] == -1) {
            flipstart[i][j - 1] = time + 1;
            todo.push_back({i, j - 1, time + 1});
        } if (j < M - 1 && flipstart[i][j + 1] == -1) {
            flipstart[i][j + 1] = time + 1;
            todo.push_back({i, j + 1, time + 1});
        }
    }

    while (T--) {
        int i, j;
        ll t;
        cin >> i >> j >> t;
        i--;
        j--;

        if (flipstart[i][j] == -1 || flipstart[i][j] > t) {
            cout << a[i][j] << endl;
            continue;
        }

        if ((t - flipstart[i][j]) % 2 == 1) cout << (a[i][j] ^ 1);
        else cout << a[i][j];
        cout << endl;
    }
}