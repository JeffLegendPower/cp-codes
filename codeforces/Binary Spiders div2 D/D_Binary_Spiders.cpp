// https://codeforces.com/contest/1625/problem/D

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


// Taken from gfg
ll max_xor(vector<plli> &arr, int n) {
    int maxx = 0, mask = 0;

    set<ll> se;
 
    for (int i = 30; i >= 0; i--) {
        mask |= (1 << i);
 
        for (int j = 0; j < n; j++)
            se.insert(arr[j].first & mask);
 
        ll newMaxx = maxx | (1 << i);
 
        for (ll prefix : se) {
            if (se.count(newMaxx ^ prefix)) {
                maxx = newMaxx;
                break;
            }
        }
        se.clear();
    }
 
    return maxx;
}

int main() {
    int N;
    ll k;
    cin >> N >> k;
    
    ll k2 = k;
    int dividenum = 0;
    while (k2 > 0) {
        k2 /= 2;
        dividenum++;
    }

    ll a[N];
    vector<int> idxs;
    set<ll> usedgreater;
    vector<plli> unused;
    map<ll, int> unusedmap;

    for (int i = 0; i < N; i++) {
        cin >> a[i];
        ll a2 = a[i];
        if (dividenum > 0) for (int j = 0; j < dividenum; j++) a2 /= 2;
        if (a2 > 0) {
            if (usedgreater.find(a2) == usedgreater.end()) {
                usedgreater.insert(a2);
                idxs.push_back(i + 1);
            }
        } else {
            unused.push_back({a[i], i + 1});
        }
    }

    ll maxxor = max_xor(unused, unused.size());
    if (maxxor < k) {
        if (unused.size() > 0) idxs.push_back(unused[0].second);
        goto end;
    }

    for (int i = 0; i < unused.size(); i++) {
        if (unusedmap[unused[i].first] > 0) {
            idxs.push_back(unused[i].second);
            idxs.push_back(unusedmap[unused[i].first]);
            break;
        }

        unusedmap[maxxor ^ unused[i].first] = unused[i].second;
    }

    end:
    if (idxs.size() >= 2) {
        cout << idxs.size() << endl;
        for (int idx : idxs) cout << idx << " ";
    } else cout << -1;
}