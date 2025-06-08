// https://usaco.org/index.php?page=viewproblem2&cpid=696

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

struct node {
    vector<int> next;
    ll p;

    int start, end;
    int ans = 0;
};
node graph[100000];

int timer = 0;
void euler_tour(int cur, int parent) {
    graph[cur].start = timer++;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur);
    }
    graph[cur].end = timer;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("promote");

    cin >> N;

    plli vs[N];
    for (int i = 0; i < N; i++) {
        cin >> graph[i].p;
        vs[i] = {graph[i].p, i};
    } for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        p--;

        graph[p].next.push_back(i);
    }
    euler_tour(0, -1);

    sort(vs, vs + N, [](plli one, plli two) {
        return one > two;
    });

    int left = 0;
    while (left < N) {
        ll p = vs[left].first;
        int right = left;

        while (right < N && vs[right].first == p) {
            int v = vs[right].second;
            graph[v].ans = query(graph[v].start, graph[v].end);
            right++;
        }

        while (left < right) {
            int v = vs[left].second;
            modify(graph[v].start, 1);
            left++;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << graph[i].ans;
        if (i < N - 1) cout << endl;
    }
}