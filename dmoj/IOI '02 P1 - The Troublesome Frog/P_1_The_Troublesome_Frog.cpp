// https://dmoj.ca/problem/ioi02p1

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

struct HASH {
    size_t operator()(const pair<int,int> &x) const {
        return hash<long long>()(((long long) x.first)^(((long long) x.second)<<32));
    }
};

int R, C, N;
vector<pii> rice;
unordered_map<pii, int, HASH> ricemap;

bool searched[5000][5000];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> R >> C >> N;
    for (int i = 0; i < N; i++) {
        pii cur; cin >> cur.first >> cur.second;
        rice.push_back(cur);
    }
    sort(rice.begin(), rice.end());
    for (int i = 0; i < N; i++) ricemap[rice[i]] = i;

    int best = 0;
    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            if (searched[i][j]) continue;
            int len = 2;
            int a = i, b = j;
            int dx = rice[b].first - rice[a].first, dy = rice[b].second - rice[a].second;
            int startx = rice[a].first, starty = rice[a].second;
            int x = rice[b].first, y = rice[b].second;

            searched[a][b] = true;
            int c = b;
            while (true) {
                pii next = {x+dx, y+dy};
                if (ricemap.find(next) == ricemap.end()) break;
                len++;
                x += dx, y += dy;
                c = ricemap[next];
                searched[b][c] = true;
                b = c;
            }

            bool valid =
                (startx-dx <= 0 || startx-dx > R || starty-dy <= 0 || starty-dy > C) 
                && (x+dx <= 0 || x+dx > R || y+dy <= 0 || y+dy > C);

            // cout << valid << " " << len << " " << " " << startx << " " << starty << " " << x << " " << y << endl;

            if (valid && len >= 3) best = max(best, len);
        }
    }

    cout << best;
}