// https://codeforces.com/contest/1515/problem/D

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
    int T;
    cin >> T;

    while (T--) {
        int N, l, r;
        cin >> N >> l >> r;

        int freq[N + 1];
        for (int i = 0; i <= N; i++) freq[i] = 0;

        for (int i = 0; i < N; i++) {
            int ci;
            cin >> ci;
            if (i < l) freq[ci]++;
            else freq[ci]--;
        }

        map<int, int> pos, neg;
        for (int i = 1; i <= N; i++) {
            if (freq[i] > 0) pos[i] = freq[i];
            else if (freq[i] < 0) neg[i] = -freq[i];
        }

        int oper = 0;

        auto left = pos.begin(), right = neg.begin();
        while (left != pos.end() && right != neg.end()) {
            if (pos[left->first] == 0) {
                left++;
                continue;
            } if (neg[right->first] == 0) {
                right++;
                continue;
            }

            int rem = min(left->second, right->second);
            oper += rem;
            pos[left->first] -= rem;
            neg[right->first] -= rem;
        }

        while (left != pos.end() && pos[left->first] == 0) left++;
        while (right != neg.end() && neg[right->first] == 0) right++;

        int extra = 0;
        while (left != pos.end()) {
            int num = left->second;
            oper += num / 2;
            extra += num % 2;
            left++;
        } while (right != neg.end()) {
            int num = right->second;
            oper += num / 2;
            extra += num % 2;
            right++;
        }

        oper += extra;
        cout << oper << endl;
    }
}