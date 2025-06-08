// https://codeforces.com/contest/1976/problem/D

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 3 * 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return max(a, b);
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0; // NOTE, must change to something like 1e6 or 1e9 if using min()
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    int T;
    cin >> T;

    while (T--) {
        string s;
        cin >> s;
        N = s.size();

        int pre[N + 1];
        pre[0] = 0;
        t[N] = pre[0];
        for (int i = 0; i < N; i++) {
            pre[i + 1] = pre[i];
            if (s[i] == '(') pre[i + 1]++;
            else pre[i + 1]--;

            t[i + N + 1] = pre[i + 1];
        }

        build();

        ll total = 0;

        map<int, ll> nums;
        map<int, int> lastpos;
        for (int i = 0; i < N; i++) {
            int cur = pre[i + 1];

            if (lastpos.find(cur) == lastpos.end()) {
                lastpos[cur] = i;
                nums[cur]++;
                continue;
            }
            int maxbetween = query(lastpos[cur] + 1, i + 1);
            if ((maxbetween + 1) / 2 > cur) {
                total += nums[cur] * (nums[cur] - 1) / 2;
                nums[cur] = 1;
            } else nums[cur]++;

            lastpos[cur] = i;
        }

        for (auto itr = nums.begin(); itr != nums.end(); itr++) {
            total += (itr->second) * (itr->second - 1) / 2;
        }

        cout << total << endl;
    }
}