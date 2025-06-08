// https://usaco.org/index.php?page=viewproblem&cpid=1436

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>

struct upd {
    int i, j;
};

const int MAXN = 1000;
int N;
char grid[MAXN][MAXN];
bool usable[MAXN][MAXN];
int num = 0;

void update(int i, int j) {
    if (!usable[i][j]) num--;
    usable[i][j] = true;

    if (i > 0 && !usable[i - 1][j] && (grid[i - 1][j] == 'D' || grid[i - 1][j] == '?')) update(i - 1, j);
    if (i < N - 1 && !usable[i + 1][j] && (grid[i + 1][j] == 'U' || grid[i + 1][j] == '?')) update(i + 1, j);
    if (j > 0 && !usable[i][j - 1] && (grid[i][j - 1] == 'R' || grid[i][j - 1] == '?')) update(i, j - 1);
    if (j < N - 1 && !usable[i][j + 1] && (grid[i][j + 1] == 'L' || grid[i][j + 1] == '?')) update(i, j + 1);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // If we reverse our updates, once a conveyor becomes usable, it stays usable
    // And once a conveyor becomes a wildcard, it stays a wildcard
    // Also, any conveyor that connects to a usable conveyor is also usable
    // So by reversing our updates, we can first compute which tiles are usable in O(n^2) at the end state
    // and by going back an update we can check to see if a tile becomes usable, and then see which unusable tiles that this update turn usable
    // and this effect propagates, but it amortizes to a total of O(n^2) calls to update()

    int Q; cin >> N >> Q;
    num = N*N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) grid[i][j] = '?';
    }

    vector<upd> qs;
    for (int i = 0; i < Q; i++) {
        char c;
        upd cur; cin >> cur.i >> cur.j >> c;
        cur.i--; cur.j--;
        qs.push_back(cur);

        grid[cur.i][cur.j] = c;
    }
    reverse(qs.begin(), qs.end());

    for (int i = 0; i < N; i++) {
        if (grid[i][0] == 'L' || grid[i][0] == '?') update(i, 0);
        if (grid[i][N - 1] == 'R' || grid[i][N - 1] == '?') update(i, N - 1);
        if (grid[0][i] == 'U' || grid[0][i] == '?') update(0, i);
        if (grid[N - 1][i] == 'D' || grid[N - 1][i] == '?') update(N - 1, i);
    }

    vector<int> unusables;
    int tx = 0;
    for (auto [i, j] : qs) {
        unusables.push_back(num);

        grid[i][j] = '?';
        if (usable[i][j]) continue;
        
        if (i > 0 && usable[i - 1][j]) update(i, j);
        else if (i < N - 1 && usable[i + 1][j]) update(i, j);
        else if (j > 0 && usable[i][j - 1]) update(i, j);
        else if (j < N - 1 && usable[i][j + 1]) update(i, j);
        
        else if (i == 0) update(i, j);
        else if (i == N - 1) update(i, j);
        else if (j == 0) update(i, j);
        else if (j == N - 1) update(i, j);
    }

    for (int i = Q - 1; i >= 0; i--) {
        cout << unusables[i];
        if (i > 0) cout << endl;
    }
}