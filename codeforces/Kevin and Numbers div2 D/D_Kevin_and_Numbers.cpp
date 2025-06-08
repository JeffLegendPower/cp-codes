// https://codeforces.com/contest/2061/problem/D

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

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        ll a[N], b[M];
        map<ll, ll> nums;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            nums[a[i]]++;
        } for (int i = 0; i < M; i++) {
            cin >> b[i];
            nums[b[i]]--;
        }

        int numpos = 0;
        // for (auto itr = nums.begin(); itr != nums.end(); itr++) {
        //     if (itr->second > 0) numpos++;
        //     if (itr->second == 0) nums.erase(itr->first);
        // }

        for (auto it = nums.begin(); it != nums.end();) {
            if (it->second > 0) {
                ++numpos;
            }
            if (it->second == 0) {

                it = nums.erase(it);
            } else {
                ++it;
            }
        }

        bool works = true;
        while (!nums.empty()) {
            auto itr = nums.rbegin();

            if (itr->second > 0) {
                works = false;
                break;
            }

            if (itr->first == 0) works = false;

            if ((itr->first)%2 == 0) {
                if (-2*itr->second > nums[itr->first/2]) numpos--;
                if (-2*itr->second == nums[itr->first/2]) nums.erase(itr->first/2);
                else nums[itr->first/2] += 2*itr->second;
            } else {
                if (-itr->second > nums[(itr->first-1)/2]) numpos--;
                if (-itr->second == nums[(itr->first-1)/2]) nums.erase((itr->first-1)/2);
                else nums[(itr->first-1)/2] += itr->second;

                if (-itr->second > nums[(itr->first-1)/2 + 1]) numpos--;
                if (-itr->second == nums[(itr->first-1)/2 + 1]) nums.erase((itr->first-1)/2 + 1);
                else nums[(itr->first-1)/2 + 1] += itr->second;
            }

            nums.erase(itr->first);
        }

        if (works) cout << "Yes";
        else cout << "No";
        cout << endl;
    }
}