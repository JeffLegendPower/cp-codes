// https://codeforces.com/contest/1987/problem/E

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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

typedef pair<ll, ll> pll;

struct node {
    ll height = -1;
    ll val;
    vector<int> next;
    // number of +, cost of each +
    vector<pll> cheaps;
};

vector<node> graph;

ll cost = 0;
int heightdfs(int curIdx) {
    int height = 1;
    ll sumBelow = 0;

    ll minChildHeight = 1e6;

    for (int next : graph[curIdx].next) {
        height = max(height, heightdfs(next) + 1);
        sumBelow += graph[next].val;
        minChildHeight = min(minChildHeight, graph[next].height);
        for (pll cheap : graph[next].cheaps) {
            // cout << "E " << cheap.first << " " << cheap.second << endl;
            cheap.second++;
            graph[curIdx].cheaps.push_back(cheap);
        }
    }

    if (height > 1 && graph[curIdx].val < sumBelow)
        graph[curIdx].cheaps.push_back({ sumBelow - graph[curIdx].val, 0 });

    if (sumBelow < graph[curIdx].val && graph[curIdx].cheaps.size() > 0 && graph[curIdx].cheaps.back().second < minChildHeight) {
        ll diff = min(graph[curIdx].val - sumBelow, graph[curIdx].cheaps.back().first);
        sumBelow += diff;
        graph[curIdx].cheaps.back().first -= diff;
        cost += diff * graph[curIdx].cheaps.back().second;
        if (graph[curIdx].cheaps.back().first == 0) graph[curIdx].cheaps.pop_back();
    }

    if (height == 1) minChildHeight = 0;
    cost += max(0ll, graph[curIdx].val - sumBelow) * minChildHeight;

    // if (graph[curIdx].cheaps.size() > 0)
    // cout << curIdx << " " << graph[curIdx].cheaps.back().second << endl;


    graph[curIdx].height = height;
    return height;
}

void costdfs(int curIdx) {
    if (graph[curIdx].height == 1) return;
    // cout << curIdx << endl;

    ll valBelow = 0;
    ll minChildHeight = 1e6;
    for (int next : graph[curIdx].next) {
        
        valBelow += graph[next].val;
        minChildHeight = min(minChildHeight, graph[next].height);
    }

    int backIdx = graph[curIdx].cheaps.size() - 1;
    // if (valBelow < graph[curIdx].val ) {
    //     g
    // }

    cost += max(0ll, graph[curIdx].val - valBelow) * minChildHeight;
    // cout << curIdx << endl;
    // cout << curIdx << " " << graph[curIdx].val - valBelow << " " << minChildHeight << endl;
}


int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        cost = 0;
        graph.clear();

        for (int i = 0; i < N; i++) {
            ll val;
            cin >> val;
            graph.push_back({});
            graph[i].val = val;
        } for (int i = 1; i < N; i++) {
            int start;
            cin >> start;
            graph[start - 1].next.push_back(i);
        }

        heightdfs(0);
        // for (int i = 0; i < N; i++)
        //     costdfs(i);

        // for (int i = 0; i < N; i++) cout << graph[i].height << endl;

        cout << cost << endl;
    }
}