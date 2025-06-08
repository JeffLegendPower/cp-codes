// https://usaco.org/index.php?page=viewproblem2&cpid=838

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

struct node {
    bool searched = false;
    vector<int> next;
    int indeg = 0;
};

const int MAXN = 1000000;
node graph[MAXN];

bool cyclic = false;
bool stackk[MAXN];
vector<int> topo;
void toposort(int cur) {
    graph[cur].searched = true;
    stackk[cur] = true;

    for (int next : graph[cur].next) {
        if (stackk[next]) cyclic = true;
        if (!graph[next].searched) toposort(next);
    }

    stackk[cur] = false;
    topo.push_back(cur);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("milkorder");

    int N, M;
    cin >> N >> M;

    vector<int> m[M];
    for (int i = 0; i < M; i++) {
        int mi;
        cin >> mi;

        while (mi--) {
            int a;
            cin >> a;
            m[i].push_back(a);
        }
    }

    int low = 0, high = M - 1;
    int best = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        topo.clear();
        cyclic = false;

        for (int i = 0; i < N; i++) {
            graph[i].searched = false;
            graph[i].next.clear();
        }

        for (int i = 0; i <= mid; i++) {
            for (int j = 1; j < m[i].size(); j++) {
                graph[m[i][j - 1] - 1].next.push_back(m[i][j] - 1);
            }
        }

        for (int i = 0; i < N; i++) if (!graph[i].searched) toposort(i);
        if (cyclic) {
            high = mid - 1;
        } else {
            low = mid + 1;
            best = mid;
        }
    }

    topo.clear();
    cyclic = false;

    for (int i = 0; i < N; i++) {
        graph[i].searched = false;
        graph[i].next.clear();
    }

    for (int i = 0; i <= best; i++) {
        for (int j = 1; j < m[i].size(); j++) {
            graph[m[i][j - 1] - 1].next.push_back(m[i][j] - 1);
            graph[m[i][j] - 1].indeg++;
        }
    }

    // topo sort using kahn's algorithm to get the lexographically smallest sorting
    priority_queue<int, vector<int>, greater<int>> queue;
    for (int i = 0; i < N; i++) if (graph[i].indeg == 0) queue.push(i);

    vector<int> topo;
    while (!queue.empty()) {
        int cur = queue.top();
        queue.pop();

        topo.push_back(cur);
        for (int next : graph[cur].next) {
            if (--graph[next].indeg == 0) {
                queue.push(next);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << topo[i] + 1;
        if (i < N - 1) cout << " ";
    }
}