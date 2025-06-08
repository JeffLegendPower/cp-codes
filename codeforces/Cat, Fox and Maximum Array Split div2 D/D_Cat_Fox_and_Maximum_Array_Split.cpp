// https://codeforces.com/contest/1973/problem/D

// We can solve this with a sequence of steps
// First, we must find the maximum of the array
// This will take at most n operations and we will do this by assuming
// the maximum (iterating from i=1 to N inclusive) and make a query starting at 1
// and with a sum of N*i. If r=N, then that means that the maximum value in the array
// is i. Now, we need to notice that using this we can cut down on the number of possible
// m significantly. To test each value of m, we need k operations. However, there are actually
// only floor(n / k) possible values of m (totaling to at most n operations to test all possible m)
// We can find this by looking at the maximum value in the array and the longest subsegment it can
// be in. Assuming the most ideal case where every element in the array is the maximum,
// each subsequence should be n / k length to have the maximum m as that would make them all
// closest together, and since we are dealing with integers we have to take the floor of n / k
// Now that is for the maximum length, the minimum length is evidently 1 and to get m from length
// you do length * max(a). So now the values of m are max(a), 2*max(a)..., floor(n / k) * max(a)
// and we can just test all of those

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
        int N, k;
        cin >> N >> k;

        // First, find the maximum element in the array
        int maxele = -1;
        for (int i = 1; i <= N; i++) {
            cout << "? 1 " << (i * N) << endl;

            int res;
            cin >> res;
            if (res == N) {
                maxele = i;
                break;
            }
        }
        
        // cout << maxele << endl;

        // What is the largest subsegment with the maximum element that still makes it possible
        // to have an m that the other subsegments can achieve?
        // Assuming the most ideal case where every other element is also the maximum
        // the length of this subsegment must be min(N / k) as any larger means that there will be
        // another subsegment whom even with a maximum element in it would not be able to achieve the same
        // m as this one
        ll maxMcoeff = N / k;

        ll bestm = -1;
        for (ll Mcoeff = maxMcoeff; Mcoeff >= 1; Mcoeff--) {
            int c = 0;
            ll m = maxele * Mcoeff;

            // Test if this m works by going through all the k subsegments
            bool works = true;
            for (int i = 0; i < k; i++) {
                if (c >= N || c == -1) {
                    works = false;
                    break;
                }
                cout << "? " << (c + 1) << " " << m << endl;

                cin >> c;
            }

            if (c != N || !works) continue;
            bestm = max(bestm, m);
        }

        cout << "! " << bestm << endl;

        int correct;
        cin >> correct;
        if (correct == -1) return 0;
    }
}