// https://dmoj.ca/problem/ioi01p6

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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


int R, N;
vector<vector<int>> target;
map<int, int> mapp;

vector<vector<int>> ways;

vector<int> cur;
vector<vector<int>> curans;

vector<int> rowof;
vector<int> colof;

int len = 0;
vector<int> used;

int mmm = 0;
void run() {
    mmm++;
    if (len == N) {
        bool equal = curans.size() == target.size();
        if (!equal) return;
        for (int i = 0; i < curans.size(); i++) {
            if (curans[i].size() != target[i].size()) equal = false;
            if (!equal) return;

            for (int j = 0; j < curans[i].size(); j++) {
                if (curans[i][j] != target[i][j]) equal = false;
            }

            if (!equal) return;
        }

        ways.push_back({});
        for (int x : cur) ways[ways.size()-1].push_back(x);

        return;
    }

    vector<vector<int>> prev(curans);
    
    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        used[i] = true;
        len++;
        cur.push_back(i);

        int row = 0;
        int num = i;
        bool bad = false;

        while (true) {
            if (curans.size() == row) curans.push_back({});
            int idx = 0;

            if (row >= target.size()) {
                bad = true;
                break;
            }

            if (row > rowof[num]) {
                bad = true;
                break;
            }

            if (rowof[num] > row + (N-len)) {
                bad = true;
                break;
            }

            if (curans[row].empty() || num > curans[row].back()) {
                if (row == rowof[num] && curans[row].size() > colof[num]) {
                    bad = true;
                    break;
                }

                curans[row].push_back(num);
                if (curans[row].size() > target[row].size()) bad = true;

                if (target[row].size() > curans[row].size() + (N-len)) bad = true;
                break;
            }

            while (idx < curans[row].size()) {
                if (row == rowof[num] && idx > colof[num]) {
                    bad = true;
                    break;
                }

                if (curans[row][idx] < num) {
                    idx++;
                    continue;
                }
                swap(num, curans[row][idx]);
                break;
            }

            if (target[row].size() > curans[row].size() + (N-len)) {
                bad = true;
                break;
            }
            row++;
        }       

        if (!bad) run();
        curans = vector<vector<int>>(prev);

        used[i] = false;
        len--;
        cur.pop_back();
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> R;
    target.resize(R);

    vector<int> ids;
    for (int i = 0; i < R; i++) {
        int l; cin >> l;
        for (int j = 0; j < l; j++) {
            int k; cin >> k;
            ids.push_back(k);
            target[i].push_back(k);
        }
    }
    N = ids.size();
    rowof.resize(N);
    colof.resize(N);
    used.assign(N, false);

    sort(ids.begin(), ids.end());
    for (int i = 0; i < N; i++) mapp[ids[i]] = i;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < target[i].size(); j++) {
            target[i][j] = mapp[target[i][j]];
            rowof[target[i][j]] = i;
            colof[target[i][j]] = j;
            // cout << rowof[target[i][j]] << endl;
        }
    }

    run();

    // cout << ways.size();
    cout << mmm << endl;

    for (int i = 0; i < ways.size(); i++) {
        for (int x : ways[i]) cout << ids[x] << " ";
        cout << endl;
    }
}