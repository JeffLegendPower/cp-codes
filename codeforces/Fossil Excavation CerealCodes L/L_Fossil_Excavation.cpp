// https://codeforces.com/gym/103886/problem/L

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

const int MAXN = 500, MAXK = 12;
int N, K;
ll M;
char grid[MAXN][MAXN];
int fgrid[MAXN][MAXN];
bool searched[MAXN][MAXN];
vector<ll> fossils[MAXK];
ll dists[MAXK][MAXK];
ll basedist[MAXK];

// min fuel to pick up subset of fossils i and ending at fossil j
ll dp[1<<MAXK][MAXK];
// min fuel to move subset of fossils i to base
ll dp2[1<<MAXK];

void bfs(int fossil) {
    int x = fossils[fossil][0], y = fossils[fossil][1];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) searched[i][j] = false;
    }
    
    deque<vector<ll>> q;
    q.push_back({x, y, grid[x][y] == '+'});
    searched[x][y] = true;
    while (!q.empty()) {
        vector<ll> cur = q.front();
        q.pop_front();
        ll xi = cur[0], yi = cur[1], d = cur[2];

        int fos = fgrid[xi][yi];
        if (fos >= 0) {
            dists[fossil][fos] = d;
        } if (xi == 0 && yi == 0) {
            basedist[fossil] = d;
        }

        if (xi + 1 < N && !searched[xi + 1][yi] && grid[xi + 1][yi] != '#') {
            searched[xi + 1][yi] = true;
            if (grid[xi + 1][yi] == '.') q.push_front({xi + 1, yi, d});
            else q.push_back({xi + 1, yi, d + 1});
        } 
        if (xi - 1 >= 0 && !searched[xi - 1][yi] && grid[xi - 1][yi] != '#') {
            searched[xi - 1][yi] = true;
            if (grid[xi - 1][yi] == '.') q.push_front({xi - 1, yi, d});
            else q.push_back({xi - 1, yi, d + 1});
        } 
        if (yi + 1 < N && !searched[xi][yi + 1] && grid[xi][yi + 1] != '#') {
            searched[xi][yi + 1] = true;
            if (grid[xi][yi + 1] == '.') q.push_front({xi, yi + 1, d});
            else q.push_back({xi, yi + 1, d + 1});
        } 
        if (yi - 1 >= 0 && !searched[xi][yi - 1] && grid[xi][yi - 1] != '#') {
            searched[xi][yi - 1] = true;
            if (grid[xi][yi - 1] == '.') q.push_front({xi, yi - 1, d});
            else q.push_back({xi, yi - 1, d + 1});
        } 
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> K >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            fgrid[i][j] = -1;
        }
    }

    for (int i = 0; i < K; i++) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        x--, y--;
        fossils[i] = {x, y, w};
        fgrid[x][y] = i;
    }
    for (int i = 0; i < K; i++) {
        bfs(i);
        dp[1<<i][i] = basedist[i];
    }

    for (int sz = 2; sz <= K; sz++) {
        for (int msk = 0; msk < 1<<K; msk++) {
            if (__builtin_popcount(msk) != sz) continue;

            for (int fos = 0; fos < K; fos++) {
                dp[msk][fos] = 1e18;
                if (!(msk&(1<<fos))) continue;
                int prev = msk^(1<<fos);
                for (int fos2 = 0; fos2 < K; fos2++) {
                    if (!(prev&(1<<fos2))) continue;
                    dp[msk][fos] = min(dp[msk][fos], dp[prev][fos2] + dists[fos2][fos]);
                }
            }
        }
    }
    for (int msk = 0; msk < 1<<K; msk++) {
        dp2[msk] = 1e18;
    }
    dp2[0] = 0;

    for (int msk = 0; msk < 1<<K; msk++) {
        for (int msk2 = 0; msk2 < 1<<K; msk2++) {
            ll w = 0;
            for (int k = 0; k < K; k++) if (msk2&(1<<k)) w += fossils[k][2];
            if (w > M) continue;

            for (int k = 0; k < K; k++) {
                if (!(msk2&(1<<k))) continue;
                dp2[msk | msk2] = min(dp2[msk | msk2], dp2[msk] + dp[msk2][k] + basedist[k]);
            }
        }
    }

    cout << dp2[(1<<K) - 1] << endl;
}