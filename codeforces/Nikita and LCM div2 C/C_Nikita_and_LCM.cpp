// https://codeforces.com/contest/1977/problem/C

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


int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        set<ll> a2;
        ll most = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            a2.insert(a[i]);
            most = max(most, a[i]);
        }

        bool alldivides = true;
        for (int i = 0; i < N; i++) {
            if (most % a[i] > 0) alldivides = false;
        }

        // If the LCM of every element == max(a), then we know every element divides max(a) and vice versa
        // So we can just look over all the factors of max(a) and see how many elements
        // divide each factor, the maximum of that will be our answer
        if (!alldivides) {
            cout << N << endl;
            continue;
        }

        int maxele = 0;

        for (ll i = 1; i <= sqrt(most); i++) {
            if (most % i == 0 && a2.find(i) == a2.end()) {
                int num = 0;
                ll lcmm2 = 1;
                // Iterate through each element that divides this factor
                for (ll ai : a) {
                    if (i % ai > 0) continue;
                    lcmm2 = lcm(lcmm2, ai);
                    num++;
                }
                // Sometimes a subsequence of a may divide this factor but we can't get this LCM
                // So we need to account for that
                if (lcmm2 == i) maxele = max(maxele, num);
            }
            if (most % i == 0) {
                ll i2 = most / i;
                if (a2.find(i2) != a2.end()) continue;
                int num = 0;
                ll lcmm2 = 1;
                // Iterate through each element that divides this factor
                for (ll ai : a) {
                    if (i2 % ai > 0) continue;
                    lcmm2 = lcm(lcmm2, ai);
                    num++;
                }
                // Sometimes a subsequence of a may divide this factor but we can't get this LCM
                // So we need to account for that
                if (lcmm2 == i2) maxele = max(maxele, num);
            }
        }

        cout << maxele << endl;
    }
}