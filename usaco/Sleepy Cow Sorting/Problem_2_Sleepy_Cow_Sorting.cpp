// https://usaco.org/index.php?page=viewproblem2&cpid=898

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const int& a, const int& b) const {
        return a < b;
    }
};

typedef tree<int, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("sleepy");

    int N;
    cin >> N;

    int a[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        a[i];
    }

    int numset = 1;
    ordered_set oset;
    oset.insert(a[N - 1]);

    for (int i = N - 2; i >= 0; i--) {
        if (a[i] > a[i + 1]) break;
        numset++;
        oset.insert(a[i]);
    }

    int num = N - numset;
    cout << num << endl;
    for (int i = 0; i < num; i++) {
        int k = N - 1;
        k -= numset;
        k += oset.order_of_key(a[i]);

        cout << k;
        if (i < num - 1) cout << " ";

        numset++;
        oset.insert(a[i]);
    }
}