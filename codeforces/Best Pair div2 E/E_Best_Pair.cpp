// https://codeforces.com/contest/1637/problem/E

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;
    
    while (T--) {
        int N, M;
        cin >> N >> M;

        map<ll, ll> freq;
        ll a[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }


        map<ll, set<ll>> badpairs;
        for (int i = 0; i < M; i++) {
            ll x, y;
            cin >> x >> y;
            badpairs[x].insert(y);
            badpairs[y].insert(x);
        }

        // cnt[i] = vector of elements which have a freq of i
        vector<vector<ll>> cnts(N + 1);

        for (auto itr = freq.begin(); itr != freq.end(); itr++) {
            cnts[itr->second].push_back(itr->first);
        }

        for (int i = 0; i <= N; i++) {
            sort(cnts[i].begin(), cnts[i].end(), greater<ll>());
        }

        // compress and get rid of the empty vectors
        // {cnt, vector}
        vector<pair<ll, vector<ll>>> cnts2;
        for (int i = 0; i <= N; i++) {
            if (cnts[i].size() > 0) cnts2.push_back({i, cnts[i]});
        }

        ll most = 0;

        for (auto [freqa, cur] : cnts2) {
        for (ll ai : cur) {
        // for (ll ai : a) {
            ll freqa = freq[ai];

            // for (ll cnt = 1; cnt <= freqa; cnt++) {
            int idx = 0;
            int t = 0;
            while (idx < cnts2.size() && cnts2[idx].first <= freqa) {
                ll cnt = cnts2[idx].first;

                ll i = 0;
                while (i < cnts[cnt].size() && 
                    (
                        (cnts[cnt][i] == ai)
                        || (badpairs[ai].find(cnts[cnt][i]) != badpairs[ai].end())
                    )
                ) i++;

                if (i < cnts[cnt].size()) {
                    most = max(most, (freqa + cnt) * (ai + cnts[cnt][i]));
                }

                idx++;
            }
        }
        }

        cout << most << endl;
    }
}