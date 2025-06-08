// https://codeforces.com/contest/1804/problem/D

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


int main() {
    int N, M;
    cin >> N >> M;

    int most = 0, least = 0;

    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;

        // val, num twos
        vector<pii> dpmin(M + 1, {1e6, 0});
        // val, num ones
        vector<pii> dpmax(M + 1, {0, 0});
        dpmin[0] = {0, 0};

        int doubles = 0;
        for (int j = 0; j < M; j++) {
            if (row[j] - '0') {
                dpmin[j + 1].first = min(dpmin[j + 1].first, dpmin[j].first + 1);
                if (j == 0) {
                    dpmax[1] = {1, 1};
                }
            } else {
                dpmin[j + 1].first = min(dpmin[j + 1].first, dpmin[j].first);
                if (j == 0) {
                    dpmax[1] = {0, 1};
                }
            }

            if (j == 0) continue;


            pii doublecost = dpmin[j - 1];
            if ((row[j] - '0') || (row[j - 1] - '0')) doublecost.first++;
            doublecost.second++;

            if (doublecost < dpmin[j + 1] && doublecost.second <= M / 4) {
                dpmin[j + 1] = doublecost;
            }

            dpmax[j + 1] = dpmax[j - 1];
            if ((row[j] - '0') || (row[j - 1] - '0')) dpmax[j + 1].first++;
            pii singlecost = dpmax[j];
            if (row[j] - '0') singlecost.first++;
            singlecost.second++;

            int singlesreq = singlecost.second;
            // if (j % 2) singlesreq--;
            // bool condition = singlecost.first - dpmax[j + 1].first >= singlecost.second - dpmax[j + 1].second;
            bool condition = singlecost.first > dpmax[j + 1].first;
            if (singlecost.first == dpmax[j + 1].first && singlecost.second < dpmax[j + 1].second) condition = true;
            // if (singlecost.first - dpmax[j + 1].first >= singlecost.second - dpmax[j + 1].second)
            // if (singlecost.first > dpmax[j + 1].first && singlecost.second < M / 2) {
            if (condition && singlecost.second <= M / 2) {
                // singlecost.second++;
                dpmax[j + 1] = singlecost;
            }

            // 2, 1, 2, 0
            cout << dpmax[j + 1].first << " " << dpmax[j + 1].second << " " << singlecost.second << endl;
        }

        // for (int j = 0; )
        

        least += dpmin[M].first;
        most += dpmax[M].first;
        // cout << dpmax[M].second << endl;
    }

    cout << least << " " << most << endl;
}