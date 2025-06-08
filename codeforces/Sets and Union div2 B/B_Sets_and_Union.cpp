// https://codeforces.com/contest/1882/problem/B

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
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<set<int>> ss;
        
        int stotal[51];

        // i: which number is removed, j: count of each
        int totals[50][50];

        for (int i = 0; i <= 50; i++) stotal[i] = 0;

        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) totals[i][j] = 0;
        }

        for (int i = 0; i < N; i++) {
            ss.push_back({});
            vector<int> s1;
            set<int> s;
            int k;
            cin >> k;

            for (int j = 0; j < k; j++) {
                int si;
                cin >> si;
                s.insert(si);
                s1.push_back(si);
                stotal[si]++;
                // cout << k << endl;
            }

            for (int j = 0; j < 50; j++) {
                if (s.find(j + 1) != s.end()) continue;
                for (int l = 0; l < k; l++) {
                    totals[j][s1[l] - 1]++;
                }
            }
        }

        int bound = 0;
        for (int i = 0; i <= 50; i++) if (stotal[i] > 0) bound++;

        int highest = 0;
        for (int i = 0; i < 50; i++) {
            int count = 0;
            for (int j = 0; j < 50; j++) {
                if (totals[i][j] > 0) count++;
                // cout << totals[i][j] << " ";
            }
            // cout << count << " " << i << endl;
            // cout << endl;
            if (count < bound)
            highest = max(highest, count);
        }

        cout << highest << endl;

        // int best = 0;

        // for (int i = 0; i < N; i++) {
        //     int total = 0;
        //     for (int j = 1; j <= 50; j++) {
        //         if (ss[i].find(j) == ss[i].end()) {
        //             if (stotal[j] > 0) total++;
        //         } else if (stotal[j] > 1) total++;
        //     }

        //     // cout << total << endl;

        //     if (total < highest) best = max(best, total);
        // }

        // cout << best << endl;
    }
}