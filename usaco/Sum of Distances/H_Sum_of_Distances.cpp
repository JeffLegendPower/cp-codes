// https://vjudge.net/contest/693462#problem/H

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

vector<vector<int>> graphs[50000];
vector<int> evendist[50000], odddist[50000];

ll MOD = 1e9 + 7;

ll binpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll modinv(ll x) {
    if (x == 0) return 1ll;
    return binpow(x, MOD - 2);
}

void bfs(int gidx) {
    evendist[gidx][0] = 0;

    // {v, dist}
    deque<pii> todo;
    todo.push_back({0, 0});
    while (!todo.empty()) {
        auto [v, d] = todo.front();
        todo.pop_front();

        for (int x : graphs[gidx][v]) {
            if (d&1) {
                if (evendist[gidx][x] != -1) continue;
                evendist[gidx][x] = d+1;
            } else {
                if (odddist[gidx][x] != -1) continue;
                odddist[gidx][x] = d+1;
            }
            todo.push_back({x, d+1});
        }
    }
}

ll calcans(vector<vector<int>>& dists, vector<int>& N, int K) {
    // num tuples with max dist <= i
    ll numtup[200001];

    // for graph k numdist[k], num nodes with dist <= i
    vector<ll> numdist[K];

    sort(N.begin(), N.end(), greater<int>());
    sort(dists.begin(), dists.end(), [](vector<int> &one, vector<int> &two) {
        return one.size() > two.size();
    });

    numtup[0] = 1;
    for (int i = 0; i < K; i++) {
        numdist[i].assign(2*N[i] + 1, 0);
        for (int dist : dists[i]) numdist[i][dist]++;
        for (int j = 1; j <= 2*N[i]; j++) {
            numdist[i][j] += numdist[i][j-1];
        }

        if (numdist[i][2*N[i]] == 0) return 0ll;

        numtup[0] = (numtup[0] * numdist[i][0]) % MOD;
    }

    for (int i = 1; i <= 200000; i++) {
        ll num = max(1ll, numtup[i-1]);
        for (int j = 0; j < K; j++) {
            if (2*N[j] < i) break;

            if (numdist[j][i] == 0) {
                num = 0;
                break;
            }

            num = (num * modinv(numdist[j][i-1])) % MOD;
            num = (num * numdist[j][i]) % MOD;
        }

        numtup[i] = num;
    }

    ll ans = 0;
    for (ll i = 1; i <= 200000; i++) {
        ll diff = (i * (numtup[i] - numtup[i-1])) % MOD;
        ans = (ans + diff) % MOD;
    }
    return ans;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int K; cin >> K;

    vector<int> N(K);
    for (int k = 0; k < K; k++) {
        int M;
        cin >> N[k] >> M;
        graphs[k].resize(N[k]);
        while (M--) {
            int u, v; cin >> u >> v;
            u--, v--;
            graphs[k][u].push_back(v);
            graphs[k][v].push_back(u);
        }
        evendist[k].assign(N[k], -1);
        odddist[k].assign(N[k], -1);

        bfs(k);
    }

    vector<int> N2(N);
    vector<vector<int>> dists;
    dists.resize(K);
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N[k]; i++) {
            if (evendist[k][i] == -1) {
                N2[k]--;
            } else {
                dists[k].push_back(evendist[k][i]);
            }
        }
    }

    ll ans = calcans(dists, N2, K);

    dists.clear();
    N2 = vector<int>(N);
    dists.resize(K);
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N[k]; i++) {
            if (odddist[k][i] == -1) {
                N2[k]--;
            } else dists[k].push_back(odddist[k][i]);
        }
    }

    ans = (ans + calcans(dists, N2, K)) % MOD;

    dists.clear();
    N2 = vector<int>(N);
    dists.resize(K);
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N[k]; i++) {
            if (min(evendist[k][i], odddist[k][i]) == -1) {
                N2[k]--;
            } else {
                dists[k].push_back(max(evendist[k][i], odddist[k][i]));
            }
        }
    }

    ans = (ans + MOD - calcans(dists, N2, K)) % MOD;

    cout << ans;
}