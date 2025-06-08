// Problem link here:

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

#define edg array<int, 3>

const int MAXN = 1000, MAXM = 1000;
int N, M;

// closest wall loc in the direction
pii wallleft[MAXN][MAXM], wallright[MAXN][MAXM], wallup[MAXN][MAXM], walldown[MAXN][MAXM];
int walldist[MAXN][MAXM];

char grid[MAXN][MAXM];

int dists[MAXN][MAXM];

void wallbfs() {
    deque<edg> todo;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '#') {
                todo.push_back({i, j, 0});
                walldist[i][j] = 0;
            }
        }
    } for (int i = 0; i < N; i++) {
        todo.push_back({i, -1, 0});
        todo.push_back({i, M, 0});
    } for (int j = 0; j < M; j++) {
        todo.push_back({-1, j, 0});
        todo.push_back({N, j, 0});
    }

    while (!todo.empty()) {
        auto [i, j, d] = todo.front();
        todo.pop_front();
        d++;

        if (i<N-1 && walldist[i+1][j] == -1) {
            walldist[i+1][j] = d;
            todo.push_back({i+1, j, d});
        } if (i>0 && walldist[i-1][j] == -1) {
            walldist[i-1][j] = d;
            todo.push_back({i-1, j, d});
        } if (j<M-1 && walldist[i][j+1] == -1) {
            walldist[i][j+1] = d;
            todo.push_back({i, j+1, d});
        } if (j>0 && walldist[i][j-1] == -1) {
            walldist[i][j-1] = d;
            todo.push_back({i, j-1, d});
        }
    }
}

vector<edg> getedges(int i, int j) {
    vector<edg> edges;
    if (i > 0 && grid[i-1][j] != '#') edges.push_back({i-1, j, 1});
    if (i < N-1 && grid[i+1][j] != '#') edges.push_back({i+1, j, 1});
    if (j > 0 && grid[i][j-1] != '#') edges.push_back({i, j-1, 1});
    if (j < M-1 && grid[i][j+1] != '#') edges.push_back({i, j+1, 1});

    edges.push_back({wallleft[i][j].first, wallleft[i][j].second+1, walldist[i][j]});
    edges.push_back({wallright[i][j].first, wallright[i][j].second-1, walldist[i][j]});
    edges.push_back({wallup[i][j].first+1, wallup[i][j].second, walldist[i][j]});
    edges.push_back({walldown[i][j].first-1, walldown[i][j].second, walldist[i][j]});

    return edges;
}

void dijkstra(int startx, int starty) {
    auto cmp = [](edg a, edg b) {
        return a[2] > b[2];
    };

    dists[startx][starty] = 0;

    priority_queue<edg, vector<edg>, decltype(cmp)> pq(cmp);
    pq.push({startx, starty, 0});

    while (!pq.empty()) {
        auto [i, j, d] = pq.top();
        pq.pop();
        
        vector<edg> edges = getedges(i, j);
        for (auto [i2, j2, w] : edges) {
            if (grid[i2][j2] == '#') continue;
            if (d+w >= dists[i2][j2]) continue;
            dists[i2][j2] = d+w;
            pq.push({i2, j2, d+w});
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> M;

    int startx, starty, endx, endy;
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
        cin >> grid[i][j];
        dists[i][j] = 1e8;
        walldist[i][j] = -1;

        if (grid[i][j] == 'S') {
            startx = i, starty = j;
        } if (grid[i][j] == 'C') {
            endx = i, endy = j;
        }
    }

    for (int i = 0; i < N; i++) {
        if (grid[i][0] == '#') wallleft[i][0] = {i, 0};
        else wallleft[i][0] = {i, -1};
        for (int j = 1; j < M; j++) {
            if (grid[i][j] == '#') wallleft[i][j] = {i, j};
            else wallleft[i][j] = wallleft[i][j-1];
        }
    } for (int i = 0; i < N; i++) {
        if (grid[i][M-1] == '#') wallright[i][M-1] = {i, M-1};
        else wallright[i][M-1] = {i, M};
        for (int j = M-2; j >= 0; j--) {
            if (grid[i][j] == '#') wallright[i][j] = {i, j};
            else wallright[i][j] = wallright[i][j+1];
        }
    } for (int j = 0; j < M; j++) {
        if (grid[0][j] == '#') wallup[0][j] = {0, j};
        else wallup[0][j] = {-1, j};
        for (int i = 1; i < N; i++) {
            if (grid[i][j] == '#') wallup[i][j] = {i, j};
            else wallup[i][j] = wallup[i-1][j];
        }
    } for (int j = 0; j < M; j++) {
        if (grid[N-1][j] == '#') walldown[N-1][j] = {N-1, j};
        else walldown[N-1][j] = {N, j};
        for (int i = N-2; i >= 0; i--) {
            if (grid[i][j] == '#') walldown[i][j] = {i, j};
            else walldown[i][j] = walldown[i+1][j];
        }
    }

    wallbfs();
    dijkstra(startx, starty);

    cout << dists[endx][endy];
}