// https://codeforces.com/contest/1973/problem/C

// We need to notice that it's always possible to achieve N / 2 - 1 maxima
// As the ends can't be maxima and every other (first or second) index can be
// Now to do this we just need to choose the alternating subsequence that contains N
// As that way it's always possible to create p + q with N / 2 - 1 maxima
// And then we can greedily set elements of q

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

struct num {
    int ai;
    int idx;
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        num a[N];
        int q[N];
        int Nidx;
        for (int i = 0; i < N; i++) {
            cin >> a[i].ai;
            a[i].idx = i;
            if (a[i].ai == N) Nidx = i;
            q[i] = -1;
        }

        vector<num> maxs, mins;
        if (Nidx % 2 == 0) {
            for (int i = 2; i < N; i += 2) maxs.push_back(a[i]);
            for (int i = 1; i < N; i += 2) mins.push_back(a[i]);
        } else {
            for (int i = 1; i < N - 1; i += 2) maxs.push_back(a[i]);
            for (int i = 0; i < N; i += 2) mins.push_back(a[i]);
        }

        sort(maxs.begin(), maxs.end(), [](num one, num two) {
            return one.ai < two.ai;
        }); sort(mins.begin(), mins.end(), [](num one, num two) {
            return one.ai > two.ai;
        });

        for (int i = 0; i < mins.size(); i++) {
            q[mins[i].idx] = i + 1;
        } for (int i = 0; i < maxs.size(); i++) {
            q[maxs[i].idx] = N - i;
        }
        for (int i = 0; i < N; i++) {
            if (q[i] == -1) q[i] = N / 2 + 1;
            cout << q[i] << " ";
        }
        cout << endl;
    }
}