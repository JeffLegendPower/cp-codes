// https://codeforces.com/contest/1203/problem/F2

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

    int N, R; cin >> N >> R;

    pii projs[N];
    for (int i = 0; i < N; i++) {
        cin >> projs[i].first >> projs[i].second;
        if (projs[i].second < 0) projs[i].first = max(projs[i].first, -projs[i].second);
    }

    sort(projs, projs + N, [](pii one, pii two) {
        if (one.second >= 0 && two.second >= 0) return one.first < two.first;
        else if (one.second < 0 && two.second < 0) {
            // order such that worst case, maximum rating after project will be higher
            return one.first + one.second > two.first + two.second;
        } else return one.second > two.second;
    });

    int num = 0;
    int i;
    for (i = 0; i < N; i++) {
        if (projs[i].second < 0) break;
        if (R >= projs[i].first) {
            num++;
            R += projs[i].second;
        }
    }

    priority_queue<int> used;
    for (; i < N; i++) {
        if (projs[i].first <= R) {
            num++;
            R += projs[i].second;
        } 
        // if we cant add another project, lets maximize our R if possible
        // note that this wont be a problem because if we are replacing project j with project i
        // and b[j] < b[i] (remember both are negative), since a[j] + b[j] >= a[i] + b[i], a[j] > a[i] so we won't
        // have an issue in replacing j with i
        else if (!used.empty() && used.top() < projs[i].second) {
            R -= used.top();
            R += projs[i].second;
            used.pop();
        }
    }

    cout << num;
}