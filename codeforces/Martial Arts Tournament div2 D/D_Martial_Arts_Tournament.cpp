// https://codeforces.com/contest/1626/problem/D

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
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int a[N];
        for (int i = 0; i < N; i++) cin >> a[i];
        sort(a, a + N);
        int starts[N];
        starts[0] = 0;
        for (int i = 1; i < N; i++) {
            if (a[i] == a[i - 1]) starts[i] = starts[i - 1];
            else starts[i] = i;
        }

        ll least = 1e18;
        for (int one = 0; one <= 18; one++) {
            for (int two = 0; two <= 18; two++) {
                for (int three = 0; three <= 18; three++) {
                    ll Ni = N;
                    ll cost = 0;

                    int first = 1<<one;
                    int second = 1<<two;
                    int third = 1<<three;


                    if (first >= Ni) {
                        least = min(least, first - Ni + second + third);
                        continue;
                    }
                    Ni -= starts[first];
                    int curidx = starts[first];
                    first -= starts[first];

                    if (second >= Ni) {
                        least = min(least, first + second - Ni + third);
                        continue;
                    }
                    int next = starts[curidx + second];
                    Ni -= next - curidx;
                    second -= next - curidx;

                    // if (one == 1 && two == 0 && three == 0) {
                    //     cout << first << " " << two << " " << three << endl;
                    //     cout << curidx << " " << Ni << endl;
                    // }   
                    if (third < Ni) {
                        continue;
                    }

                    least = min(least, first + second + third - Ni);
                }
            }
        }

        cout << least << endl;
    }
}