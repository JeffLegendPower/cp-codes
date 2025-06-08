// https://dmoj.ca/problem/ioi00p4

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

const int MAXN = 250, MAXM = 200, MAXL = 30;
int M, L;

struct node {
    bool searched = false;
    vector<int> next;

    ll dp[MAXL];
};
node graph[MAXM];
vector<int> club;

vector<int> adj[MAXN][MAXN];
vector<int> regions[MAXN];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> M >> N >> L;

    for (int i = 0; i < L; i++) {
        int c;
        cin >> c;
        club.push_back(c);
    }

    for (int i = 0; i < M; i++) {
        int I;
        cin >> I;

        int last = -1, first = -1;
        for (int j = 0; j < I; j++) {
            int cur;
            cin >> cur;
            regions[cur].push_back(i);

            if (last != -1) {
                adj[last][cur].push_back(i);
                adj[cur][last].push_back(i);
            } if (j == I - 1) {
                adj[first][cur].push_back(i);
                adj[cur][first].push_back(i);
            }

            last = cur;
            if (first == -1) first = cur;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (adj[i][j].size() == 0) continue;

            int a = adj[i][j][0], b = adj[i][j][1];

            graph[a].next.push_back(b);
            graph[b].next.push_back(a);
        }
    }

    int idx = -1;
    for (int c : club) {
        idx++;
        for (int i = 0; i < M; i++) graph[i].searched = false;

        deque<int> todo;
        for (int reg : regions[c]) {
            todo.push_back(reg);
            graph[reg].searched = true;
            graph[reg].dp[idx] = 0;
        }

        while (!todo.empty()) {
            int cur = todo.front();
            todo.pop_front();

            ll dist = graph[cur].dp[idx] + 1;

            for (int next : graph[cur].next) {
                if (graph[next].searched) continue;

                graph[next].searched = true;
                graph[next].dp[idx] = dist;
                todo.push_back(next);
            }
        }
    }

    ll mincost = 1e9;
    int minlabel = -1;
    for (int i = 0; i < M; i++) {
        ll cost = 0;
        for (int j = 0; j < L; j++) cost += graph[i].dp[j];

        if (cost < mincost) {
            mincost = cost;
            minlabel = i + 1;
        }
    }
    
    cout << mincost << endl << minlabel;
}