// https://codeforces.com/contest/1418/problem/G

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

    ll MOD = 1e9 + 7;

    int N; cin >> N;
    int a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    ll hashes[N + 1];
    hashes[0] = 0;
    for (int i = 1; i <= N; i++) hashes[i] = uld(10000ll, 1e9 + 6);

    vector<int> cnts(N + 1, 0);

    ll hashpre[N + 1];
    ll hash = 0;
    hashpre[0] = 0;
    for (int i = 0; i < N; i++) {
        int ai = a[i];
        
        hash ^= hashes[a[i]] * cnts[a[i]];

        cnts[a[i]]++;
        cnts[a[i]] %= 3;

        hash ^= hashes[a[i]] * cnts[a[i]];

        hashpre[i + 1] = hash;
    }

    ll total = 0;
    map<ll, ll> nums;
    nums[0] = 1;

    cnts = vector<int>(N + 1, 0);
    int left = -1;
    for (int i = 0; i < N; i++) {
        cnts[a[i]]++;
        while (cnts[a[i]] > 3) {
            if (left >= 0) cnts[a[left]]--;
            if (left >= 0) nums[hashpre[left]]--;
            left++;
        }

        cout << left << " " << hashpre[i + 1] << endl;

        total += nums[hashpre[i + 1]];
        nums[hashpre[i + 1]]++;
    }

    cout << total;
}