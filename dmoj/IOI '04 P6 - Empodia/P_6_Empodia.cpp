// https://dmoj.ca/problem/ioi04p6

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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

    int N; cin >> N;

    int a[N], p[N];
    map<int, set<int>> st;
    stack<int> less, more;
    
    vector<pii> empodia;
    int rem = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        p[i] = a[i] - i;
        int back = 0; // index of rightmost ele > a[i]

        while (!less.empty() && a[less.top()] > a[i]) {
            int j = less.top();
            st[p[j]].erase(j);
            less.pop();
        }
        less.push(i);

        while (!more.empty() && a[more.top()] < a[i]) more.pop();
        if (more.empty()) back = -1;
        else back = more.top();
        more.push(i);

        if (st[p[i]].empty()) {
            st[p[i]].insert(i);
            continue;
        }

        int stidx = *st[p[i]].rbegin();
        if (stidx > back) {
            empodia.push_back({stidx, i});

            while (rem <= stidx) {
                st[p[rem]].erase(rem);
                rem++;
            }
        }

        st[p[i]].insert(i);
    }

    cout << empodia.size() << endl;
    for (auto [a, b] : empodia) cout << a+1 << " " << b+1 << endl;
}