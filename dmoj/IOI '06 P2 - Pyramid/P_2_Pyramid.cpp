// https://dmoj.ca/problem/ioi06p2

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


const int MAXN = 1000, MAXM = 1000;

int pre2d[MAXN+1][MAXM+1];
int grid[MAXN][MAXM];

int chamber[2*MAXN][2*MAXM];
pii chamber2[2*MAXN][2*MAXM];

int rect(int i1, int j1, int i2, int j2) {
    return pre2d[i2+1][j2+1] - pre2d[i1][j2+1] - pre2d[i2+1][j1] + pre2d[i1][j1];
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int M, N, A, B, C, D;
    cin >> M >> N >> A >> B >> C >> D;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i <= N; i++) pre2d[i][0] = 0;
    for (int i = 0; i <= M; i++) pre2d[0][i] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            pre2d[i][j] = grid[i-1][j-1] + pre2d[i-1][j] + pre2d[i][j-1] - pre2d[i-1][j-1];
        }
    }

    // for (int i = 0; i < 2*N; i++) {
    //     for (int j = 0; j < 2*)
    // }

    for (int i = 1; i+D < N; i++) {
        for (int j = 1; j+C < M; j++) {
            chamber[i-(B-D-1) + N][j-(A-C-1) + M] = rect(i, j, i+D-1, j+C-1);
            chamber2[i-(B-D-1) + N][j-(A-C-1) + M] = {j+1, i+1};
        }
    }
    
    for (int j = 0; j < 2*M; j++) {
        // [val, idx, x, y]
        deque<array<int, 4>> todo;
        int len = B-D-1;

        for (int i = 0; i < 2*N; i++) {
            if (chamber[i][j] > 0) {
                while (!todo.empty() && todo.back()[0] > chamber[i][j]) todo.pop_back();
                todo.push_back({chamber[i][j], i, chamber2[i][j].first, chamber2[i][j].second});
            }

            while (!todo.empty() && todo.front()[1] <= i-len) todo.pop_front();

            if (!todo.empty()) {
                chamber[i][j] = todo.front()[0];
                chamber2[i][j] = {todo.front()[2], todo.front()[3]};
            }
        }
    }

    for (int i = 0; i < 2*N; i++) {
        // [val, idx, x, y]
        deque<array<int, 4>> todo;
        int len = A-C-1;

        for (int j = 0; j < 2*M; j++) {
            if (chamber[i][j] > 0) {
                while (!todo.empty() && todo.back()[0] > chamber[i][j]) todo.pop_back();
                todo.push_back({chamber[i][j], j, chamber2[i][j].first, chamber2[i][j].second});
            }

            while (!todo.empty() && todo.front()[1] <= j-len) todo.pop_front();

            if (!todo.empty()) {
                chamber[i][j] = todo.front()[0];
                chamber2[i][j] = {todo.front()[2], todo.front()[3]};
            }
        }
    }

    int best = -1;
    int x1, y1, x2, y2;
    for (int i = 0; i < N-B+1; i++) {
        for (int j = 0; j < M-A+1; j++) {
            if (chamber[i+N][j+M] == 0) continue;
            int summ = rect(i, j, i+B-1, j+A-1) - chamber[i+N][j+M];
            if (summ > best) {
                best = summ;
                x1 = j+1, y1 = i+1;
                x2 = chamber2[i+N][j+M].first, y2 = chamber2[i+N][j+M].second;
            }
        }
    }

    cout << x1 << " " << y1 << endl << x2 << " " << y2;
}