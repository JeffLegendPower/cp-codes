// https://codeforces.com/problemset/problem/1082/E

// I had a lot of implementation issues, gotta make sure I do it right
// This problem can be solved by using dp on the first i elements
// First, we need to notice that we can split up our elements into
// groups. One group is the elements = to c, other groups are elements of 
// the same value. If we do an operation just incrementing 0, then the
// score (num elements = c) would be only the elements already equal to c
// Now, for any given [l, r] where we set element with value x to c, the score
// would be (num c in array) - (num c in subsequence) + (num x in subsequence)
// Now we can hold a counter for the num of occurences of each value in the array a
// and their start index. By default, we'd want to set the start index to the first
// occurence of that value in the array. And every time we see that element we increment the counter
// However, we would only want to keep that subsequence if the num x in the subsequence >= num c
// As otherwise, it's better to just not keep that subsequence and move it to after those c
// as we'd get more score from those c than those x in the previous subsequence.
// So the moment that happens, we reset the counter and update the start index for the subsequence of that value
// We will also always update the maximum score for each value whenever we have an occurence of an element x
// So at the end we can go through all the values and find the maximum score we could've achieved
// We end up solving this in O(n)

// The way we decide when to re-fix the start index for a value is VERY similar to how Kadane's algorithm does it

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
    int N, c;
    cin >> N >> c;

    int a[N];
    int cprefix[N + 1];
    cprefix[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        cprefix[i + 1] = cprefix[i];
        if (a[i] == c) cprefix[i + 1]++;
    }

    vector<int> bestdpcount((int) 5e5 + 1, 0);   

    vector<int> dpcount((int) 5e5 + 1, 0);
    vector<int> dpstart((int) 5e5 + 1, -1);
    int c_count = 0;

    for (int i = 0; i < N; i++) {
        if (a[i] == c) {
            c_count++;
            continue;
        }

        if (dpstart[a[i]] == -1) dpstart[a[i]] = i;
        if (dpcount[a[i]] < cprefix[i + 1] - cprefix[dpstart[a[i]]]) {
            dpstart[a[i]] = i;
            dpcount[a[i]] = 0;
        }

        dpcount[a[i]]++;

        if (dpcount[a[i]] + cprefix[N] - cprefix[i + 1] + cprefix[dpstart[a[i]]] > bestdpcount[a[i]]) {
            bestdpcount[a[i]] = dpcount[a[i]] + cprefix[N] - cprefix[i + 1] + cprefix[dpstart[a[i]]];
        } 
    }

    int mostcount = cprefix[N];

    for (int i = 0; i <= (int) 5e5; i++) mostcount = max(mostcount, bestdpcount[i]);

    cout << mostcount << endl;
}