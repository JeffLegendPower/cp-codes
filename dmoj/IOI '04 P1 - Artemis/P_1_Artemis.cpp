// https://dmoj.ca/problem/ioi04p1

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

#define tree array<int, 3>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, T;
    cin >> N >> T;

    // trees[i][j]: j=0 is x, j=1 is y, j=2 is i
    tree trees[N];
    for (int i = 0; i < N; i++) {
        cin >> trees[i][0] >> trees[i][1];
        trees[i][2] = i;
    }

    sort(trees, trees + N, [](tree &one, tree &two) {
        return one[0] < two[0];
    }); for (int i = 0; i < N; i++) trees[i][0] = i;

    sort(trees, trees + N, [](tree &one, tree &two) {
        return one[1] < two[1];
    }); for (int i = 0; i < N; i++) trees[i][1] = i;

    int mintrees = 1e9;
    int t1 = 0, t2 = 0;

    int rects[N];
    for (int i = 0; i < N; i++) {
        rects[i] = 1;
        for (int j = 0; j < i; j++) rects[i] += trees[j][0] <= trees[i][0];
    }

    int verts[N], hors[N];
    for (int i = 0; i < N; i++) {
        if (rects[i] < T) continue;

        for (int j = 0; j < N; j++) {
            verts[trees[j][1]] = trees[j][0] <= trees[i][0];
            hors[trees[j][0]] = trees[j][1] <= trees[i][1];
        } for (int j = 1; j < N; j++) {
            verts[j] += verts[j-1];
            hors[j] += hors[j-1];
        }

        for (int j = 0; j < i; j++) {
            if (trees[j][0] >= trees[i][0]) continue;

            int numtrees = rects[i] + rects[j] - verts[trees[j][1]] - hors[trees[j][0]] + 1;

            if (numtrees >= T && numtrees < mintrees) {
                mintrees = numtrees;
                t1 = trees[i][2], t2 = trees[j][2];
            }
        }
    }
    
    cout << t1+1 << " " << t2+1 << endl;
}