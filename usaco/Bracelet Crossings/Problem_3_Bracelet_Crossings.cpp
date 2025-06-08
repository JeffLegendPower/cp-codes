// https://usaco.org/index.php?page=viewproblem2&cpid=1163&lang=en

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

    int T; cin >> T;

    while (T--) {
        int N, M; cin >> N >> M;

        map<pii, int> cnts;
        vector<int> num(N + 1, 0);
        for (int i = 0; i < M; i++) {
            int k; cin >> k;

            vector<int> cs;
            for (int j = 0; j < k; j++) {
                int x; cin >> x;
                if (num[x]&1) {
                    // I know that this may "mess up" the stack and the counting
                    // but if the stack were to get messed up then this ordering isn't good anyways
                    while (!cs.empty() && cs.back() != x) cs.pop_back();
                    if (!cs.empty()) cs.pop_back();
                    // cout << cs.size() << endl;
                    if (!cs.empty()) cnts[{x, cs.back()}]++;
                } else {
                    // cout << cs.size() << endl;
                    if (!cs.empty()) cnts[{x, cs.back()}]++;
                    cs.push_back(x);
                }

                num[x]++;
            }
        }

        bool works = true;
        for (auto itr = cnts.begin(); itr != cnts.end(); itr++) {
            cout << "E";
            // cout << itr->first.first << " " << itr->first.second << "  " << itr->second << endl;
            if (itr->second != num[itr->first.first]) works = false;
        }
        
        cout << (works ? "YES" : "NO") << endl;
    }
}