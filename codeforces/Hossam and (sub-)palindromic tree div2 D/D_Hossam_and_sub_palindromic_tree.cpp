// https://codeforces.com/contest/1771/problem/D

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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

struct node {
    vector<int> next;
    char c;
};
vector<node> graph;

vector<vector<int>> pprev;
vector<vector<int>> dp;
vector<array<int, 3>> todo;
void dfs(int v, int p, int root, int dist) {
    pprev[v][root] = p;
    todo.push_back({v, root, dist});

    for (int next : graph[v].next) {
        if (next == p) continue;
        dfs(next, v, root, dist+1);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        string s; cin >> s;
        graph.clear();
        pprev.clear();
        dp.clear();
        todo.clear();

        for (int i = 0; i < N; i++) {
            node cur; cur.c = s[i];
            graph.push_back(cur);

            pprev.push_back({});
            dp.push_back({});
            for (int j = 0; j < N; j++) {
                pprev[i].push_back(-1);
                dp[i].push_back(0);
            }
        }

        for (int i = 0; i < N - 1; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }
        for (int i = 0; i < N; i++) dfs(i, i, i, 0);

        sort(todo.begin(), todo.end(), [](array<int, 3> one, array<int, 3> two) {
            return one[2] < two[2];
        });

        int best = 1;
        for (int i = 0; i < todo.size(); i++) {
            auto [a, b, dist] = todo[i];
            if (dist == 0) {
                dp[a][b] = 1;
                continue;
            }

            // if (dist > 1) break;

            if (s[a] == s[b]) {
                if (dist == 1) dp[a][b] = 2;
                else dp[a][b] = dp[pprev[a][b]][pprev[b][a]] + 2;
            }
            dp[a][b] = max({dp[a][b], dp[pprev[a][b]][b], dp[a][pprev[b][a]]});

            // cout << a+1 << " " << b+1 << " " << dp[a][b] << endl;

            best = max(best, dp[a][b]);
        }

        cout << best << endl;
    }
}