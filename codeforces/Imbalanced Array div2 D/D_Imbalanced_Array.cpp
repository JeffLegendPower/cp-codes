// https://codeforces.com/contest/817/problem/D

// First, the imbalance of a subsegment can be written as the max of the subsegment - the min
// So the total imbalance of the array is the sum of the maxes of all the subsegments
// minus all the mins
// Now we can do this by looking at each element and the number of subsegments that element is the min in (and max)
// There's a final detail that a subsegment can have multiple mins or maxes, so we will want to find the
// number of subsegments that an element is the LEFTMOST min or max in
// For each element we can find the left and right bounds that the element is the leftmost min/max in
// For example, to find the left bound of an element for min, we will want to find the rightmost j such that a[j] <= a[i] and j < i
// And for right we will want to find the leftmost j such that a[j] < a[i] and j > i
// To do this we will iterate in the reverse direction and keep a priority queue at hand, so we can always
// check to see if the condition is satisfied, so we can do this precomputation in O(n*logn)
// Now that we have the bounds, we can get the number of arrays such that a[i] is the leftmost min or max
// and add/subtract that to our total imbalance

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
ll t[2 * Nmax];
int h = sizeof(int) * 8 - __builtin_clz(N);
ll d[Nmax];

void apply(int p, ll value) {
    t[p] = max(t[p], value);
    if (p < N) d[p] = max(d[p], value);
}

int oper(int a, int b) {
    return a + b;
}

void build(int p) {
    while (p > 1) p >>= 1, t[p] = t[p<<1] + t[p<<1|1] + d[p];
}

void push(int p) {
  for (int s = h; s > 0; --s) {
    int i = p >> s;
    if (d[i] != 0) {
        apply(i<<1, d[i]);
        apply(i<<1|1, d[i]);
        d[i] = 0;
    }
  }
}

void setmax(int l, int r, ll value) {
  l += N, r += N;
  int l0 = l, r0 = r;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) apply(l++, value);
    if (r&1) apply(--r, value);
  }
  build(l0);
  build(r0 - 1);
}

ll query(int l, int r) {
  l += N, r += N;
  push(l);
  push(r - 1);
  ll res = 0;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


int main() {
    int N;
    cin >> N;

    ll a[N];

    for (int i = 0; i < N; i++) cin >> a[i];

    ll leftmin[N], rightmin[N], leftmax[N], rightmax[N];
    for (int i = 0; i < N; i++) {
        leftmin[i] = -1;
        leftmax[i] = -1;
        rightmin[i] = N;
        rightmax[i] = N;
    }
    priority_queue<pii> minpq;
    for (int i = N - 1; i >= 0; i--) {
        while (!minpq.empty() && minpq.top().first >= a[i]) {
            leftmin[minpq.top().second] = i;
            minpq.pop();
        }
        minpq.push({a[i], i});
    }

    minpq = priority_queue<pii>();
    for (int i = 0; i < N; i++) {
        while (!minpq.empty() && minpq.top().first > a[i]) {
            rightmin[minpq.top().second] = i;
            minpq.pop();
        }
        minpq.push({a[i], i});
    }

    priority_queue<pii, vector<pii>, greater<pii>> maxpq;
    for (int i = N - 1; i >= 0; i--) {
        while (!maxpq.empty() && maxpq.top().first <= a[i]) {
            leftmax[maxpq.top().second] = i;
            maxpq.pop();
        }
        maxpq.push({a[i], i});
    }

    maxpq = priority_queue<pii, vector<pii>, greater<pii>>();
    for (int i = 0; i < N; i++) {
        while (!maxpq.empty() && maxpq.top().first < a[i]) {
            rightmax[maxpq.top().second] = i;
            maxpq.pop();
        }
        maxpq.push({a[i], i});
    }

    ll total = 0;
    for (ll i = 0; i < N; i++) {
        total += a[i] * (i - leftmax[i]) * (rightmax[i] - i);
        total -= a[i] * (i - leftmin[i]) * (rightmin[i] - i);
    }
    cout << total << endl;
}