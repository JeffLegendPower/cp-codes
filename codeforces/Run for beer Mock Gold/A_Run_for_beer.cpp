// https://codeforces.com/gym/588594/problem/A

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

vector<pii> graph[100000];
int N;

// 1st is unweight, 2nd is weight
// prioritize minimize 1st first because
// say 2 paths A and B and unweight len A > unweight len B
// right out the weighted lens of A and B in order from first to last
// because len < 10, if you drop the first edge of A you see that all edges in A > all edges in B

// also spigmale since a sigmale cant hold 10^big number without overflow, we also gotta see that only the last diff edge
// controls weight in comparison
// so solved by knowing what "place" the last vertex

pii last[200000];
int place[200000];
int dists[200000];

void bfs() {
    vector<vector<int>> todo(N);
    place[0] = 0;
    todo[0].push_back(0);

    for (int idx = 0; idx < N; idx++) {
        if (todo[idx].empty()) break;

        // edg weight, place of parent, vertx, parent
        vector<array<int, 4>> edgs;

        for (int i = 0; i < todo[idx].size(); i++) {
            int v = todo[idx][i];

            for (auto [x, w] : graph[v]) {
                if (last[x].first != -1) continue;
                edgs.push_back({w, place[v], x, v});
            }

            dists[v] = idx;
        }

        sort(edgs.begin(), edgs.end(), [](const array<int, 4>& a, const array<int, 4>& b) {
            if (a[0] < b[0]) return true;
            if (b[0] < a[0]) return false;
            return a[1] < b[1];
        });

        for (int i = 0; i < edgs.size(); i++) {
            if (last[edgs[i][2]].first != -1) continue;
            last[edgs[i][2]] = {edgs[i][3], edgs[i][0]};
            place[edgs[i][2]] = i;

            if (idx < N-1) todo[idx+1].push_back(edgs[i][2]);
        }
    }
}

bool searched[100000];
vector<int> path0;
array<int, 3> best = {1000000, 1000000, 1000000};
bool dfs2(int v, int d) {
    searched[v] = true;
    bool good = false;

    if (dists[v] < best[0] || (dists[v] == best[0] && 
        (place[v] < best[1] || (place[v] == best[1] && dists[v] + d < best[2]))
    )) {
        best = {dists[v], place[v], dists[v] + d};
        path0.clear();
        good = true;
    }

    for (auto [x, w] : graph[v]) {
        if (w != 0) continue;
        if (searched[x]) continue;

        if (dfs2(x, d+1)) good = true;
    }

    if (good) path0.push_back(v);

    return good;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    for (int i = 0; i < 200000; i++) last[i] = {-1, -1};

    bfs();

    dfs2(N-1, 1);

    string dist = "";
    vector<int> path;
    int v = path0[0];

    while (v != 0) {
        auto [p, w] = last[v];
        v = p;
        path.push_back(v);

        if (dist.empty() && w == 0) continue;
        dist += to_string(w);
    }

    reverse(path.begin(), path.end());

    if (dist.empty()) dist = "0";

    cout << dist << endl;
    cout << path.size() + path0.size() << endl;
    for (int x : path) cout << x << " ";
    for (int x : path0) cout << x << " ";
}