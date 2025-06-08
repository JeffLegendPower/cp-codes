// https://codeforces.com/contest/1990/problem/C

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

        int a[N];
        ll sum = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            sum += a[i];
        }

        map<int, int> freq;
        int mad = 0;
        for (int i = 0; i < N; i++) {
            freq[a[i]]++;
            if (freq[a[i]] > 1) mad = max(mad, a[i]);
            a[i] = mad;
            // cout << a[i] << endl;
        }

        freq.clear();

        mad = 0;
        for (int i = 0; i < N; i++) {
            sum += a[i];
            freq[a[i]]++;
            if (freq[a[i]] > 1) mad = max(mad, a[i]);
            a[i] = mad;
            // cout << a[i] << endl;
        }

        for (int i = N - 1; i >= 0; i--) {
            ll num = a[i];
            ll count = 0;
            int j = i;
            for (; j >= 0; j--) {
                if (a[j] == a[i]) count++;
                else break;
            }

            // cout << j << endl;
            // cout << a[i] << " " << i << " " << count << endl;

            ll dist = N - i - 1;
            i = j + 1;

            if (count == 1) {
                sum += a[i];
                continue;
            }

            ll beforesum = sum;
            sum += dist * count * num;
            // cout << dist << " " << i << " " << a[i] << endl;

            sum += num * count * (1 + count) / 2;

            // cout << sum - beforesum << endl;
        }

        cout << sum << endl;
    }
}