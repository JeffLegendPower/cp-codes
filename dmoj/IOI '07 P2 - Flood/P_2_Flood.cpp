// https://dmoj.ca/problem/ioi07p2

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

bool flooded[100000];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    vector<pii> points(N);
    for (int i = 0; i < N; i++) cin >> points[i].first >> points[i].second;

    int W; cin >> W;
    vector<pii> walls(W);
    vector<vector<int>> wallpts(N);

    auto cmp = [&walls, &points](int one, int two) {
        pii p1 = points[walls[one].first];
        pii p2 = points[walls[two].first];

        if (p1.first == p2.first) return p1.second < p2.second;
        else return p1.first < p2.first;
    };
    set<int, decltype(cmp)> walls2(cmp);

    for (int i = 0; i < W; i++) {
        cin >> walls[i].first >> walls[i].second;
        walls[i].first--; walls[i].second--;

        pii p1 = points[walls[i].first], p2 = points[walls[i].second];
        if (p2.first < p1.first || (p2.first == p1.first && p2.second < p1.second)) {
            swap(walls[i].first, walls[i].second);
        }

        walls2.insert(i);

        wallpts[walls[i].first].push_back(i);
        wallpts[walls[i].second].push_back(i);
    }

    for (int i = 0; i < N; i++) {
        sort(wallpts[i].begin(), wallpts[i].end(), [&walls, &points, &i](int one, int two) {
            pii p1 = points[walls[one].first];
            pii p2 = points[walls[two].first];
            if (walls[one].first == i) points[walls[one].second];
            if (walls[two].first == i) points[walls[two].second];

            int score1 = 3, score2 = 3;
            if (p1.first < points[i].first) score1 = 0;
            else if (p1.second > points[i].second) score1 = 1;
            else if (p1.first > points[i].first) score1 = 2;

            if (p2.first < points[i].first) score2 = 0;
            else if (p2.second > points[i].second) score2 = 1;
            else if (p2.first > points[i].first) score2 = 2;

            return score1 < score2;
        });
    }

    vector<int> ans;
    for (int i = 0; i < N; i++) {
        if (wallpts[i].size() == 1) {
            ans.push_back(wallpts[i][0]);
            walls2.erase(wallpts[i][0]);
            wallpts[i].erase(wallpts[i].begin());
        }
    }

    while (!walls2.empty()) {
        int start = *walls2.begin();
        
        flooded[start] = true;
        int cur = walls[start].second;
        int curwall = start;
        wallpts[cur].erase(remove(wallpts[cur].begin(), wallpts[cur].end(), start), wallpts[cur].end());
        walls2.erase(start);

        while (cur != walls[start].first) {

            int next = wallpts[cur][0];
            wallpts[cur].erase(remove(wallpts[cur].begin(), wallpts[cur].end(), next), wallpts[cur].end());
            walls2.erase(next);

            if (walls[next].first == cur) cur = walls[next].second;
            else cur = walls[next].first;

            
        }
    }
}