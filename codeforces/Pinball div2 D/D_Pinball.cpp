// https://codeforces.com/contest/1937/problem/D

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
        ll N;
        cin >> N;
        string s;
        cin >> s;

        vector<ll> leftdistssuff, rightdistspre;
        for (ll i = N - 1; i >= 0; i--) {
            if (s[i] == '<') {
                ll num = 0;
                if (leftdistssuff.size() > 0) num += leftdistssuff.back();
                leftdistssuff.push_back(num + i + 1);
                // cout << num + i + 1 << endl;
            }
        } for (ll i = 0; i < N; i++) {
            if (s[i] == '>') {
                ll num = 0;
                if (rightdistspre.size() > 0) num += rightdistspre.back();
                rightdistspre.push_back(num + N - i);
                // cout << num + N - i << endl;
            }
        }

        int rights = 0, lefts = leftdistssuff.size();
        for (int i = 0; i < N; i++) {
            int num = min(rights, lefts);
            ll cost = 0;
            // cout << i << endl;
            if (num > 0) {
                cost += rightdistspre[rights - num];
                if (rights - num - 1 >= 0) cost -= rightdistspre[rights - num - 1];
                cost -= num * (N - i);

                // cout << i << " " << cost << " " << rights << " " << num << endl;
                cout << i << " " << cost << endl;
                
                cost += leftdistssuff[lefts - num];
                // cout << i << " " << cost << endl;
                if (lefts - num - 1 >= 0) cost -= leftdistssuff[lefts - num - 1];
                // cout << i << " " << cost << endl;
                // if (lefts - num - 1)
                cost -= num * i;
                cout << i << " " << cost << endl;
            }

            if (s[i] == '>') rights++;
            else lefts--;
        }

        // cout << leftdistssuff[0];
        
        // for (int i = leftdists.size() - 1; i >= 0; i--) {
        //     if (i == leftdists.size() - 1) leftdistssuff[i] = leftdists[i];
        //     else leftdistssuff[i] = leftdists[i] + leftdistssuff[i + 1];
        // }

        // vector<ll> rightdists;
        // vector<ll> rightdistspre;
        // // ll subtrleft = 0, addright = 0;
        // int leftidx = 
        // for (int i = 0; i < N; i++) {
        //     subtrleft += leftdists.size();
        //     addright += rightdists.size();
        //     if (s[i] == '<') {
        //         leftdists.pop_back();
        //         leftdistssuff.pop_back();
        //     } else {
        //         rightdists.push_back(0);
        //         rightdistssuff
        //     }

        //     int least = min(rightdists.size(), leftdists.size());
        // }
    }
}