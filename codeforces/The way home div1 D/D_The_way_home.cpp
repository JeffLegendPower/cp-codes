// https://codeforces.com/contest/1801/problem/D

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
    // {cost, next vertex idx}
    vector<plli> next;
    ll w;
}; struct todo {
    int target;
    int maxw; // gives vertex idx of max w instead of max w itself
    ll shows;
    ll money;
};
vector<node> graph;

class cmp {
    public:
    bool operator()(todo one, todo two) {
        // put less shows at the front of pq
        if (one.shows > two.shows) return true;
        if (one.shows < two.shows) return false;

        // put more money at the front of pq
        if (one.money < two.money) return true;
        return false;
    }
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        ll p;
        cin >> N >> M >> p;
        graph.clear();

        for (int i = 0; i < N; i++) {
            node cur;
            cin >> cur.w;
            graph.push_back(cur);
        }

        for (int i = 0; i < M; i++) {
            int a, b;
            ll s;
            cin >> a >> b >> s;
            graph[a - 1].next.push_back({s, b - 1});
        }

        // node idx i, max w idx j, min shows k, max money l
        // dp[i][j] = {k, l}
        // {a, b} is better than {c, d} if a < c or a = c and b > d
        pll dp[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) dp[i][j] = {1e18, -1};
        }
        // dp[0][0] = {0, p};

        priority_queue<todo, vector<todo>, cmp> pq;
        pq.push({0, 0, 0, p});

        while (!pq.empty()) {
            auto [target, maxw, shows, money] = pq.top();
            pq.pop();

            // cout << "DEL " << shows << endl;

            bool update = false;
            if (shows < dp[target][maxw].first) {
                dp[target][maxw] = {shows, money};
                update = true;
            } else if (shows == dp[target][maxw].first && money > dp[target][maxw].second) {
                dp[target][maxw] = {shows, money};
                update = true;
            }

            if (!update) continue;

            if (graph[target].w > graph[maxw].w) maxw = target;
            for (plli next : graph[target].next) {
                ll cost = next.first;

                ll w = graph[maxw].w;

                ll shows2 = max(0ll, (cost - money + w - 1) / w);
                pq.push({next.second, maxw, shows + shows2, money + shows2 * w - cost});

                // cout << "ADD " << shows + shows2 << endl;
            }
        }

        ll best = 1e18;
        for (int i = 0; i < N; i++) best = min(best, dp[N - 1][i].first);

        if (best == 1e18) best = -1;
        cout << best << endl;
    }
}