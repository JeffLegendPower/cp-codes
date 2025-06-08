// https://codeforces.com/contest/1860/problem/D

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
    string s;
    cin >> s;
    int N = s.size();

    ll ones = 0, zeros = 0;
    ll onezeros = 0, zeroones = 0;
    for (int i = 0; i < N; i++) {
        if (s[i] == '1') {
            ones++;
            zeroones += zeros;
        } else {
            zeros++;
            onezeros += ones;
        }
    }

    cout << N << " " << ones << " " << zeros << endl;

    if (onezeros - zeroones == 0) {
        cout << 0 << endl;
        return 0;
    }

    if (N % 2 == 0) {
        int opers = 0;
        for (int i = 0; i < N / 2; i++) {
            if (s[i] != s[N - i - 1]) opers++;
        }

        cout << opers / 2 << endl;
    } else {
        int opers = 0;
        char target = (ones % 2 == 0 ? '1' : '0');
        int leftidx = 0, rightidx = N - 1;
        vector<pii> edges;

        for (int i = 0; i < N; i++) {
            // if (s[i] != s[N - i - 1]) opers++;
            if (s[i] == target) {
                int dist = (target == '1' ? ones / 2 : zeros / 2);
                if (leftidx < dist) {
                    edges.push_back({i, leftidx});
                    leftidx++;
                } else {
                    edges.push_back({i, rightidx});
                    rightidx--;
                }
            }
        }
        for (pii edge : edges) {
            cout << edge.first + 1 << " " << edge.second + 1 << endl;
        }

        // if (ones % 2 == 0 && s[N / 2] == '1') opers++;
        // if (zeros % 2 == 0 && s[N / 2] == '0') opers++;

        cout << opers / 2 << endl;
    }
}