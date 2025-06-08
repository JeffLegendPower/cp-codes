// https://codeforces.com/contest/1991/problem/D

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


vector<bool> isprime;
vector<int> primes;

void findprimes(int N) {
    isprime.resize(N + 1);

    fill(isprime.begin(), isprime.end(), true);
    for (int p = 2; p * p <= N; p++) {
        if (isprime[p]) {
            for (int i = p * p; i <= N; i += p)
                isprime[i] = false;
        }
    }

    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            primes.push_back(i);
        }
    }
}

struct node {
    bool searched = false;
    vector<int> next;
    int color;
};
vector<node> graph;
vector<bool> recurs;

void testcoloring() {
    bool works = true;
    for (int i = 0; i < N; i++) {
        int color = graph[i].color;
        for (int next : graph[i].next) {
            if (graph[next].color == color) {
                works = false;
                // cout << i << " " << next << endl;
                break;
            }
        }
        if (!works) break;
    }

    cout << works << endl;
}

int main() {
    int T;
    cin >> T;

    findprimes(524287);

    while (T--) {
        int N;
        cin >> N;

        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            graph.push_back({});
            recurs.push_back(false);
        } for (int i = 1; i <= N; i++) {
            for (int prime : primes) {
                int xorr = prime ^ i;
                if (xorr < i) continue;
                if (xorr > N || xorr == 0) continue;
                graph[i - 1].next.push_back(xorr - 1);
                graph[xorr - 1].next.push_back(i - 1);

                // cout << i << " " << xorr << endl;
                cnt++;
            }
        }

        for (int i = 0; i < N; i++) cin >> graph[i].color;
        cout << cnt << endl;

        testcoloring();
    }
}