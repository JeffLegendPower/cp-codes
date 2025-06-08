// https://codeforces.com/contest/1583/problem/D

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
    // Comment out for interactive problems
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);

    int N;
    cin >> N;

    int p[N];
    for (int i = 0; i < N; i++) p[i] = -1;
    int end = N;
    p[N - 1] = end;
    
    for (int i = 1; i < N; i++) {
        int target = i + N;

        cout << "? ";
        for (int j = 0; j < N - 1; j++)
            cout << i << " ";
        cout << N << endl;

        int res; cin >> res;
        if (res == 0) continue;
        else {
            end = i;
            p[N - 1] = i;
            break;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (i == end) continue;
        int addi = N + 1 - i;
        int addend = N + 1 - end;

        if (addi <= 0) break;

        cout << "? ";
        for (int j = 0; j < N - 1; j++) cout << addi << " ";
        cout << addend << endl;

        int res; cin >> res;
        if (res == 0) continue;
        else {
            p[res - 1] = i;
        }
    }

    cout << "! ";
    for (int i = 0; i < N; i++) cout << p[i] << " ";
    cout << endl;
}