// https://codeforces.com/contest/1525/problem/C

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


struct comp {
    bool operator() (plli a, plli b) {
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


struct robt {
    ll x;
    char dir;
    int collision = -1;
    int idx;
    int idx2;
}; struct collision {
    int one, two;
    ll time;
};

void solve(int N, ll M, vector<robt> &robots) {
    sort(robots.begin(), robots.end(), [](robt one, robt two) {
        return one.x < two.x;
    });

    vector<collision> collisions;

    vector<plli> bots;
    int i = -1;
    for (robt robot : robots) {
        i++;
        if (bots.empty()) {
            if (robot.dir == 'R') bots.push_back({robot.x, i});
            else bots.push_back({-robot.x, i});
            continue;
        }

        if (robot.dir == 'R') bots.push_back({robot.x, i});
        else {
            plli other = bots.back();
            bots.pop_back();
            ll time = abs(robot.x - other.first) / 2;
            robots[i].collision = time;
            robots[other.second].collision = time;
        }
    }

    for (int i = bots.size() - 2; i >= 0; i -= 2) {
        plli one = bots[i + 1];
        plli two = bots[i];
        if (one.first < M) one.first = 2 * M - one.first;

        ll time = abs(one.first - two.first) / 2;
        robots[one.second].collision = time;
        robots[two.second].collision = time;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        robt robots[N];
        for (int i = 0; i < N; i++) {
            cin >> robots[i].x;
            robots[i].idx2 = i;
        } for (int i = 0; i < N; i++) cin >> robots[i].dir;

        vector<robt> evenrobots, oddrobots;
        for (int i = 0; i < N; i++) {
            if (robots[i].x % 2 == 0) {
                robt cur = robots[i];
                cur.idx = evenrobots.size();
                evenrobots.push_back(cur);
            } else {
                robt cur = robots[i];
                cur.idx = oddrobots.size();
                oddrobots.push_back(cur);
            }
        }

        if (evenrobots.size() > 0) solve(evenrobots.size(), M, evenrobots);
        if (oddrobots.size() > 0) solve(oddrobots.size(), M, oddrobots);

        for (robt cur : evenrobots) {
            robots[cur.idx2].collision = cur.collision;
        } 
        for (robt cur : oddrobots) {
            robots[cur.idx2].collision = cur.collision;
        }

        for (int i = 0; i < N; i++) cout << robots[i].collision << " ";
        cout << endl;
    }
}