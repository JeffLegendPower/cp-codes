// https://cses.fi/problemset/task/1734

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 2e5;  // limit for array size
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

struct qry {
    int a, b;
    int ans;
    int idx;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int Q;
    cin >> N >> Q;

    ll x[N];
    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }

    map<ll, vector<int>> idxs;
    for (int i = N - 1; i >= 0; i--) {
        if (idxs[x[i]].size() > 0) {
            t[N + idxs[x[i]].back()] = 0;
        }

        idxs[x[i]].push_back(i);
        t[N + i] = 1;
    }

    build();

    vector<qry> q;
    for (int i = 0; i < Q; i++) {
        qry cur;
        cin >> cur.a >> cur.b;
        cur.a--, cur.b--;
        cur.idx = i;

        q.push_back(cur);
    }

    sort(q.begin(), q.end(), [](qry one, qry two) {
        return one.a < two.a;
    });

    int left = 0;
    for (int i = 0; i < Q; i++) {
        qry cur = q[i];
        int a = cur.a, b = cur.b;

        while (left < a) {
            modify(left, 0);
            idxs[x[left]].pop_back();
            if (idxs[x[left]].size() > 0) {
                modify(idxs[x[left]].back(), 1);
            }

            left++;
        }

        q[i].ans = query(a, b + 1);
    }

    sort(q.begin(), q.end(), [](qry one, qry two) {
        return one.idx < two.idx;
    });

    for (int i = 0; i < Q; i++) cout << q[i].ans << endl;
}