// https://atcoder.jp/contests/abc363/tasks/abc363_d

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
    ll N;
    cin >> N;
    N--;

    int digits = 1;

    
    ll count = 9;
    while (true) {
        if (digits == 1) {
            count = 10;
        } else if (digits % 2 == 1) count *= 10;
        
        if (count > N) break;
        N -= count;
        
        if (digits == 1) count = 9;
        digits++;
    }

    if (digits == 1) {
        cout << N;
        return 0;
    }

    string ans = "";

    // cout << N << endl;

    // most leftward to most middle digit
    for (int i = 0; i < (digits + 1) / 2; i++) {
        if (i == 0) count /= 9;
        else count /= 10;

        int digit = N / count;

        if (i == 0) ans += digit + '1';
        else ans += digit + '0';


        // cout << digit << " " << count << endl;
        N %= count;
    }

    int start = ans.size() - 1;
    if (digits % 2 == 1) start--;
    for (int i = start; i >= 0; i--) ans += ans[i];
    cout << ans;
}