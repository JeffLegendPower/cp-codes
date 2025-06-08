// https://codeforces.com/contest/1296/problem/E2

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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
    int N;
    cin >> N;
    string s;
    cin >> s;

    int c[N];
    int colors = 1;
    c[N - 1] = 1;

    int colorchar[26];
    for (int i = 0; i < 26; i++) colorchar[i] = 1;

    for (int i = N - 1; i >= 0; i--) {
        c[i] = colorchar[s[i] - 'a'];
        colors = max(colors, c[i]);
        // cout << s[i] - 'a' << endl;
        // cout << c[i] << endl;
        for (int j = s[i] - 'a' + 1; j < 26; j++) {
            colorchar[j] = max(colorchar[j], c[i] + 1);
            // cout << colorchar[i] << " " << i << endl;
        }
    }
    
    cout << colors << endl;
    for (int i = 0; i < N; i++) cout << c[i] << " ";
}